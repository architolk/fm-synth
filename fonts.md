# Fonts

De Adafruit library geeft de mogelijkheid om nieuwe fonts toe te voegen:

https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts

Om deze te gebruiken moet je eerst de git repo van Adafruit GFX ophalen:

```
git clone git@github.com:adafruit/Adafruit-GFX-Library.git
```

Vervolgens ga je naar de `fontconvert` map en compileer je de code:

```
make
```

Tenslotte zorg je er voor dat de executable `fontconvert` en het truetype bestand in dezelfde directory staan, en kies je:

```
fontconvert myfont.ttf 12 > myfont12pt7b.h
```

Dit zorgt voor een bitmap font ter grootte van 12pt, vergelijkbaar kun je ook kleinere en grotere bitmaps maken.

Voor de synth fonts gebruiken we het volgende font: http://www.fonts101.com/fonts/view/Graffiti/56682/Dungeon
