// testet ob der LED Streifen auch funktioniert. 
#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 23
#define DATA_PIN 4
#define NUM_COLORS 5
#define TONE_PIN 0
#define COLOR_RED CRGB::Red  
#define COLOR_BLUE CRGB::Blue  
#define SIREN_SPEED 300  // Geschwindigkeit in ms

#define FLASH_DURATION 80   // Blitzdauer in ms
#define PAUSE_DURATION 40   // Pause zwischen Blitzen
#define SIDE_SWITCH_DELAY 3 // Anzahl Blitze pro Seite
#define SOUND_DURATION SIDE_SWITCH_DELAY * (PAUSE_DURATION + FLASH_DURATION)


// array of leds
CRGB leds[NUM_LEDS];
bool sirenPhase = false;
uint8_t activeSide = 0;     // 0 = links, 1 = rechts
uint8_t flashCount = 0;
uint32_t lastUpdate = 0;
bool ledState = false;



int g_Brightness = 255;   



class Drawer{
    private:
    byte marqueeHue = 4;
    int marqueeScroll = 0;
    uint32_t lastUpdate = 0;


    public:
    void DrawTwinkle()
    {
        FastLED.clear(false);

        const CRGB TwinkleColors [NUM_COLORS] = 
        {
            CRGB::Red,
            CRGB::Blue,
            CRGB::Purple,
            CRGB::Green,
            CRGB::Yellow
        };

        for (int i=0; i<NUM_LEDS/4; i++) 
        {
            leds[random(NUM_LEDS)] = TwinkleColors[random(0, NUM_COLORS)];
            FastLED.show(g_Brightness);
            delay(200);
        }
    }


    void DrawMarqueeMirrored()
    {        
        (marqueeHue < 255) ? marqueeHue+=4:0;
        byte newHue = marqueeHue;
        
        CRGB c;
        for (int i = 0; i < (NUM_LEDS + 1) / 2; i ++)
        {
            leds[i].setHue(newHue).fadeToBlackBy(100);
            leds[NUM_LEDS - 1 - i].setHue(newHue).fadeToBlackBy(100); 
            // die set anweisung verbraucht entweder zuviel Speicher oder
            // erzeugt einne Überlauf. deswegen im Hauptprogramm herausgenommen
            (newHue < 255) ? newHue+=8: newHue=0;
        }
        
        leds[random(NUM_LEDS)].setColorCode(CRGB::White).maximizeBrightness();                         
    }

    void policeBlueFlash()
    {
        uint32_t now = millis();
        static uint16_t toneFreq = 780;

        if (now - lastUpdate > (ledState ? PAUSE_DURATION : FLASH_DURATION))
        {
            ledState = !ledState;

            if (ledState)
            {
                // Aktiviere LEDs der aktuellen Seite
                for (uint8_t i = 0; i < NUM_LEDS; i++)
                {
                    bool isLeftSide = i < NUM_LEDS / 2;
                    leds[i] = ((activeSide == 0 && isLeftSide) || (activeSide == 1 && !isLeftSide)) ? CRGB::Blue : CRGB::Black;
                }
            }
            else
            {
                FastLED.clear();
                flashCount++;

                if (flashCount >= SIDE_SWITCH_DELAY)
                { // wechsle Seiten
                    activeSide = !activeSide;
                    flashCount = 0;
                    toneFreq = (toneFreq == 440) ? 780 : 440;
                }
                tone(TONE_PIN, toneFreq);
            }
            lastUpdate = now;
        }
    }
};


Drawer drawer;


void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    drawer = Drawer();
    
}

void DrawComet()
{
    const byte fadeAmt = 128;
    const int cometSize = 1;
    const int deltaHue  = 4;

    static byte hue = HUE_RED;
    static int iDirection = 1;
    static int iPos = 0;

    hue += deltaHue;

    iPos += iDirection;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        leds[iPos + i].setHue(hue);
    
     //Randomly fade the LEDs
     for (int j = 0; j < NUM_LEDS; j++)
         if (random(10) > 5)
             leds[j] = leds[j].fadeToBlackBy(fadeAmt);  

    delay(60);
}



void loop() { 

  drawer.policeBlueFlash();  
  delay(50);
  FastLED.show();
}