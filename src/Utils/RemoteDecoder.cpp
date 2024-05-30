#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <atRcRwitch.h>

#define INTERRUPT_PIN PCINT1  // Interupt ist PB1 gemäß dem Schaltplan
#define INT_PIN PB1           // Interrupt-Pin nach Wahl: PB1 (wie PCINT1) - Pin 6
#define LED_PIN PB3           // PB4 - Pin 3
#define CONTROL_LED PB4
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit


boolean volatile irFired=false;
boolean lightsOn =false;
unsigned long startTime = 0;
unsigned int currentCode=0;

const unsigned int taste1 = 32936;
const unsigned int taste2 = 32932;

byte started = false;
RCSwitch mySwitch = RCSwitch();



void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(CONTROL_LED, OUTPUT);
  cli();                            
  PCMSK |= (1 << INTERRUPT_PIN);    
  GIMSK |= (1 << PCIE);             
  pinMode(INT_PIN, INPUT_PULLUP);   
  mySwitch.enableReceive(0);
  sei();                            
}

void blinkControll(int times, int  unsigned frequence)
{  
  for(int i=0; i< times;i++){
    digitalWrite(CONTROL_LED, HIGH);
    delay(frequence);
    digitalWrite(CONTROL_LED, LOW);
    delay(frequence);
  }

}

ISR(PCINT_VECTOR)
{ 
   mySwitch.handleInterrupt();
}

void blinkZiffer(unsigned int zahl){
  int ziffer=0;
  while (zahl != 0) {
    delay(1000);
    blinkControll(3,50);
    delay(1000);
    ziffer = zahl % 10;    
    blinkControll(ziffer,300);
    zahl /= 10;
    delay(500);
  }
}

void blinkBinar(unsigned int zahl){
  for (int i = 0; i < sizeof(int) * 8; ++i) {
        int bit = (zahl >> i) & 1;
        if (bit==0){
          blinkControll(1,100);          
        }else{
          blinkControll(2,100);   
        }
        delay(2000);
    }
}

void loop() {
  if (mySwitch.available()) {    
    unsigned int code= mySwitch.getReceivedValue();    
    currentCode = code;  
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);      
    blinkZiffer(code);     
    delay(2000);  
  }

}

   
   
  
  


