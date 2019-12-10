#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
#include <SharpIR.h>

SharpIR LSensor = SharpIR(A3, 1080);
SharpIR RSensor = SharpIR(A4, 1080);
SharpIR CSensor = SharpIR(A5, 1080);

int ldist = 0;
int rdist = 0;
int cdist = 0;

boolean tookHighway = false;

//motor1
const int AIN1 = 11;
const int AIN2 = 10;

//motor2
const int BIN1 = 6;
const int BIN2 = 5;

const int PWM = 13;

int motorSpeed = 0;

RedBotSensor lSen = RedBotSensor(A2);
RedBotSensor cSen = RedBotSensor(A1);
RedBotSensor rSen = RedBotSensor(A0);

const int bgLevel = 400;
const int lineLevel = 800;
const int stopFloor = 500;
const int stopCeiling = 600;

void setup() {
  tookHighway = false;
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.print("Left Sensor: ");
  Serial.println(lSen.read());
  Serial.print("Center Sensor: ");
  Serial.println(cSen.read());
  Serial.print("Right Sensor: ");
  Serial.println(rSen.read());

  //Case 1: both white
  if(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
    spinMotor(0);
    Serial.println("go straight");
  }

  //left + center
  if(tookHighway == false && lSen.read() > lineLevel && rSen.read() < bgLevel) {
    spinMotor(-3);
    Serial.println("go left");
    while(lSen.read() > lineLevel) {
      spinMotor(-1);
    }
  }

  //right + center
  if(tookHighway == false && rSen.read() > lineLevel && lSen.read() < bgLevel) {
    Serial.println("go right");
    while(rSen.read() > lineLevel) {
      spinMotor(-2);
    }
  }
  
  //right exit
  if(tookHighway == true && cSen.read() > lineLevel && rSen.read() > lineLevel && lSen.read() < bgLevel) {
    Serial.println("right exit");
    while(rSen.read() > lineLevel)
      spinMotor(-2);
  }

  //left exit
  if(tookHighway == true && cSen.read() > lineLevel && rSen.read() < bgLevel && lSen.read() > lineLevel) {
    Serial.println("left exit");
    while(lSen.read() > lineLevel)
      spinMotor(-1);
  }

  //Case 3: all sensors see dark
  if (tookHighway == false && lSen.read() > lineLevel && rSen.read() > lineLevel && cSen.read() > lineLevel) {
    Serial.println("taking highway");
    spinMotor(1);
    tookHighway = true;
  }

  //Case 4: all sensors see nothing
  if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel) {
    Serial.println("taking tunnel");
    takeTunnel();
  }

  //Case 5: all sensors see red
  if (lSen.read() > stopFloor && rSen.read() > stopFloor && cSen.read() > stopFloor && lSen.read() < stopCeiling && rSen.read() < stopCeiling && cSen.read() < stopCeiling) {
    spinMotor(-3);
  }
}

void takeTunnel() {
  int lbound = 100;
  int rbound = 100;
  while(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel) {
    int ldist = LSensor.distance();
    int rdist = RSensor.distance();
    if(ldist < lbound) {
      spinMotor(-2);
    }
    if(rdist < rbound) {
      spinMotor(-1);
    }
  }
}

void spinMotor(int motorSpeed) {
  Serial.println(motorSpeed);
  if(motorSpeed == 1)
    analogWrite(PWM, 127);
  else
    analogWrite(PWM, 100);
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
    digitalWrite(BIN2, LOW);
  }
  if(motorSpeed == -2)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
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
}
