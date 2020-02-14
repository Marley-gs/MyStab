#include <SoftwareSerial.h>
#include<Servo.h>
int TX=10;
int RX=11;
int SERVO=9;
int valeur;
Servo monServo;

int inv;
char Data;
SoftwareSerial blueT(RX,TX);

void setup(){
  Serial.begin(9600); 
  blueT.begin(9600);
  monServo.attach(9);
  
}

void loop(){
  if (blueT.available()) {
    Data=blueT.read();
    if (Data=='A'){
      valeur=blueT.parseInt();
      inv=map(valeur,80,105,105,80);
      
      Serial.println(inv);
      monServo.write(inv);}     
    }
}
