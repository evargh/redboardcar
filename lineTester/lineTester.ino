#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

//this code tests what the levels should be

RedBotSensor cSen = RedBotSensor(A1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(cSen.read());
  delay(100);
}
