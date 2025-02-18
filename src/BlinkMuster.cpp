#include <BlinkMuster.h>

BlinkMuster::BlinkMuster()
{
}

void BlinkMuster::setLeds(CRGB *leds)
{
    this->leds = leds;
}

void BlinkMuster::blinkCommon(bool isLeft) {
    const int8_t startPos = isLeft ? (NUM_LEDS - LED_FRAGMENT) : RIGHT_BEGIN;
    const int8_t step = isLeft ? 1 : -1;
    const int toneFreqDirect = isLeft ? 300 : 200;

    const bool resetNeeded = isLeft 
        ? (iPos < startPos || iPos == NUM_LEDS)
        : (iPos >= LED_FRAGMENT || iPos < 0);

    if (resetNeeded) {
        FastLED.clear();
        FastLED.show();
        iPos = startPos;
        tone(TONE_PIN, 500, 50); 
        delay(100);
        tone(TONE_PIN, toneFreqDirect, 150);
        delay(500);
    }

    leds[iPos].setHue(HUE_ORANGE);
    iPos += step;
    FastLED.show();
    delay(80);
}

void BlinkMuster::drawComet()
{
    hue += deltaHue;
    iPos += iDirection;
    if (iPos == (NUM_LEDS - COMET_SIZE) || iPos == 0)
        iDirection *= -1;

    for (int i = 0; i < COMET_SIZE; i++)
        leds[iPos + i].setHue(hue);

    // Zufälliges Ausblenden der LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(10) > 5)
            leds[j] = leds[j].fadeToBlackBy(FADEAMT);
    FastLED.show();
    delay(60);
}

void BlinkMuster::drawKitt()
{    
    //Reset, falls die Positionswerte und die Direction nicht mehr passen
    if (iPos> NUM_LEDS || iPos< 0 || abs(iDirection)!= 1)
    {
        iPos=0;
        iDirection=1;
    }
    iPos += iDirection;
    if (iPos == (NUM_LEDS - 1) || iPos == 0)
        iDirection *= -1;

    FastLED.clear();
    leds[iPos].setHue(HUE_RED).fadeLightBy(0);
    if ((iPos + 1) < NUM_LEDS)
         leds[iPos + 1].setHue(HUE_RED).fadeToBlackBy(150);
    leds[iPos - 1].setHue(HUE_RED).fadeToBlackBy(150);
    FastLED.show();
    delay(43);
}

void BlinkMuster::drawHollywood()
{
    (marqueeHue < 255) ? marqueeHue+=4:0;
    byte newHue = marqueeHue;
    
    CRGB c;
    for (int i = 0; i < (NUM_LEDS + 1) / 2; i ++)
    {   
        leds[i]=  c.setHue(newHue);
        leds[NUM_LEDS - 1 - i]=  leds[i];
        (newHue < 255) ? newHue+=8: newHue=0;
    }    
    leds[random(NUM_LEDS)].setColorCode(CRGB::White).maximizeBrightness();   
    FastLED.show();
    delay(50);          
}

void BlinkMuster::drawFullRed(uint8_t brightness){
    for (int i=0; i< NUM_LEDS; i++)
    {
        leds[i] = CRGB::Red;
        leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    delay(50);  
}
