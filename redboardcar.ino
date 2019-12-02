#include <RedBot.h>

//motor1
const int AIN1 = 11;
const int AIN2 = 10;

//motor2
const int BIN1 = 6;
const int BIN2 = 5;

const int PWM = 11;

int switchPin = 7;

int motorSpeed = 0;

RedBotSensor cSen = RedBotSensor(A1);
RedBotSensor lSen = RedBotSensor(A0);
RedBotSensor rSen = RedBotSensor(A2);

RedBotSoftwareSerial swsp;

const int bgLevel = 300;
const int lineLevel = 800;
const int stopFloor = 500;
const int stopCeiling = 600;
const int exitLevel = 0;

int whichExit = 0;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  
  swsp.begin(9600);

}

void loop() {
  //Case 1: both white
  if(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
    spinMotor(0);
  }

  //left center
  if(cSen.read() > lineLevel && lSen.read() > lineLevel && rSen.read() < bgLevel) {
    while(lSen.read() > lineLevel) {//this and some condition to make sure is
      spinMotor(-1);           //limited within 90 degrees
    }
  }

  //right center
  if(cSen.read() > lineLevel && rSen.read() > lineLevel && lSen.read() < bgLevel) {
    while(rSen.read() > lineLevel) { //this and some condition to make sure is
      spinMotor(-2);           //limited within 90 degrees
    }
  }
  
  //Case 3: all sensors see dark
  if (lSen.read() > lineLevel && rSen.read() > lineLevel && cSen.read() > lineLevel)
  {
    takeHighway();
  }

  //Case 4: all sensors see red
  if (lSen.read() > stopFloor && rSen.read() > stopFloor && cSen.read() > stopFloor && lSen.read() < stopCeiling && rSen.read() < stopCeiling && cSen.read() < stopCeiling)
  {
    spinMotor(-3);
  }
  
  // put your main code here, to run repeatedly:
  //implement basic line following code
  //if multiple IR sensors are toggled, run takeHighway
  //if an exit is passed, increment the exit counter or run takeExit
  //if the black line is gone, run takeTunnel
  //if you hit red, STOP
}

void takeExit() {
  //after counting a certain amount of exits, run this function to turn off of the line
  //return to loop after the function is done
  
}

void takeHighway() {
  while(true) {
    spinMotor(1);
    //when three lines are found, run this function to speed up
    //when the two outside sensors lose their input, return to loop
    if(cSen.read() > lineLevel && rSen.read() < bgLevel && lSen.read() < bgLevel) {
      loop();
    }
  }
}

void takeTunnel() {
  while(true) {
    //when the black line is missing, check and follow the walls using sonar
    //when the black line returns, return to loop
    if(cSen.read() > lineLevel && rSen.read() < bgLevel && lSen.read() < bgLevel) {
      loop();
    }
    //if(nearing left wall)
    //  motorWrite(-2)
    //if(nearing right wall)
    // motorWrite(-1)
  }
}

void spinMotor(int motorSpeed) {
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
  if(motorSpeed == 2)
    analogWrite(PWM, 150);
  else
    analogWrite(PWM, 100);
}
