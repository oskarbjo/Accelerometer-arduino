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

int val = 0;
byte LSB = 0;
byte MSB = 0;

byte CTRL1_XL = 0x10; //Linear acceleration sensor control register
byte CTRL2_G = 0x11; //Gyro sensor control register
//byte CTRL1_XL_settings = 0b01100000;
//byte CTRL2_G_settings = 0b01100010;
byte CTRL1_XL_settings = 0b01000000;
byte CTRL2_G_settings = 0b01000010;



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
  Serial.begin(115200);
  while (!Serial) ; //remove if running on battery
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

signed int val1, val2, val3, val4, val5, val6;
unsigned long val7;

void loop() {

  unsigned long t1 = micros();
  val1 = readData(OUTX_H_XL, OUTX_L_XL);
  val2 = readData(OUTY_H_XL, OUTY_L_XL);
  val3 = readData(OUTZ_H_XL, OUTZ_L_XL);
  val4 = readData(OUTX_H_G, OUTX_L_G);
  val5 = readData(OUTY_H_G, OUTY_L_G);
  val6 = readData(OUTZ_H_G, OUTZ_L_G);



  printToMatlab(t1);
  //serialPlotter(t1);
  //delay(1);
}


int readData(byte MSBaddress, byte LSBaddress) {
  MSB = 0;
  LSB = 0;
  Wire.beginTransmission(deviceAddress); //Which device to read/write
  Wire.write(MSBaddress); //Point at MSG register name
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, 1); //Request data from above address
  MSB = Wire.read();
  //delay(0.5);
  Wire.beginTransmission(deviceAddress);
  Wire.write(LSBaddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, 1);
  LSB = Wire.read();

  val = MSB << 8 | LSB;
  return val;
}

void printToMatlab(unsigned long startTime) {
  //Serial.print("X: ");
  Serial.print(val1); //X
  Serial.print(",");
  Serial.print(val2); //Y
  Serial.print(",");
  Serial.print(val3); //Z
  Serial.print(",");
  Serial.print(val4); //WX
  Serial.print(",");
  Serial.print(val5); //WY
  Serial.print(",");
  Serial.print(val6); //WZ
  Serial.print(",");
  unsigned long stopTime = micros();
  Serial.print(stopTime - startTime);
  Serial.write(13); //Carriage return
  Serial.write(10); //Linefeed

}

void serialPlotter(unsigned long startTime) {
  unsigned long stopTime = micros();
  Serial.println(stopTime - startTime);
}

//for(int i=7;i>-1;i--){
//  Serial.print(bitRead(MSB,i));
//  }
//for(int i=7;i>-1;i--){
//  Serial.print(bitRead(LSB,i));
//  }
