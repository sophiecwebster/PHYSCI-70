#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>

#define PIN        9 
#define NUMPIXELS 10

CapacitiveSensor slider = CapacitiveSensor(2,3);
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(20); 
  slider.set_CS_AutocaL_Millis(0xFFFFFFFF);
  
  Serial.begin(9600);
}

void loop() {
  strip.clear();
  long start = millis();
  long touch = slider.capacitiveSensor(9000);

  int val = analogRead(touch);
  Serial.println(val);
  Serial.print(touch);

  byte r, g, b;
  r = random(256);
  g = random(256-r);
  b = (255-r-g);

  if (touch >= 0 && touch < 400) { strip.clear(); }
  if (touch >= 5000) { strip.setPixelColor(1, strip.Color(r, g, b));
  strip.show(); }
  if (touch >= 5250) { strip.setPixelColor(2, strip.Color(255, 0, 0));
  strip.show(); }
  if (touch >= 5500) strip.setPixelColor(3, strip.Color(255, 100, 0));
  strip.show();
  if (touch >= 5750) strip.setPixelColor(4, strip.Color(225, 255, 0));
  strip.show();
  if (touch >= 6000) strip.setPixelColor(5, strip.Color(0, 225, 0));
  strip.show();
  if (touch >= 6250) strip.setPixelColor(6, strip.Color(0, 0, 225));
  strip.show();
  if (touch >= 6500) strip.setPixelColor(7, strip.Color(75, 0, 255));
  strip.show();
  if (touch > 6600) strip.setPixelColor(8, strip.Color(148, 0, 211));
  strip.show();
  if (touch >= 6700) strip.setPixelColor(9, strip.Color(r, g, b));
  strip.show();

  delay(10);
}
