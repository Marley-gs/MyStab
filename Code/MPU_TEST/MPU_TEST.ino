

#include "Wire.h"  // Arduino Wire library
#include "I2Cdev.h"  //Installer ces 2 librairies
#include "MPU6050.h"
#include "math.h"
#include<Servo.h>

#include <SoftwareSerial.h>
int TX=10;
int RX=11;
int SERVO=3;
int valeur;
Servo monServo;

int inv;
char Data;
SoftwareSerial blueT(RX,TX);


MPU6050 accelgyro;

int16_t ax, ay, az;  //mesures brutes
int16_t gx, gy, gz;
uint8_t Accel_range;
uint8_t Gyro_range;
float angle_x=0;
float angle_y=0;
float val1;
float val2;
float map_y;
float valeur_fin_X;
float valeur_fin_Y;


Servo servoX;
Servo servoY;


void setup() {
  Wire.begin();  //I2C bus
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB (LEONARDO)
  }

  // initialize device
  Serial.println("Initialisation I2C...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Test de la conection du dispositif ...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection reussie" : "MPU6050 connection echec");
  delay(1000);

  servoX.attach(6);
  servoX.write(90);

  servoY.attach(5);
  servoY.write(90);

  delay(100);

  blueT.begin(9600);
  monServo.attach(3);
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angle_y=0.98*(angle_y+float(gy)*0.01/131) + 0.02*atan2((double)ax,(double)az)*180/PI;
  angle_x=0.98*(angle_x+float(gx)*0.01/131) + 0.02*atan2((double)ay,(double)az)*180/PI;
  
  Serial.print("angle_x");
  Serial.println(angle_x);

  val2= 90-angle_y;
  servoY.write(val2);

  val1 = angle_x+90;
  servoX.write(val1);


  if (blueT.available()) {
    Data=blueT.read();
    if (Data=='A'){
      valeur=blueT.parseInt();
      inv=map(valeur,80,105,105,80);
      
      Serial.println(inv);
      monServo.write(inv);}     
    }
}
