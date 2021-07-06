// Accelerometer I2c communication


//Connections: 
// Arduino 3.3V --> LSM6DS3H SDO, SDX, CS, SCX, Vdd
// Arduino GND --> LSM6DS3H GND
// Arduino A4 --> LSM6DS3H SDA
// Arduino A5 --> LSM6DS3H SCL



#include <Wire.h>

byte WHO_AM_I_register = 0b01101001;
//byte deviceAddress = 0x6A;
byte deviceAddress = 0x6B;

int val=0;
byte LSB = 0;
byte MSB = 0;

byte CTRL1_XL = 0x10; //Linear acceleration sensor control register
byte CTRL2_G = 0x11; //Gyro sensor control register
byte CTRL1_XL_settings = 0b01100000;
byte CTRL2_G_settings = 0b01100010;


byte OUTX_L_G = 0x22;
byte OUTX_H_G = 0x23;
byte OUTY_L_G = 0x24;
byte OUTY_H_G = 0x25;
byte OUTZ_L_G = 0x26;
byte OUTZ_H_G = 0x27;
byte OUTX_L_XL = 0x28;
byte OUTX_H_XL = 0x29;
byte OUTY_L_XL = 0x2A;
byte OUTY_H_XL = 0x2B;
byte OUTZ_L_XL = 0x2C;
byte OUTZ_H_XL = 0x2D;

void setup() {
  Wire.begin(); // Initiate the Wire library
  Wire.setClock(400000);
  Serial.begin(9600);
  while (!Serial) ;
  delay(100);
  // Enable measurement
  Wire.beginTransmission(deviceAddress);
  Wire.write(CTRL1_XL);
  delay(1);
  Wire.write(CTRL1_XL_settings);
  Wire.endTransmission();

  Wire.beginTransmission(deviceAddress);
  Wire.write(CTRL2_G);
  delay(1);
  Wire.write(CTRL2_G_settings);
  Wire.endTransmission();

  
}

signed int val1,val2,val3,val4,val5,val6;

void loop() {

  val1 = readData(OUTX_H_XL,OUTX_L_XL);
  val2 = readData(OUTY_H_XL,OUTY_L_XL);
  val3 = readData(OUTZ_H_XL,OUTZ_L_XL);
  val4 = readData(OUTX_H_G,OUTX_L_G);
  val5 = readData(OUTY_H_G,OUTY_L_G);
  val6 = readData(OUTZ_H_G,OUTZ_L_G);



  printToMatlab();
  delay(10);


}


int readData(byte MSBaddress,byte LSBaddress){
  MSB=0;
  LSB=0;
  Wire.beginTransmission(deviceAddress);
  Wire.write(MSBaddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress,1);
  MSB=Wire.read();
  delay(0.5);
  Wire.beginTransmission(deviceAddress);
  Wire.write(LSBaddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress,1);
  LSB=Wire.read();

  val = MSB << 8 | LSB;
  return val;
  }

void printToMatlab(){
  Serial.print("X: ");
  Serial.print(val1);
  Serial.print(", Y: ");
  Serial.print(val2);
  Serial.print(", Z: ");
  Serial.print(val3);
  Serial.print(", wx: ");
  Serial.print(val4);
  Serial.print(", wy: ");
  Serial.print(val5);
  Serial.print(", wz: ");
  Serial.print(val6);
  Serial.write(13); //Carriage return
//  Serial.write(10); //Linefeed

  }

void serialPlotter(){
  Serial.println(val3);
//  Serial.println(val2);
//  Serial.println(val3);
  
  }
  
//for(int i=7;i>-1;i--){
//  Serial.print(bitRead(MSB,i));
//  }
//for(int i=7;i>-1;i--){
//  Serial.print(bitRead(LSB,i));
//  }
