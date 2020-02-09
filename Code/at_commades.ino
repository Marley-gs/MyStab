#include <SoftwareSerial.h>

int TX=10;
int RX=11;

SoftwareSerial blueT(RX,TX);

void setup(){
  Serial.begin(9600);
  Serial.println("Bonjour -Pret pour les commandes AT"); 
  blueT.begin(9600);
}

void loop(){
  while (blueT.available()) {
    Serial.print(char(blueT.read())); }
  while (Serial.available()) { 
    blueT.write(char(Serial.read())); }
}
