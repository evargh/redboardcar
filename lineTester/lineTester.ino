#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

//this code tests what the levels should be

RedBotSensor cSen = RedBotSensor(A0);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  Serial.println(cSen.read());
  delay(100);
}

//123
