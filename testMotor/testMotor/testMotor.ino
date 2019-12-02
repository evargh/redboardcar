#include <RedBot.h>

const int AIN1 = 10;
const int AIN2 = 11;

const int BIN1 = 6;
const int BIN2 = 5;

const int PWMA = 13;

int motorSpeed = 0;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  Serial.begin(9600);

}

void loop() {
 Serial.print("start running");
 spinMotor(2);
 delay(4000);
 spinMotor(1);
 delay(4000);
 spinMotor(0);
 delay(4000);
 spinMotor(-1);
 delay(4000);
 spinMotor(-2);
 delay(4000);
 spinMotor(-3);
 delay(4000);
}

void spinMotor(int motorSpeed)
{
  if(motorSpeed >= 0)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  if(motorSpeed == -1)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  if(motorSpeed == -2)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  if(motorSpeed == -3)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  if(motorSpeed == 2)
    analogWrite(PWMA, 80);
  else
    analogWrite(PWMA, 64);
}
