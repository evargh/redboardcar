#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

//this code tests what the levels should be
RedBotSensor lSen = RedBotSensor(A2);
RedBotSensor cSen = RedBotSensor(A1);
RedBotSensor rSen = RedBotSensor(A0);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  Serial.print("Left Sensor: ");
  Serial.println(lSen.read());
  Serial.print("Center Sensor: ");
  Serial.println(cSen.read());
  Serial.print("Right Sensor: ");
  Serial.println(rSen.read());
  delay(1000);
}

//123
