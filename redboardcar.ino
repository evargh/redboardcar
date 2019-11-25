#include <RedBot.h>

const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;

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
  pinMode(PWMA, OUTPUT);
  
  swsp.begin(9600);

}

void loop() {
  //Case 1: both white
  if(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) 
    spinMotor(0);
    
  //Case 2: center sensor is empty
  if(cSen.read() < bgLevel) {
    while(cSen.read() < bgLevel) //this and some condition to make sure im
      spinMotor(-1);           //limited within 90 degrees
    while(cSen.read() < bgLevel) //this and some condition to make sure im
      spinMotor(-2);           //limited within 180 degrees
    if(cSen.read() < bgLevel)
      takeTunnel();
  }
  
  //Case 3: all sensors see dark
  if (lSen.read() > lineLevel && rSen.read() > lineLevel && cSen.read() > lineLevel)
  {
    takeHighway();
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
  }
}

void spinMotor(int motorSpeed)
{
  if(motorSpeed >= 0)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
  }
  if(motorSpeed == -1)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  if(motorSpeed == -2)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  if(motorSpeed == -3)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  if(motorSpeed == 1)
    analogWrite(PWMA, 64);
  else
    analogWrite(PWMA, 80);
}
