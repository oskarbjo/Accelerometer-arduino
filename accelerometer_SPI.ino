// Using on-board IMU chip

#include <Arduino_LSM6DS3.h>

uint16_t x, y, z;
uint16_t wx, wy, wz;
int i = 0;
void setup(){
Serial.begin(115200);
IMU.begin();
}

void loop(){
unsigned long startTime = micros();
while(!IMU.accelerationAvailable() && !IMU.gyroscopeAvailable()){

}

IMU.readAcceleration(x, y, z);

IMU.readGyroscope(wx, wy, wz);

  Serial.print(x); //X
  Serial.print(",");
  Serial.print(y); //Y
  Serial.print(",");
  Serial.print(z); //Z
  Serial.print(",");
  Serial.print(wx); //WX
  Serial.print(",");
  Serial.print(wy); //WY
  Serial.print(",");
  Serial.print(wz); //WZ
  Serial.print(",");
  unsigned long stopTime = micros();
//  Serial.print(dt,4);
  Serial.print(stopTime - startTime);
//  Serial.print(i);
  Serial.write(13); //Carriage return
  Serial.write(10); //Linefeed
//  i++; %Check that all data is transmitted correctly
}
