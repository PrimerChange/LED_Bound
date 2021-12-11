#include <WS2812FX.h>

#define LED_COUNT 30
#define LED_PIN D2

#define ANALOG_PIN A0
#define ANALOG_THRESHOLD 512

#define TIMER_MS 5000

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long last_change = 0;
unsigned long now = 0;

void Led_control(int a)
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    if (a > i)
    {
      ws2812fx.setPixelColor(i, 0xff * (LED_COUNT - i) / LED_COUNT, 0xff * i / LED_COUNT, 0x00);
    }
    else
    {
      ws2812fx.setPixelColor(i, (uint32_t)0x000000);
    }
  }
  ws2812fx.show();
}

int LED_count(float a)
{
  return (a / ANALOG_THRESHOLD) * LED_COUNT;
}

void setup()
{
  Serial.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x007BFF);
  // ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();
}

void loop()
{
  int This;
  ws2812fx.service();
  ws2812fx.setColor(0x00);
  This = LED_count((float)analogRead(ANALOG_PIN));
  Led_control(This);
}
