#include <Adafruit_NeoPixel.h>
//#include <StripPatterns.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 10 // Pin for led strip
int nPixels = 132;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nPixels, PIN, NEO_GRB + NEO_KHZ800);
int analogPin=A0;
int strobePin=2;
int resetPin=9;
int spectrumValue[7];
int filter = 80;
int waitForEQdelay = 30; // 30 ms as in the sheet.



void setup() {
        #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  Serial.begin(9600); // Just for debugging, will be disabled.
  pinMode(analogPin, INPUT);  //defines analog pin A0 as an Input
  pinMode(strobePin, OUTPUT); //defines strobe pin 2 as Output
  pinMode(resetPin, OUTPUT);  //defines reset pin 3 as Output
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
  

  strip.begin();
  strip.setBrightness(200);
  strip.show();

}

void loop() {
  // if hexvalue == something, swap to different mode and reset hex to deafult value;
  // perhaps save hexvalue as previousHex in order to adjust brightness of leds.
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW); // restarts output of multiplexer.
  for(int i =0; i<7; i++){
    digitalWrite(strobePin, LOW);
    delayMicroseconds(waitForEQdelay);
    spectrumValue[i]=analogRead(analogPin);
    if (spectrumValue[i]<filter){spectrumValue[i] = 0;}
    spectrumValue[i]=map(spectrumValue[i],0,1023,0,255);
    digitalWrite(strobePin, HIGH);
  }
  for(int i=0; i<44; i++){ //OBS!! Frekvensområdet för spectrumValue har random initiation,
    //dvs ibland börjar basen på 3 istället för 0, men det stegar alltid uppåt rätt
    // ir-sensor.read(hex);
    strip.setPixelColor(i,spectrumValue[0],0,0);
    strip.setPixelColor(i,spectrumValue[1],0,0);
    //strip.setPixelColor(i+44,0,spectrumValue[3],0);
    strip.setPixelColor(i+44,0,spectrumValue[4],0);
    strip.setPixelColor(i+88,0,0,spectrumValue[5]);
    strip.setPixelColor(i+88,0,0,spectrumValue[6]);
  }
strip.show();
}

void blue(int brightness){
  for(int i=0; i<nPixels; i++){
    strip.setPixelColor(i,0,0,brightness);
  }
  strip.show();
}

void red(int brightness){
  for(int i=0; i<nPixels; i++){
    strip.setPixelColor(i,brightness,0,0);
  }
  strip.show();
    /*while(waiting for input){
   * scan for input;
   * }
   */
}

void green(int brightness){
  for(int i=0; i<nPixels; i++){
    strip.setPixelColor(i,0,brightness,0);
  }
  strip.show();
  /*while(waiting for input){
   * scan for input;
   * }
   */
}

void inputInterpreter(int hex){
  // interpret what command is executed by user.
  // Probably switch statement of all possible commands to the arduino
  // brightnessUp{} 
  // brightnessDown{}
  // blue{}
  // red{}
  // green{}
  // purple{}
  // default: do nothing
  
}


