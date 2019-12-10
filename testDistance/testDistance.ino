#include <SharpIR.h>
#include <HCSR04.h>

SharpIR LSensor = SharpIR(A3, 1080);
SharpIR RSensor = SharpIR(A4, 1080);

UltraSonicDistanceSensor CSensor(9, 8);

void setup() {
  Serial.print(9600);
}

void loop() {
  Serial.println("Center Sensor");
  Serial.println(CSensor.measureDistanceCm());
  Serial.println("Left Sensor");
  Serial.println(LSensor.distance());
  Serial.println("Right Sensor");
  Serial.println(RSensor.distance());
  delay(500);
}
