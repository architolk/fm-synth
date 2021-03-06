/*
* Dx2xfm: reading DX7 sysex file and convert them to XFM2 parameter values (in JSON format)
*
* Based on:
* - https://github.com/xerhard/DX7syx-to-XFM2patches
*   (Java version, modified and fixed conversion errors)
* - https://github.com/rheslip/dx72xfm2
*   (C version, with better conversion - the java version has been modified with the optimalizations from the C version)
*
* Author: https://github.com/architolk
*/
package nl.architolk.dx2xfm;

import java.nio.ByteBuffer;
import java.io.IOException;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import org.json.JSONArray;
import org.json.JSONObject;

import static java.nio.file.Files.readString;

public class Dx2xfm {

   private static String confDir;
   private static JSONArray flatcurve;
   private static JSONArray levelcurve;
   private static JSONArray ratecurve;
   private static JSONArray attackcurve;
   private static JSONArray paramnames;
   private static JSONArray inits;

   private static int lscale(int rate, JSONArray curve) {
   	float x1,y1,x2,y2,y,slope,r;
   	r = (float) rate;
   	x1 = curve.getJSONObject(0).getInt("DX7");
   	y1 = curve.getJSONObject(0).getInt("XFM2");;
   	for (int i=1;i <curve.length(); i++) {  // step through each line segment of the curve
      x2 = curve.getJSONObject(i).getInt("DX7");
      y2 = curve.getJSONObject(i).getInt("XFM2");;
   		if (x2 >= r) {  // find the segment this rate (X point) lies on
   			slope = (y2-y1)/(x2-x1);
   			y = y1+(r-x1)*slope;
   			return (int)(Math.round(y));
   		}
   		x1=x2;
   		y1=y2;
   	}
   	return 255;  // if curves are correct we should never get here
   }

   private static JSONArray loadConfig(String name) {
     try {
        String JsonStr = readString(Paths.get(confDir + name + ".json"), StandardCharsets.UTF_8);
        JSONObject jsonObject = new JSONObject(JsonStr);
        return (JSONArray) jsonObject.get("parameters");
     } catch (Exception e) {
         e.printStackTrace();
         System.exit(1);
         return null;
     }
   }

   private static int getXFM2Ratio(int dx7ratio) {
     double ratio = dx7ratio;
     ratio = 256/(Math.log(2)/Math.log(1+ratio/100)); // log(2)/log(x) = log2(x)
     return (int)Math.round(ratio);
   }

