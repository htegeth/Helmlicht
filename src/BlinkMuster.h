#include <FastLED.h>

#define NUM_LEDS 23
#define LED_FRAGMENT NUM_LEDS / 3
#define BLINK_DELAY_MAIN 500
#define BLINK_DELAY_SUB BLINK_DELAY_MAIN / (LED_FRAGMENT*2)
#define RIGHT_BEGIN LED_FRAGMENT-1
#define FADEAMT 128
#define TONE_PIN 0
#define COMET_SIZE 1
        
class BlinkMuster
{
     private:        
        const int8_t deltaHue  = 4;    
        CRGB* leds;

        byte hue = HUE_RED;
        int8_t iDirection = 1;
        int8_t iPos = 0;

        byte marqueeHue = 4;
        byte fade = 0;


    public:
        BlinkMuster();
        void setLeds(CRGB* leds);               

        void drawComet();
        void drawKitt();
        void drawHollywood();
        void drawFullRed(uint8_t brightness);

        void setBlinkLeft()  {blinkCommon(true);};
        void setBlinkRight() {blinkCommon(false);};
        void blinkCommon(bool isLeft); 
                

};