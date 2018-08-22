#include <FastLED.h>

#define LED_PIN     4
#define NUM_LEDS   150
#define BRIGHTNESS  55
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;

const int LIGHT_PIN = A0; // Pin connected to voltage divider output
const int GND_PIN = 6; // Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 4660.0; // Measured resistance of 3.3k resistor

// Set this to the minimum resistance require to turn an LED on:
const float DARK_THRESHOLD = 16000.0;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
  pinMode(LIGHT_PIN, INPUT);
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
  //Serial.begin(9600);

}


void loop()
{    
 int lightADC = analogRead(LIGHT_PIN);
 //Serial.print("Light");
// Serial.println(lightADC);
  if (lightADC <250)
  {
    // Use the ADC reading to calculate voltage and resistance
    float lightV = lightADC * VCC / 1023.0;
    float lightR = R_DIV * (VCC / lightV - 1.0);
    if (lightR >= DARK_THRESHOLD)
    {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            
            FillLEDsFromPaletteColors( startIndex);
            
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);    
      }
  }
  else{
    wipeLEDColors();
     FastLED.show();
     FastLED.delay(1000 / UPDATES_PER_SECOND); 
  }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void wipeLEDColors()
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}









