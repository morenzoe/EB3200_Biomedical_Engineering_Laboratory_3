 /*
 * Program Bar Sudut Kemiringan Sumbu X 0-90 drj
 *
 * Koneksi Pin
 * ESP32 | MPU6050
 * ---------------
 *  22   |  SCL
 *  21   |  SDA
 *  GND  |  GND
 *  3V3  |  VCC
 *  
 * Koneksi Pin
 * ESP32 | MPS20N0040D
 * ---------------
 *  19   |  SCK
 *  18   |  OUT
 *  GND  |  GND
 *  3V3  |  VCC
 *  
 *  Referensi
 *  how2electronics, “Measure Tilt Angle Using MPU6050 Gyro/Accelerometer & Arduino” Newton, A., Sep. 16, 2022. 
 *  Accessed: Apr. 18, 2023. [Online]. 
 *  Available: https://how2electronics.com/measure-tilt-angle-mpu6050-arduino/
 */

#include<Wire.h>
#include <Q2HX711.h>
#include <Average.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
//double y;
//double z;

const byte MPS_OUT_pin = 18; // OUT data pin
const byte MPS_SCK_pin = 19; // clock data pin
int avg_size = 10; // #pts to average over

Q2HX711 MPS20N0040D(MPS_OUT_pin, MPS_SCK_pin); // start comm with the HX710B
Average<long> ave(avg_size);

void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
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
 
if ((x>=0&&x<90)&&(ave.mean()<10000000)){
  if(x>=0&&x<10){
    Serial.println("|o| | | |[ ]| | | | |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=10&&x<20){
    Serial.println("| |o| | |[ ]| | | | |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=20&&x<30){
    Serial.println("| | |o| |[ ]| | | | |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=30&&x<40){
    Serial.println("| | | |o|[ ]| | | | |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=40&&x<50){
    Serial.println("| | | | |[o]| | | | |");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else if(x>=50&&x<60){
    Serial.println("| | | | |[ ]|o| | | |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=60&&x<70){
    Serial.println("| | | | |[ ]| |o| | |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=70&&x<80){
    Serial.println("| | | | |[ ]| | |o| |");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  } else if(x>=80&&x<90){
    Serial.println("| | | | |[ ]| | | |o|");
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
 }

ave.push(MPS20N0040D.read());
Serial.println(ave.mean());                                                                                                     // wait for a second
  

delay(40);
}
