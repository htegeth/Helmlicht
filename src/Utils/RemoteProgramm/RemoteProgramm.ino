/*
 Wird verwendet um die Fernbedienung zu programmieren.
 Wichtig ist es die Fernbedienung ganz nah an den  Sender zu halten. 
 Die Fernbedienung darf den Sender sogar berühren, sonst frunktioniert die Übertragung nicht.

 Die Fernbedienung sollte vorher in den Programmiermodus gebracht werden. Bei den meisten Modellen mit vier Knöpfen geht das so:
 1. Knopf 1 (oder A) und 2 (B) gleichzeigtig drücken bis die LED blinkt und ausgeht
 2. Knopf 2 (oder B) drei mal hintereinander drücken. Dann fackert die LED
 3. Unter mySwitch.send(n,24) einen der Werte eintragen (2,5,10,20)
 4. Knopf 1-4 (A-D) drücken und halten bis die LED nicht mehr blinkt sondern flackert.
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(10);
}

void loop() {
  mySwitch.setProtocol(1);
  mySwitch.send(10, 8);
  delay(100);

}