   public static void main(String[] args) {

     if (args.length!=1) {
   System.out.println("Need as argument filename.syx");
   System.exit(1);
 }
     String extention = "";
     String fullName = args[0];

     if (fullName.lastIndexOf(".") != -1 && fullName.lastIndexOf(".") != 0){
         extention=fullName.substring(fullName.lastIndexOf(".")+1);
         if (!extention.equals("syx")) {
             System.out.println("Wrong extention, need .syx file");
             System.exit(1);
         }
     }
     else {
         System.out.println("Need as argument filename.syx");
         System.exit(1);
     }
     String DX7Syx = fullName.substring(0,fullName.lastIndexOf("."));
     String baseDir = "./";

     String fInput =  baseDir + DX7Syx + ".syx";
     String fOutput = baseDir + "out/" + DX7Syx + ".h";
     String XFM2out = baseDir + "out/XFM2/";
     String DX7out =  baseDir + "out/DX7/";
     confDir = baseDir + "conf/";
     String confStr = confDir + "000init.json";

     List<String> names = new ArrayList<String>();

     try {
       Files.createDirectories(Paths.get(baseDir + "out"));
       Files.createDirectories(Paths.get(XFM2out));
       Files.createDirectories(Paths.get(DX7out));
     } catch (Exception e) {
         //Nothing: exception might be that directory already exists - whatever...
     }

     flatcurve = loadConfig("curve_flat");
     levelcurve = loadConfig("curve_level");
     ratecurve = loadConfig("curve_rate");
     attackcurve = loadConfig("curve_attack");
     paramnames = loadConfig("DX7Params");

     try (
             InputStream inputStream = new BufferedInputStream(new FileInputStream(fInput));
             FileWriter outwriter = new FileWriter(fOutput);
     ) {
         long fileSize = new File(fInput).length();
         byte[] allBytes = new byte[(int) fileSize];
         byte[] singlVoice = {(byte) 0xF0, 0x43, 0x00, 0x00};
         byte[] multiVoice = {(byte) 0xF0, 0x43, 0x00, 0x09};
         byte[] name = new byte[10];
         int[]  DX7Par = new int[155];
         String ProgName = null;
         String pNameSpaces = null;

         outwriter.write("//DX7 converted Sysex patches\n");
         outwriter.write("//Name: " + DX7Syx + "\n");
         outwriter.write("typedef struct {\n");
         outwriter.write("  char * const name;\n");
         outwriter.write("  uint8_t algo;\n");
         outwriter.write("  uint8_t pval[512];\n");
         outwriter.write("} patch_type;");
         outwriter.write("\n");
         outwriter.write("const patch_type PATCHPARAMS[32] PROGMEM = {\n");

         inputStream.read(allBytes);
         if (ByteBuffer.wrap(allBytes, 0, 4).equals(ByteBuffer.wrap(singlVoice, 0, 4))) {
             System.out.println("************** Single DX7Par SysEx file found");
         } else if (ByteBuffer.wrap(allBytes, 0, 4).equals(ByteBuffer.wrap(multiVoice, 0, 4))) {
             System.out.println("************** Multi DX7Par SysEx file found");
             int startpos = 0;
             for (int i = 0; i < 32; i++) {  // Read all 32 Program presets  !! Less for testing
                 System.out.println(">>>>>>> START PRESET NUMBER: " + i);
                 String iStr = String.format("%02d", i);
                 startpos = 6 + i*128;
                 //START Read 6 operator blocks 0 .. 101
                 for (int p = 0; p < 6; p++) {  // 21 parameters to be filled from 17 packed
                     //First 11 parameters 0 .. 10   Read byte into int as unsigned: int i2 = b & 0xFF;
                     for (int q = 0; q < 11; q++) {
                         DX7Par[q+p*21] = allBytes[(startpos + p*17 + q)] & 0xFF;
                     }
                     //extract packed parameters 11 .. 16
                     DX7Par[11+p*21] = allBytes[startpos + p*17 + 11] & 0x03;        // LEFT CURVE
                     DX7Par[12+p*21] = (allBytes[startpos + p*17 + 11] & 0x0C)>>2;   // RGHT CURVE
                     DX7Par[13+p*21] = allBytes[startpos + p*17 + 12] & 0x07;        // Keyb Rate Scale
                     DX7Par[20+p*21] = (allBytes[startpos + p*17 + 12] & 0x78)>>3;   // OSC DETUNE
                     DX7Par[14+p*21] = allBytes[startpos + p*17 + 13] & 0x03;        // AMP MOD SENSITIVITY
                     DX7Par[15+p*21] = (allBytes[startpos + p*17 + 13] & 0x1C)>>2;   // KEY VEL SENSITIVITY
                     DX7Par[16+p*21] = allBytes[startpos + p*17 + 14]& 0xFF;         // OP# OUT LEVEL
                     DX7Par[17+p*21] = allBytes[startpos + p*17 + 15] & 0x01;        // OSC MOD fixed/ratio 0=ratio
                     if (DX7Par[17+p*21]==0) {
                       DX7Par[18+p*21] = (allBytes[startpos + p*17 + 15] & 0x3E)>>1;   // OSC FREQ COARSE, ratio PITCH
                     } else {
                       DX7Par[18+p*21] = (allBytes[startpos + p*17 + 15] & 0x06)>>1;   // OSC FREQ COARSE, fixed pitch
                     }
                     DX7Par[19+p*21] = allBytes[startpos + p*17 + 16] & 0xFF;        // OSC FREQ FINE
                     // DX7Par 20 already filled ...
                 }
                 //END Read 6 operator blocks 0 .. 101
                 //Read program parameters 102 .. 117
                 for (int q = 102; q < 110; q++) {      /// check counting left & right
                     DX7Par[q+24] = allBytes[startpos +  q] & 0xFF;
                 }
                 DX7Par[134] = allBytes[startpos + 110] & 0x1F;        // ALGORITHM
                 DX7Par[135] = allBytes[startpos + 111] & 0x07;        // FEEDBACK
                 DX7Par[136] = (allBytes[startpos + 111] & 0x08)>>3;   // Osc Key Sync OKS
                 DX7Par[137] = allBytes[startpos + 112] & 0xFF;        // LFO SPEED
                 DX7Par[138] = allBytes[startpos + 113] & 0xFF;        // LFO DELAY
                 DX7Par[139] = allBytes[startpos + 114] & 0xFF;        // PITCH MOD DEPTH
                 DX7Par[140] = allBytes[startpos + 115] & 0xFF;        // AMP MOD DEPTH
                 DX7Par[141] = allBytes[startpos + 116] & 0x01;        // LFO SYNC
                 DX7Par[142] = (allBytes[startpos + 116] & 0x0E)>>1;   // LFO Waveform
                 DX7Par[143] = (allBytes[startpos + 116] & 0x70)>>4;   // LFO Mod Sensitivity
                 DX7Par[144] = allBytes[startpos + 117] & 0xFF; // TRANSPOSE
                 //Read Program name 118 .. 127
                 for (int n = 0; n < 10 ; n++) {  // 6 + i*128 + 118
                     name[n] = allBytes[6 + i*128 + 118 + n];
                     DX7Par[145+n] = allBytes[6 + i*128 + 118 + n];
                 }
                 pNameSpaces = new String(name);
                 ProgName = pNameSpaces.replaceAll("[^a-zA-Z0-9#()]+","_");
                 System.out.println("Found preset: " + ProgName );
                 // Write DX7 preset as Json file
                 Date date = Calendar.getInstance().getTime();
                 DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss z");
                 String strDate = dateFormat.format(date);

                 String fJson = DX7out + DX7Syx + "_" + iStr + "-DX7-" + ProgName + ".json";
                 try (FileWriter writer = new FileWriter(fJson)) {
                     // Build json header
                     String jHead = "{\n\t\"Short_Name\": \"" + pNameSpaces + "\",\n";
                     jHead = jHead + "\t\"Long_Name\": \"DX7-" + pNameSpaces + "  " + iStr + "\",\n";
                     jHead = jHead + "\t\"Description\": \"Converted from DX7 SysEx file " + DX7Syx + ".syx\",\n";
                     jHead = jHead + "\t\"Creator\": \"Design.Thoughtz.eu\",\n";
                     jHead = jHead + "\t\"date\": \"" + strDate + "\",\n";
                     jHead = jHead + "\t\"hash\": \"0\",\n";
                     jHead = jHead + "\t\"parameters\": [\n";
                     writer.write(jHead);
                     for (int k = 0; k < 155; k++) {
                         String paramname = paramnames.getJSONObject(k).getString("Name");
                         writer.write("\t\t{ \"Par#\": " + k + " , \"Value\": " + DX7Par[k] + ", \"Name\": \"" + paramname + "\" }");
                         if (k==154) {
                           writer.write("\n");
                         } else {
                           writer.write(",\n");
                         }
                     }
                     writer.write("\t]\n}\n");
                     writer.flush();
                     System.out.println("Saved Program to: " + fJson );
                 }
                 // create XFM2 byte buffer
                 byte[] XFM2parB = new byte[512];
                 long[] XFM2parL = new long[512];
                 // read init into XFM2 buffer

                 String JsonStr = readString(Paths.get(confStr), StandardCharsets.UTF_8);
                 try {
                     JSONObject jsonObject = new JSONObject(JsonStr);
                     // Build Parameter string for json file to write to
                     String parStr = "\t\"parameters\": [\n";
                     int lPar;
                     int lVal;

                     inits = (JSONArray) jsonObject.get("parameters");
                     Iterator<Object> iterator = inits.iterator();
                     while (iterator.hasNext()) {
                         JSONObject element = (JSONObject) iterator.next();
                         lPar = (int) element.get("Par#");
                         lVal = (int) element.get("Value");
                         XFM2parL[lPar] = lVal;
                     }

                 } catch (Exception e) {
                     e.printStackTrace();
                 }
                 // read in Algorithm file related to DX7Par[134] value
                     int alg = DX7Par[134]+1;  // DX7 0..31 conf files, Display 1..32
                     String algPath = baseDir + "conf/_";
                     String algStr = String.format("%02d", alg);
                     algPath = algPath + algStr + "DX7Algorithm.json";
                     //System.out.println(algPath);
                 JsonStr = readString(Paths.get(algPath), StandardCharsets.UTF_8);
                 try {
                     JSONObject jsonObject = new JSONObject(JsonStr);
                     //System.out.println(jsonObject.toJSONString());
                     // Build Parameter string for json file to write to
                     String parStr = "\t\"parameters\": [\n";
                     int lPar;
                     int lVal;

                     JSONArray array = (JSONArray) jsonObject.get("parameters");
                     Iterator<Object> iterator = array.iterator();
                     while (iterator.hasNext()) {
                         JSONObject element = (JSONObject) iterator.next();
                         lPar = (int) element.get("Par#");
                         lVal = (int) element.get("Value");
                         XFM2parL[lPar] = lVal;
                     }
                 } catch (Exception e) {
                     e.printStackTrace();
                 }
                 // calculate feedback
                 for (int p = 7; p < 13 ; p++) {
                     XFM2parL[p] = XFM2parL[p]*DX7Par[135]*255/7; //Max value DX7 = 7, max value XFM2 = 255
                 }
                 // translate DX7Par parameters to XFM2 buffer values per Operator
                 long mode = 0x00;
                 for (int op = 0;  op < 6 ; op++) {  //dx7 starts with OP6 and xfm2 with OP1
                     XFM2parL[103+op]= lscale(DX7Par[0+(5-op)*21],attackcurve); // R1
                     XFM2parL[110+op]= lscale(DX7Par[1+(5-op)*21],ratecurve); // R2
                     XFM2parL[117+op]= lscale(DX7Par[2+(5-op)*21],ratecurve); // R3
                     XFM2parL[124+op]= lscale(DX7Par[3+(5-op)*21],ratecurve); // R4
                     XFM2parL[75+op]= DX7Par[4+(5-op)*21]*255/99;  // L1
                     XFM2parL[82+op]= DX7Par[5+(5-op)*21]*255/99;  // L2
                     XFM2parL[89+op]= DX7Par[6+(5-op)*21]*255/99;  // L3
                     XFM2parL[96+op]= DX7Par[7+(5-op)*21]*255/99;  // L4
                     XFM2parL[45+op]= DX7Par[8+(5-op)*21]+21;        // BP DX7 C3=27 , XFM2 C3=48
                     XFM2parL[51+op]= DX7Par[9+(5-op)*21]*255/99;  // Key LDept
                     XFM2parL[57+op]= DX7Par[10+(5-op)*21]*255/99; // Key RDept
                     XFM2parL[63+op] = (DX7Par[11+(5-op)*21]==0) ? 1 : (DX7Par[11+(5-op)*21]==1) ? 0 : (DX7Par[11+(5-op)*21]==2) ? 3 :2;
                     XFM2parL[69+op] = (DX7Par[12+(5-op)*21]==0) ? 1 : (DX7Par[12+(5-op)*21]==1) ? 0 : (DX7Par[12+(5-op)*21]==2) ? 3 :2;
                     XFM2parL[140+op]= DX7Par[13+(5-op)*21]*255/7;     //Rate Key (DX7: 0-7, XFM2: 0-255)
                     XFM2parL[159+op]= DX7Par[14+(5-op)*21]*255/3;     //AMS (DX7: 0-3, XFM2: 0-255)
                     XFM2parL[39+op]= DX7Par[15+(5-op)*21]*255/7;      //Velo Sens (DX7: 0-7, XFM2: 0-255)
                     //Just a test: it seems that the original flat level is better, just KB levels should be better!!!
                     XFM2parL[33+op]= DX7Par[16+(5-op)*21]*255/99;
                     /*
                     if ((XFM2parL[1+op] & 1) == 1) {
                       XFM2parL[33+op]= lscale(DX7Par[16+(5-op)*21],flatcurve); // LEVEL for carriers
                     } else {
                       XFM2parL[33+op]= lscale(DX7Par[16+(5-op)*21],levelcurve); // LEVEL for operators
                     }
                     */
                     // MODE DX7Par[17..] on DX7 1bit per Operator => XFM2 bits set in XFM2parL[14]
                     mode |= DX7Par[17+(5-op)*21] << (op);
                     if (DX7Par[17+(5-op)*21]==0) {
                       //Pitch ratio
                       XFM2parL[15+op]= DX7Par[18+(5-op)*21];       // RATIO
                       XFM2parL[21+op]= getXFM2Ratio(DX7Par[19+(5-op)*21]); // Fine ratio XFM2 = part of an octave, Fine ratio DX7 = part of a frequency
                       // Check!!
                       XFM2parL[27+op]= 128+(DX7Par[20+(5-op)*21]-7);  // Pitch FINE  neutral   DX7 (0-14)  7 = XFM2 128
                       // CHeck!!
                     } else {
                       // Fixed pitch
                       double freq = DX7Par[18+(5-op)*21];
                       freq = (freq==0) ? 1 : (freq==1) ? 10 : (freq==2) ? 100 : 1000; //Frequency part from coarse
                       freq = freq * (1 + 8.772*DX7Par[19+(5-op)*21]/99); //Calculated frequency
                       XFM2parL[15+op] = (int)(freq/32.7); //RATIO = Rounded down frequency/32.7
                       freq = (freq - 32.7*XFM2parL[15+op])/(32.7*XFM2parL[15+op]); //frequency ratio we need to add (kinda similar to ratio fine)
                       XFM2parL[21+op] = (int)Math.round(256/(Math.log(2)/Math.log(1+freq))); // FINE RATIO: log(2)/log(x) = log2(x))
                       XFM2parL[27+op] = 0; // Pitch FINE, detune
                     }
                 }
                 XFM2parL[13]=(DX7Par[136]==1) ? 63 : 0;
                 XFM2parL[14]=mode;
                 XFM2parL[134]= lscale(DX7Par[126],attackcurve);  // R1
                 XFM2parL[135]= lscale(DX7Par[127],ratecurve);  // R2
                 XFM2parL[136]= lscale(DX7Par[128],ratecurve);  // R3
                 XFM2parL[137]= lscale(DX7Par[129],ratecurve);  // R4
                 XFM2parL[130]= DX7Par[130]*255/99;  // L1
                 XFM2parL[131]= DX7Par[131]*255/99;  // L2
                 XFM2parL[132]= DX7Par[132]*255/99;  // L3
                 XFM2parL[133]= DX7Par[133]*255/99;  // L4
                 XFM2parL[13]=(DX7Par[136]==1) ? 63 : 0;  //SYNC
                 XFM2parL[151]= DX7Par[137]*115/30;  // LFO SPEED (255/99 doesn't seem to be OK - according to code of rheslip)
                 XFM2parL[154]= DX7Par[138]*255/99;  // LFO FADE/DELAY
                 XFM2parL[149]= DX7Par[139]*7/17;  // LFO PITCH DEPTH (255/99 doesn't seem to be OK - according to code of rheslip)
                 XFM2parL[150]= DX7Par[140]*255/99;  // LFO AMP DEPTH
                 XFM2parL[152]= DX7Par[141];          // LFO SYNC
                 XFM2parL[153]=(DX7Par[142]==1) ? 3 : (DX7Par[142]==3) ? 1 : DX7Par[142] ; // LFO WAVE
                 // PITCH MOD SENSITIVITY  VOICE[143]
                 // TRANSPOSE DX7: C3 = 24, XFM2: C4 = 24, so XFM2: C3 = 12 (!)
                 // Strangely enough, with "adlib" conversion, the keyboard seems ok, so for now...
                 XFM2parL[174]= DX7Par[144];
                 /*
                 if (DX7Par[144]<12) {
                   XFM2parL[174]= DX7Par[144]; //Problem! Cannot go lower than 0 :-(
                   System.out.println("!!!WARNING: had to shift transpose: resulting voice will be an octave to high");
                 } else {
                   XFM2parL[174]= DX7Par[144]-12;
                 }
                 */

                 // write algorithm values to XFM2 buffer
                 for (int p= 0; p < 512; p++) {
                     XFM2parB[p]= (byte) ( XFM2parL[p] & 0xFF );
                 }
                 // create XFM2 json program file
                 int hash = Arrays.hashCode(XFM2parB);

                 fJson = XFM2out + DX7Syx + "_" + iStr + "-" + ProgName + ".json";
                 try (FileWriter writer = new FileWriter(fJson)) {
                     // Build json header
                     String jHead = "{\n\t\"Short_Name\": \"" + pNameSpaces + "\",\n";
                     jHead = jHead + "\t\"Long_Name\": \"DX7-" + pNameSpaces + "  " + iStr + "\",\n";
                     jHead = jHead + "\t\"Description\": \"Converted from DX7 SysEx file " + DX7Syx + ".syx\",\n";
                     jHead = jHead + "\t\"Creator\": \"https://github.com/architolk\",\n";
                     jHead = jHead + "\t\"date\": \"" + strDate + "\",\n";
                     jHead = jHead + "\t\"hash\": \"" + Integer.toHexString((int) hash) + "\",\n";
                     jHead = jHead + "\t\"parameters\": [\n";
                     writer.write(jHead);
                     for (int k = 0; k < 512; k++) {
                         String paramname = inits.getJSONObject(k).getString("Name");
                         writer.write("\t\t{ \"Par#\": " + k + " , \"Value\": " + Byte.toUnsignedInt(XFM2parB[k]) + ", \"Name\": \"" + paramname + "\" }");
                         if (k==511) {
                           writer.write("\n");
                         } else {
                           writer.write(",\n");
                         }
                     }
                     writer.write("\t]}\n");

                     //Extra Dump
                     names.add(pNameSpaces);
                     outwriter.write("  {" + ProgName + "," + Integer.toString(DX7Par[134]) + ",{");
                     for (int k = 0; k < 512; k++) {
                       if (k>0) {
                         outwriter.write(",");
                       }
                       outwriter.write(Integer.toString(Byte.toUnsignedInt(XFM2parB[k])));
                     }
                     outwriter.write("}}");
                     if (i==31) {
                       outwriter.write("\n");
                     } else {
                       outwriter.write(",\n");
                     }

                     writer.flush();
                     System.out.println("Saved Program to: " + fJson );
                 }
             }
         }
         outwriter.write("};\n");

         Iterator<String> iterator = names.iterator();
          while(iterator.hasNext()) {
              String aname = iterator.next();
              outwriter.write("const char " + aname.replaceAll("[^a-zA-Z0-9#()]+","_") + "[] PROGMEM =  \"" + aname + "\";\n");
          }

         outwriter.flush();

     } catch (IOException ex) {
         ex.printStackTrace();
     }
 }
}
