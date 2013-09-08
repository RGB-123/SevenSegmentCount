#include <Adafruit_NeoPixel.h>

// --5--
//|     |
//4     6
//|--0--|
//3     1
//|     |
// --2--
const uint16_t LedsPerSeg = 12;
const uint16_t TotalLeds = LedsPerSeg * 7+1; //+1 =Point
//                       A,B,C,D,E,F,G 
byte Digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                       { 0,1,1,0,0,0,0 },  // = 1
                       { 1,1,0,1,1,0,1 },  // = 2
                       { 1,1,1,1,0,0,1 },  // = 3
                       { 0,1,1,0,0,1,1 },  // = 4
                       { 1,0,1,1,0,1,1 },  // = 5
                       { 1,0,1,1,1,1,1 },  // = 6
                       { 1,1,1,0,0,0,0 },  // = 7
                       { 1,1,1,1,1,1,1 },  // = 8
                       { 1,1,1,0,0,1,1 }   // = 9 
                       };
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(TotalLeds, 6, NEO_GRB + NEO_KHZ800);

int ledPin = 13;
byte state = LOW; //our on/off switch
byte MaxBright = 16;

byte Count;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  toggleLedPin();
  
  for (byte n=0; n<10;++n){  
    if (n==8) {
        SetNumber(strip.Color(MaxBright, MaxBright, MaxBright), n,1); 
        delay(250);
        SetNumber(strip.Color(0, 0, 0), n,0);
        delay(250);
        SetNumber(strip.Color(MaxBright, MaxBright, MaxBright), n,1);
        delay(250);
        SetNumber(strip.Color(0, 0, 0), n,0);
        delay(250);
        SetNumber(strip.Color(MaxBright, MaxBright, MaxBright), n,1);
    } else {
        SetNumber(strip.Color(MaxBright, MaxBright, 0), n,1);
    }
    Serial.println(n);
    delay(250);
  }
}

void SetNumber(uint32_t c, byte Number, byte DP) {
  byte idx = 0;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    for (byte i=0; i<LedsPerSeg;++i){
      if (Digits[Number][segCount]==1){
        strip.setPixelColor(idx, c);
      } else {
        strip.setPixelColor(idx, 0);
      }
      ++idx;
    }
  
  if (DP == 1) {
    strip.setPixelColor(idx, c);
  }else {
    strip.setPixelColor(idx, 0);    
  }
  strip.show();
  }
}
void toggleLedPin(){
  // Some example procedures showing how to display to the pixels:
    if (state == LOW){
    state = HIGH;
  } else {
    state = LOW;
  }
  //toggle the LED based on our switch above
  digitalWrite(ledPin, state);
  }



