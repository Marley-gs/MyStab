#include <SoftwareSerial.h>
#include<Servo.h>
int TX=10;
int RX=11;
int SERVO=9;
Servo monServo;

char Data;
SoftwareSerial blueT(RX,TX);

void setup(){
  Serial.begin(9600); 
  blueT.begin(9600);
  monServo.attach(9);
  monServo.write(0); //position à 0° au depart
}

void loop(){
  if (blueT.available()) {
    Serial.println(blueT.read());
    
    monServo.write(blueT.read());
  }
}
