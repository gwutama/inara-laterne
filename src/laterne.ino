#include <FastLED.h>

#define BUTTON_PIN  7
#define LED_PIN     5
#define NUM_LEDS    15
#define CHIPSET     WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  255
#define FPS         30

CRGB leds[NUM_LEDS];
uint8_t startHue = 0;
uint8_t toggle = 0;
bool isSolidColorRefreshed = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT);

  delay(3000); // power-up safety delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  // FastLED.setMaxRefreshRate(1000);
  FastLED.setBrightness(BRIGHTNESS);
  // FastLED.setMaxPowerInMilliWatts(1500);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == 0) {
    delay(10);

    if (digitalRead(BUTTON_PIN) == 0) {
      delay(10);

      if (digitalRead(BUTTON_PIN) == 0) {
        toggle = (toggle + 1) % 4;

        if (toggle != 0) {
          isSolidColorRefreshed = false;
        }

        while (digitalRead(BUTTON_PIN) == 0){
          delay(10);      
        }
      }
    }
  }

  if (toggle == 0) {
    fill_rainbow(leds, NUM_LEDS, --startHue);
    FastLED.show(1000 / FPS);     
    FastLED.delay(20);  
    isSolidColorRefreshed = false;    
  } else if (toggle == 1 && !isSolidColorRefreshed) {  
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();           
    isSolidColorRefreshed = true;
  } else if (toggle == 2 && !isSolidColorRefreshed) {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();           
    isSolidColorRefreshed = true;    
  } else if (toggle == 3 && !isSolidColorRefreshed) {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();           
    isSolidColorRefreshed = true;    
  }
}
