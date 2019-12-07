#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
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
const int exitLevel = 0;

int whichExit = 0;

void setup() {

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
  delay(1000);

  //Case 1: both white
  if(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
    spinMotor(0);
    Serial.println("go straight");
  }

  //left + center
  else if(cSen.read() > lineLevel && lSen.read() > lineLevel && rSen.read() < bgLevel) {
    Serial.println("go left");
    while(lSen.read() > lineLevel) {
      spinMotor(-1);
    }
  }

  //right + center
  else if(cSen.read() > lineLevel && rSen.read() > lineLevel && lSen.read() < bgLevel) {
    Serial.println("go right");
    while(rSen.read() > lineLevel) {
      spinMotor(-2);
    }
  }

  else {
    Serial.println("option not found");
  }
}

  

  //Case 3: all sensors see dark
  /*if (lSen.read() > lineLevel && rSen.read() > lineLevel && cSen.read() > lineLevel)
  {
    takeHighway();

  Serial.print("Left Sensor: ");
  Serial.println(lSen.read());
  Serial.print("Center Sensor: ");
  Serial.println(cSen.read());
  Serial.print("Right Sensor: ");
  Serial.println(rSen.read());
  delay(1000);
  }*/

  //Case 4: all sensors see red
  /*if (lSen.read() > stopFloor && rSen.read() > stopFloor && cSen.read() > stopFloor && lSen.read() < stopCeiling && rSen.read() < stopCeiling && cSen.read() < stopCeiling)
  {
    spinMotor(-3);

  Serial.print("Left Sensor: ");
  Serial.println(lSen.read());
  Serial.print("Center Sensor: ");
  Serial.println(cSen.read());
  Serial.print("Right Sensor: ");
  Serial.println(rSen.read());
  delay(1000);
  }*/

  // put your main code here, to run repeatedly:
  //implement basic line following code
  //if multiple IR sensors are toggled, run takeHighway
  //if an exit is passed, increment the exit counter or run takeExit
  //if the black line is gone, run takeTunnel
  //if you hit red, STOP
//}

/*void takeExit() {
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

      Serial.println("Taking Highway");
    }
  }
}

void takeTunnel() {
  while(true) {
    //when the black line is missing, check and follow the walls using sonar
    //when the black line returns, return to loop
    if(cSen.read() > lineLevel && rSen.read() < bgLevel && lSen.read() < bgLevel) {
      loop();

      Serial.println("Taking Tunnel");
    }
    //if(nearing left wall)
    //  motorWrite(-2)
    //if(nearing right wall)
    // motorWrite(-1)
  }
}*/

void spinMotor(int motorSpeed) {
  Serial.println(motorSpeed);
  if(motorSpeed == 1)
    analogWrite(PWM, 100);
  else
    analogWrite(PWM, 127);
  if(motorSpeed >= 0)
  {
    Serial.println("Straight up");
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  if(motorSpeed == -1)
  {
    Serial.println("Left Turn ");
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
