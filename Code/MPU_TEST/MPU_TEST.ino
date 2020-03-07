#include "Wire.h"  // Arduino Wire library
#include "I2Cdev.h"  //Installer ces 2 librairies
#include "MPU6050.h"
#include "math.h"
#include<Servo.h>

// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;  //mesures brutes
int16_t gx, gy, gz;
uint8_t Accel_range;
uint8_t Gyro_range;
float angle=0;

Servo servoY;
Servo servoX;
float val1;

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

  servoX.attach(10);
  servoX.write(90);
  servoY.write(9);
  servoY.write(90);
           
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angle=0.98*(angle+float(gy)*0.01/131) + 0.02*atan2((double)ax,(double)az)*180/PI;
  //angle2 = 0.98*(angle2+float(gx)*0.01/131) + 0.02*atan2((double)ay,(double)az)*180/PI;
  Serial.println(angle); 
  delay(10);

  //val1 = map (angle,0,180, 1000,2000);
  //val2 = map (val_y,0,180, 1000,2000);
  //Serial.println("valeur=");Serial.print(val1);
  
  //Serial.println(val2);
  
  servoY.write(angle);
  //servoX.write(angle2);
  
  //servoY.write(val2);
}
