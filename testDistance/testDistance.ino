#include <SharpIR.h>

SharpIR LSensor = SharpIR(A3, 1080);
SharpIR RSensor = SharpIR(A5, 1080);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Left Sensor");
  Serial.println(LSensor.distance());
  Serial.println("Right Sensor");
  Serial.println(RSensor.distance());
  delay(500);
}
