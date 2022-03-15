//setup library
#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>
Bounce button = Bounce();
#define BOUNCE_PIN 2
Adafruit_NeoPixel strip(24, 0, NEO_GRB + NEO_KHZ800);

int numGrid = 24;
int numFrames = 4;
int state = 0;
int buttonPin = 1;
boolean prevButtonState = false;
int stripIndex = 0;
int ledState = LOW;

unsigned long startTime = millis();;
unsigned long endTime;
int intervalTime = 50;

char index[24] {
  // Insert Index Values Here
        0,
       1, 2,
      3, 4, 5,
     6, 7, 8, 9,
  10, 11, 12, 13, 14,
    15, 16, 17, 18,
       19, 20,
       21, 22,
         23,
};

char colors[3][3] {
  //yellow
  {255, 255, 0},
  //dark red
  {204, 0, 0},
  //light blue
  {0, 0, 255},
};

char frames[4][24] {
  //frame no. 1
  {
        0,
       0, 0,
      0, 0, 0,
     0, 0, 0, 0,
    2, 1, 2, 1, 2,
     0, 0, 0, 0,
        0, 0,
        0, 0,
         0,
 
  },
  //frame no. 2
  {
         2,
        2, 2,
       1, 1, 1,
      1, 0, 0, 1,
     1, 0, 0, 0, 1,
      1, 0, 0, 1,
         2, 2,
         2, 2,
           2,


  },

  //frame no. 3
  {
         1,
        1, 1,
       1, 1, 1,
      1, 1, 1, 1,
     1, 0, 0, 0, 1,
      1, 1, 1, 2,
         1, 1,
         1, 1,
           1,

  },
  //frame no. 4
  {
          2,
         2, 2,
       2, 2, 2,
      2, 1, 1, 2,
     2, 0, 0, 0, 2,
      2, 1, 1, 2,
         2, 2,
         2, 2,
          2,

  },


};

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
  button.attach(1);
  button.interval(5);
}

void loop() {
  button.update();
  strip.clear();
  strip.show();
  // put your main code here, to run repeatedly:
  Serial.println(state);

  if (button.rose()) {
    state = (state + 1) % 3;
    strip.clear();
    strip.show();
    startTime = millis();
  }
  switch (state) {
    case 0:
      strip.clear();
      strip.show();
      break;

    case 1:
      //repeats frame animation
      //and updates color parameters
        for (int i = 0; i < numGrid; i++) {
          int whichLED = i;
          int whichIndex = index[whichLED];
          int whichColor = frames[numFrames][whichLED];
          //defines colors
          int r = colors[whichColor][0];
          int g = colors[whichColor][1];
          int b = colors[whichColor][2];

          strip.setPixelColor(whichIndex, r, g, b);
        }
        strip.show();
        
        int timer = 1000;
        if (millis() - startTime > timer) {
        startTime = millis();
        numFrames = (numFrames + 1) % 4;
        strip.clear();
        strip.show();
      }
      break;
  }
}
