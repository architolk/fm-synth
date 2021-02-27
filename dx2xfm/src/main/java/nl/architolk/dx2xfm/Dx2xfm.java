package nl.architolk.dx2xfm;

import org.json.JSONArray;
import org.json.JSONObject;

import java.nio.ByteBuffer;
import java.io.IOException;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;

import static java.nio.file.Files.readString;

public class Dx2xfm {

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
/* */
//        String baseDir = "/home/gerhard/Data/Java/Projects/ReadDX7SysEx/src/";
//        String DX7Syx = "aegix";


     String fInput =  baseDir + DX7Syx + ".syx";
     String XFM2out = baseDir + "out/";
     String DX7out =  baseDir + "out/DX7/";
     String confDir = baseDir + "conf/";
     String confStr = confDir + "000init.json";

     try {
       Files.createDirectories(Paths.get(XFM2out));
       Files.createDirectories(Paths.get(DX7out));
     } catch (Exception e) {
         //Nothing: exception might be that directory already exists - whatever...
     }

     try (
             InputStream inputStream = new BufferedInputStream(new FileInputStream(fInput));
     ) {
         long fileSize = new File(fInput).length();
         byte[] allBytes = new byte[(int) fileSize];
         byte[] singlVoice = {(byte) 0xF0, 0x43, 0x00, 0x00};
         byte[] multiVoice = {(byte) 0xF0, 0x43, 0x00, 0x09};
         byte[] name = new byte[10];
         int[]  DX7Par = new int[155];
         String ProgName = null;
         String pNameSpaces = null;

         //System.out.println("File size = " + fileSize + "\n");
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
                 //System.out.println("Startpos = " + startpos);
                 //START Read 6 operator blocks 0 .. 101
                 for (int p = 0; p < 6; p++) {  // 21 parameters to be filled from 17 packed
                     //First 11 parameters 0 .. 10   Read byte into int as unsigned: int i2 = b & 0xFF;
                     //System.out.println(">> OPERATOR NUMBER: " + (6-p));
                     for (int q = 0; q < 11; q++) {
                         DX7Par[q+p*21] = allBytes[(startpos + p*17 + q)] & 0xFF;
                         //System.out.println("q = "+q+" pos = " + (startpos + p*17 + q)+ " "+DX7Par[q+p*21]+" "+(allBytes[(startpos + p*17 + q)] & 0xFF));
                     }
                     //extract packed parameters 11 .. 16
                     DX7Par[11+p*21] = allBytes[startpos + p*17 + 11] & 0x03;        // LEFT CURVE
                     DX7Par[12+p*21] = (allBytes[startpos + p*17 + 11] & 0x0C)>>2;   // RGHT CURVE
                     //System.out.println("Left Curve = " + DX7Par[11] + " Right Curve = " + DX7Par[12]);
                     //System.out.println(DX7Par[12]+" "+((allBytes[startpos + p*17 + 11] & 0x0C)>>2));
                     //System.out.println("********************");
                     DX7Par[13+p*21] = allBytes[startpos + p*17 + 12] & 0x07;        // Keyb Rate Scale
                     DX7Par[20+p*21] = (allBytes[startpos + p*17 + 12] & 0x78)>>3;   // OSC DETUNE
                     //System.out.println("Keyb Rate Scal= " + DX7Par[13] + " OSC DETUNE = " + DX7Par[12]);
                     DX7Par[14+p*21] = allBytes[startpos + p*17 + 13] & 0x03;        // AMP MOD SENSITIVITY
                     DX7Par[15+p*21] = (allBytes[startpos + p*17 + 13] & 0x1C)>>2;   // KEY VEL SENSITIVITY
                     //System.out.println("Amp Mod Sens = " + DX7Par[11] + " Key Vel Sens = " + DX7Par[12]);
                     DX7Par[16+p*21] = allBytes[startpos + p*17 + 14]& 0xFF;         // OP# OUT LEVEL
                     DX7Par[17+p*21] = allBytes[startpos + p*17 + 15] & 0x01;        // OSC MOD fixed/ratio 0=ratio
                     DX7Par[15+p*21] = (allBytes[startpos + p*17 + 15] & 0x3E)>>1;   // OSC FREQ COARSE
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
                 DX7Par[144] = (allBytes[startpos + 117] + 12) & 0xFF; // TRANSPOSE DX7 24 = C3 XFM2 24 = C4
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
                     for (int k = 0; k < 154; k++) {
                         writer.write("\t\t{ \"Par#\": " + k + " , \"Value\": " + DX7Par[k] + " } ,\n");
                     }
                     writer.write("\t\t{ \"Par#\": " + 154 + " , \"Value\": " + DX7Par[154] + " }\n");
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
                 //System.out.println("********** " + XFM2parL.toString());
                 // calculate feedback
                 for (int p = 7; p < 13 ; p++) {
                     XFM2parL[p] = XFM2parL[p]*DX7Par[135]*255/7; //Max value DX7 = 7, max value XFM2 = 255
                 }
                 // translate DX7Par parameters to XFM2 buffer values per Operator
                 long mode = 0x00;
                 for (int op = 0;  op < 6 ; op++) {  //dx7 starts with OP6 and xfm2 with OP1
                     XFM2parL[103+op]= DX7Par[0+(5-op)*21]*256/100; // R1
                     XFM2parL[110+op]= DX7Par[1+(5-op)*21]*256/100; // R2
                     XFM2parL[117+op]= DX7Par[2+(5-op)*21]*256/100; // R3
                     XFM2parL[124+op]= DX7Par[3+(5-op)*21]*256/100; // R4
                     XFM2parL[75+op]= DX7Par[4+(5-op)*21]*256/100;  // L1
                     XFM2parL[82+op]= DX7Par[5+(5-op)*21]*256/100;  // L2
                     XFM2parL[89+op]= DX7Par[6+(5-op)*21]*256/100;  // L3
                     XFM2parL[96+op]= DX7Par[7+(5-op)*21]*256/100;  // L4
                     XFM2parL[45+op]= DX7Par[8+(5-op)*21]+9;        // BP DX7 C3=39 , XFM2 C3=48
                     XFM2parL[51+op]= DX7Par[9+(5-op)*21]*256/100;  // Key LDept
                     XFM2parL[57+op]= DX7Par[10+(5-op)*21]*256/100; // Key RDept
                     XFM2parL[63+op] = (DX7Par[11+(5-op)*21]==0) ? 1 : (DX7Par[11+(5-op)*21]==1) ? 0 : (DX7Par[11+(5-op)*21]==2) ? 3 :4;
                     XFM2parL[69+op] = (DX7Par[12+(5-op)*21]==0) ? 1 : (DX7Par[12+(5-op)*21]==1) ? 0 : (DX7Par[12+(5-op)*21]==2) ? 3 :4;
                     XFM2parL[140+op]= DX7Par[13+(5-op)*21]*32;     //Rate Key
                     XFM2parL[159+op]= DX7Par[14+(5-op)*21]*64;     //AMS
                     XFM2parL[39+op]= DX7Par[15+(5-op)*21]*32;      //Velo Sens
                     XFM2parL[33+op]= DX7Par[16+(5-op)*21]*256/100; // LEVEL
                     // MODE DX7Par[17..] on DX7 1bit per Operator => XFM2 bits set in XFM2parL[14]
                     mode |= DX7Par[17+(5-op)*21] << (op);
                     XFM2parL[15+op]= DX7Par[18+(5-op)*21]*8;       // RATIO
                     XFM2parL[21+op]= DX7Par[19+(5-op)*21]*256/100; // RATIO FINE
// Check!!
                     XFM2parL[27+op]= 128+(DX7Par[20+(5-op)*21]-7);  // Pitch FINE  neutral   DX7 (0-14)  7 = XFM2 128
// CHeck!!
                 }
                 XFM2parL[13]=(DX7Par[136]==1) ? 63 : 0;
                 XFM2parL[14]=mode;
                 XFM2parL[134]= DX7Par[126]*256/100;  // R1
                 XFM2parL[135]= DX7Par[127]*256/100;  // R2
                 XFM2parL[136]= DX7Par[128]*256/100;  // R3
                 XFM2parL[137]= DX7Par[129]*256/100;  // R4
                 XFM2parL[130]= DX7Par[130]*256/100;  // L1
                 XFM2parL[131]= DX7Par[131]*256/100;  // L2
                 XFM2parL[132]= DX7Par[132]*256/100;  // L3
                 XFM2parL[133]= DX7Par[133]*256/100;  // L4
                 XFM2parL[13]=(DX7Par[136]==1) ? 63 : 0;  //SYNC
                 XFM2parL[151]= DX7Par[137]*256/100;  // LFO SPEED
                 XFM2parL[154]= DX7Par[138]*256/100;  // LFO FADE/DELAY
                 XFM2parL[149]= DX7Par[139]*256/100;  // PITCH MOD PMD??
                 XFM2parL[150]= DX7Par[140]*256/100;  // AMP MOD   AMD??
                 XFM2parL[152]= DX7Par[141];          // LFO SYNC
                 XFM2parL[153]=(DX7Par[142]==1) ? 3 : (DX7Par[142]==3) ? 1 : DX7Par[142] ; // LFO WAVE
                 // PITCH MOD SENSITIVITY  VOICE[143]
                 XFM2parL[174]= DX7Par[144];  // TRANSPOSE

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
                     jHead = jHead + "\t\"Creator\": \"Design.Thoughtz.eu\",\n";
                     jHead = jHead + "\t\"date\": \"" + strDate + "\",\n";
                     jHead = jHead + "\t\"hash\": \"" + Integer.toHexString((int) hash) + "\",\n";
                     jHead = jHead + "\t\"parameters\": [\n";
                     writer.write(jHead);
                     for (int k = 0; k < 511; k++) {
                         writer.write("\t\t{ \"Par#\": " + k + " , \"Value\": " + Byte.toUnsignedInt(XFM2parB[k]) + " } ,\n");
                     }
                     writer.write("\t\t{ \"Par#\": " + 511 + " , \"Value\": " + Byte.toUnsignedInt(XFM2parB[511]) + " }\n");
                     writer.write("\t]\n");

                     //Extra Dump
                     writer.write("\t\"dump\": [");
                     for (int k = 0; k < 512; k++) {
                       if (k>0) {
                         writer.write(",");
                       }
                       writer.write(Integer.toString(Byte.toUnsignedInt(XFM2parB[k])));
                     }
                     writer.write("]\n}\n");

                     writer.flush();
                     System.out.println("Saved Program to: " + fJson );
                 }
             }
         }
     } catch (IOException ex) {
         ex.printStackTrace();
     }
 }
}
