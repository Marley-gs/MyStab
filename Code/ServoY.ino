#include<Wire.h>
#include<Servo.h>

Servo servoX;
Servo servoY;

float val_x;
float val_y;

const int MPU_addr=0x68;  //adresse I2C du composant, si AD0=5V(HIGH) elle devient 0x69
float Acc_X, Acc_Y, Acc_Z, Gy_X, Gy_Y, Gy_Z ; 
float angle_x, angle_y, angle_z;  //variables qui stockent les 3 accélérations


void setup() {
  
  Serial.begin(9600);

  servoX.attach(10);

  servoY.attach(9);
  //servoY.write(90);
  delay(25);  

  
  Wire.begin();   
  Wire.beginTransmission(MPU_addr);  //On indique que l'on veut communiquer avec l'accéléromètre
  Wire.write(0x6B);  //On le réveille
  Wire.write(0);
  Wire.endTransmission(true);  //On arrete la communication I2C pour libérer le BUS 
 

}

void loop() {
  Wire.beginTransmission(0x68); //On demande l'accès au premier registre
  Wire.write(0x3B); //On commence par le registre 0x3B
  Wire.endTransmission(false);   //envoie de Restart(nouvelle trame)
  Wire.requestFrom(0x68,12,true);  //demande a l'accéléromètre de lire 6 registres
  
  Acc_X=(Wire.read()<<8|Wire.read());
  Acc_Y=(Wire.read()<<8|Wire.read());
  Acc_Z=(Wire.read()<<8|Wire.read());

  Gy_X=(Wire.read()<<8|Wire.read());  
  Gy_Y=(Wire.read()<<8|Wire.read());  
  Gy_Z=(Wire.read()<<8|Wire.read()); 

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(Acc_X);
  Serial.print(" | Y = "); Serial.print(Acc_Y);
  Serial.print(" | Z = "); Serial.println(Acc_Z); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(Gy_X);
  Serial.print(" | Y = "); Serial.print(Gy_Y);
  Serial.print(" | Z = "); Serial.println(Gy_Z);
  Serial.println(" ");
  

  angle_x=(atan((Acc_X/16384)/sqrt(pow((Acc_Y/16384),2)+ pow((Acc_Z/16384),2)))*180/PI);
  angle_y=(atan((Acc_Y/16384)/sqrt(pow((Acc_X/16384),2)+pow((Acc_Z/16384),2)))*180/PI);

  Serial.print("angle_x= ");Serial.print(angle_x);
  Serial.print(" |angle_y= ");Serial.println(angle_y);

  val_x=(angle_x+90);
  val_y=(angle_y+90);
  //val= map(val1,-90,90,179,0);
  //val = map (val1,0,179, 1000,2000);

  Serial.println(val_x);
  Serial.println(val_y);
  delay(150);
  servoX.write(val_x);
  servoY.write(val_y);
    

  


  
  
}
