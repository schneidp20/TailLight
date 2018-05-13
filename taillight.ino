#include <Adafruit_NeoPixel.h>
#include <ArrayConstants.h>
#include <BlinkLed.h>
#include <CascadeLed.h>

Adafruit_NeoPixel lstrip = Adafruit_NeoPixel(40, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rstrip = Adafruit_NeoPixel(40, 3, NEO_GRB + NEO_KHZ800);
const byte R = 255;
const byte G = 255;
const byte B = 255;
const byte RT = 155;
const byte GT = 155;
const byte BT = 155;
const byte LEFTPIN = 3;
const byte BRAKEPIN = 5;
const byte RIGHTPIN = 7;

const byte maxrow = 5;
const byte maxcol = 8;
byte Rightpix[MAXROW][MAXCOL] = {
  { 0,  1,  2,  3,  4,  5,  6,  7},
  { 8,  9, 10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 27, 28, 29, 30, 31},
  {32, 33, 34, 35, 36, 37, 38, 39}
};
CascadeLed RightLed = CascadeLed(&rstrip, &Rightpix, maxrow, maxcol, RT, GT, BT, 80, 900);

byte Leftpix[MAXROW][MAXCOL] = {
  {32, 33, 34, 35, 36, 37, 38, 39},
  {24, 25, 26, 27, 28, 29, 30, 31},
  {16, 17, 18, 19, 20, 21, 22, 23},
  { 8,  9, 10, 11, 12, 13, 14, 15},
  { 0,  1,  2,  3,  4,  5,  6,  7}
};
CascadeLed LeftLed = CascadeLed(&lstrip, &Leftpix, maxrow, maxcol, RT, GT, BT, 80, 900);

byte  maxstop  = 25;
byte StopPix[MAXSINGLEROW] =  {
  3,  4, 5, 6, 7,
  11, 12, 13, 14, 15,
  19, 20, 21, 22, 23,
  27, 28, 29, 30, 31,
  35, 36, 37, 38, 39
};
BlinkLed LStopLed = BlinkLed(&lstrip, &StopPix, maxstop, R, G, B, 19);
BlinkLed RStopLed = BlinkLed(&rstrip, &StopPix, maxstop, R, G, B, 19);

byte  maxrun  = 7;
byte Runpix[MAXSINGLEROW] = {30, 14, 36, 27, 19, 11, 4};
//byte Runpix[MAXSINGLEROW] = {29, 13, 35, 26, 18, 10, 3};
BlinkLed LRunLed = BlinkLed(&lstrip, &Runpix, maxrun, R, G, B, 0); // freq not used
BlinkLed RRunLed = BlinkLed(&rstrip, &Runpix, maxrun, R, G, B, 0); // freq not used

void setup() {
  Serial.begin(9600);
  lstrip.begin();
  lstrip.show();
  rstrip.begin();
  rstrip.show();
}

void loop() {
  byte leftpin = (analogRead(LEFTPIN) > 50);
  byte brakepin = (analogRead(BRAKEPIN) > 50);
  byte rightpin = (analogRead(RIGHTPIN) > 50);

  // animate or clear the turn signals
  // PsudoOn is true when pin is high or between turn signal blinks (pin is actually low)
  bool lPsudoOn = LeftLed.Blink(leftpin);
  bool rPsudoOn = RightLed.Blink(rightpin);

  // animate or clear the brake lights
  LStopLed.Blink(brakepin);
  RStopLed.Blink(brakepin);

  // only turn on running lights.  Let the overlays turn it off
  // Clear will interfere with overlapping lights
  if (!lPsudoOn && !brakepin) LRunLed.Set(true);
  if (!rPsudoOn && !brakepin) RRunLed.Set(true);

}


