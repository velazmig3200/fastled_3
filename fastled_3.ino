
#include <FastLED.h>

#define LED_PIN 7
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
int lay = 10;
int lay2 = 1200;
int b1 = 95;

const int pixelCount = 10;
int frameCount[pixelCount];
int index[pixelCount];

//_______________________________________________colours
//_____________________hue red: 0, green: 85, blue: 170;
CHSV pink(250, 150, b1); // pink 250,150,255
CHSV warm(20, 255, b1);  // warm
CHSV white(0, 0, b1);    // white

void solidRGBA(int x, int y, int z, int a)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(x, y, z);
  }
  FastLED.setBrightness(a);
  FastLED.show();
}
// solid[show,r,g,b]
void solidSRGB(bool s, int x, int y, int z)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(x, y, z);
  }
  if (s == true)
  {
    FastLED.show();
  }
}
void colorTesting(char correctionType, int hue)
{
  /*
  correctionType {
    UncorrectedColor, TypicalLEDStrip,
    TypicalPixelString, TypicalSMD5050
  }
  color {
    [set color via any named HTML web color]
    examples:
    Red,
      DarkMagenta, DeepPink, DarkOrange, Orange, OrangeRed,
    Green,
      DarkGreen, Gold, Goldenrod, SeaGreen, LightSeaGreen, Teal, Yellow,
    Blue,
      BlueViolet, DodgerBlue, Aqua, DarkViolet, Indigo, MidnightBlue
    white
  }
  */

  hue = hue * (32 * 1.7);
  FastLED.setCorrection(correctionType);
  // white
  for (int i = 0; i < NUM_LEDS / 6; i++)
  {
    leds[i] = white;
  }
  leds[0] = CHSV(hue, 255, b1);
  FastLED.show();
  delay(lay2);
}

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  // test each led with white
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = white;
    FastLED.show();
    delay(lay);
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(lay / 2);
  }
  // set frameCount[] and index[] for pixelCount
  for (int i = 0; i < pixelCount; i++)
  {
    frameCount[i] = 0;
    index[i] = 0;
  }
}

int L1 = 1;
int S1[pixelCount];
void loop()
{
  // clear field
  //  solidSRGB(false, 10, 50, 50);
  solidSRGB(false, 0, 0, 0);
  // draw
  // pixel[
  //    pixelID,length,speed,
  //    r,g,b]
  pixel(
      0, L1, S1[0],
      50, 0, 0);
  pixel(
      3, L1, S1[3],
      0, 0, 50);
  pixel(
      1, L1, S1[1],
      50, 34, 0);
  pixel(
      2, L1, S1[2],
      50, 40, 0);
  pixel(
      4, L1, S1[4],
      0, 31, 0);
  //

  // draw
  FastLED.setBrightness(40);
  FastLED.show();
  // delay(10);
}

//_______________________body__________________________
// pixel[index[where is it on leds[]],color[rgb]]
// pixel[pixelID,length,speed,r,g,b]
void pixel(
    int pixelID, int l, int s,
    int r, int g, int b)
{
  // check current frameCount
  if (frameCount[pixelID] > s)
  {
    // reset frameCount, increment index if < NUM_LEDS
    frameCount[pixelID] = 0;
    if (index[pixelID] < NUM_LEDS)
    {
      index[pixelID]++;
    }
    else
    {
      index[pixelID] = 0;
      S1[pixelID] = random(3, 17);
    }
  }
  else
  {
    // increment frameCount
    frameCount[pixelID]++;
  }

  // draw
  draw(pixelID, l, r, g, b);
}
void draw(int pixelID, int l, int r, int g, int b)
{
  for (int i = 0; i < l; i++)
  {
    // if index < NUM_LEDS
    if (index[pixelID] + i < NUM_LEDS)
    {
      leds[index[pixelID] + i] = CRGB(r, g, b);
    }
    else
    {
      leds[(index[pixelID] + i) - NUM_LEDS] = CRGB(r, g, b);
    }
  }
}

void pixel1(
    int pixelID, int l, int s,
    int r, int g, int b)
{
  //"un-"zero-index pixelID for array
  pixelID = pixelID - 1;

  // check current frameCount
  if (frameCount[pixelID] > s)
  {
    // reset frameCount, increment index if < NUM_LEDS
    frameCount[pixelID] = 0;
    if (index[pixelID] < NUM_LEDS - 1 - pixelID)
    {
      index[pixelID]++;
    }
  }
  else
  {
    // increment frameCount
    frameCount[pixelID]++;
  }

  // draw
  draw1(pixelID, l, r, g, b);
}

void draw1(int pixelID, int l, int r, int g, int b)
{
  for (int i = 0; i < l; i++)
  {
    // if index < NUM_LEDS
    if (index[pixelID] + i < NUM_LEDS)
    {
      leds[index[pixelID] + i] = CRGB(r, g, b);
    }
  }
}
