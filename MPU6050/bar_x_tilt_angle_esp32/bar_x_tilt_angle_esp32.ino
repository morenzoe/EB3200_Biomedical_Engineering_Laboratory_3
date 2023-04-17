/*
 * Program Grafik Sudut Kemiringan Sumbu X 0-180 drj
 *
 * Koneksi Pin
 * ESP32 | MPU6050
 * ---------------
 *  22   |  SCL
 *  21   |  SDA
 *  GND  |  GND
 *  3V3  |  VCC
 *  
 *  Referensi
 *  how2electronics, “Measure Tilt Angle Using MPU6050 Gyro/Accelerometer & Arduino” Newton, A., Sep. 16, 2022. 
 *  Accessed: Apr. 18, 2023. [Online]. 
 *  Available: https://how2electronics.com/measure-tilt-angle-mpu6050-arduino/
 */

#include<Wire.h>
 
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
//double y;
//double z;
 
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
}
void loop(){
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
//y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
//z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
if (x>=0&&x<90){
  if(x>=0&&x<10){
    Serial.println("|o| | | |[ ]| | | | |");
  } else if(x>=10&&x<20){
    Serial.println("| |o| | |[ ]| | | | |");
  } else if(x>=20&&x<30){
    Serial.println("| | |o| |[ ]| | | | |");
  } else if(x>=30&&x<40){
    Serial.println("| | | |o|[ ]| | | | |");
  } else if(x>=40&&x<50){
    Serial.println("| | | | |[o]| | | | |");
  } else if(x>=50&&x<60){
    Serial.println("| | | | |[ ]|o| | | |");
  } else if(x>=60&&x<70){
    Serial.println("| | | | |[ ]| |o| | |");
  } else if(x>=70&&x<80){
    Serial.println("| | | | |[ ]| | |o| |");
  } else if(x>=80&&x<90){
    Serial.println("| | | | |[ ]| | | |o|");
  }
 }
delay(40);
}
