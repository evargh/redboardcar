#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
#include <SharpIR.h>

SharpIR LSensor = SharpIR(A3, 1080);
SharpIR RSensor = SharpIR(A4, 1080);
SharpIR CSensor = SharpIR(A5, 1080);

int ldist = 0;
int rdist = 0;
int cdist = 0;

boolean inturn = false;
boolean instraight = false;
boolean inhighway = false;
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

const int bgLevel = 500;
const int lineLevel = 700;
const int stopFloor = 500;
const int stopCeiling = 700;
const int exitLevel = 0;
const int Somevalue = 20;

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

  Serial.print("distance: ");
  Serial.println(CSensor.distance());
  Serial.print("left distance: ");
  Serial.println(LSensor.distance());
  Serial.print("right distance: ");
  Serial.println(RSensor.distance());
  if (0 < CSensor.distance() && CSensor.distance() < 8) {
    uturn();
  }
  
  //Case 4: all sensors see nothing
  if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel)
  {
    Serial.println("taking tunnel");
    takeTunnel();
  }
  //Case 1: both white
  if(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
    spinMotor(0);
    Serial.println("go straight");
  }

  //left + center
  if(lSen.read() > lineLevel && rSen.read() < bgLevel) {
    Serial.println("go left");
    spinMotor(-1);
  }

  //right + center
  if(rSen.read() > lineLevel && lSen.read() < bgLevel) {
    Serial.println("go right");
      spinMotor(-2);
  }

  //Case 3: all sensors see dark
  if (lSen.read() > lineLevel && rSen.read() > lineLevel && cSen.read() > lineLevel) { 
    Serial.println("taking highway");
    spinMotor(1);
  }



  //Case 5: all sensors see red
  if (cSen.read() > stopFloor && cSen.read() < stopCeiling)
  {
    spinMotor(-3);
  }
  Serial.println(motorSpeed);
}

void takeExit() {
  //after counting a certain amount of exits, run this function to turn off of the line
  //return to loop after the function is done

}

void takeTunnel() {
  int lbound = 15;
  int rbound = 15;
  while(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel) {
    Serial.println("in tunnel zzzzzzzsazzzzzzzzzzzzzzzzzzzzzzzzz");
    //spinMotor(0);
    ldist = LSensor.distance();
    rdist = RSensor.distance();
    Serial.println(ldist);
    Serial.println(rdist);
    if((ldist < lbound && rdist < rbound) || (ldist > lbound && rdist > rbound)) {
      Serial.println("tunnel straight");
      analogWrite(PWM, 255);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      delay(12);
      analogWrite(PWM, 0);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    else if((ldist < lbound && rdist > rbound)) {
      Serial.println("tunnel right");
      analogWrite(PWM, 255);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      delay(20);
      analogWrite(PWM, 0);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    else if((ldist > lbound && rdist < rbound)) {
      Serial.println("tunnel left");
      analogWrite(PWM, 255);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      delay(20);
      analogWrite(PWM, 0);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    }
  }
}
void uturn() 
{
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    delay(40);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    inturn = true;
    do {
    Serial.println("uturn biittch");
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    delay(10);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    //delay(40);
    if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inturn = false;
    }
    } while (inturn == true);

    instraight = true;
    do {
    Serial.println("return from uturnu");
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(7);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
    if (rSen.read() > lineLevel && lSen.read() > lineLevel) {
      instraight = false;
    }
    } while (instraight == true);

    inturn = true;
    do {
    Serial.println("exit the exit");
    analogWrite(PWM, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(7);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
  if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inturn = false;
    }
    } while (inturn == true);

    instraight = true;
    do {
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(7);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
    if (rSen.read() > lineLevel && lSen.read() > lineLevel) {
      instraight = false;
    }
    } while (instraight == true);

    inturn = true;
    do {
    analogWrite(PWM, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(7);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
  if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inturn = false;
    }
    } while (inturn == true);
}

void spinMotor(int motorSpeed) {
  Serial.print("SpinMotor motorspeed: ");
  Serial.println(motorSpeed);
  if(motorSpeed == 0)
  {
    instraight = true;
    do {
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(6);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
    if (rSen.read() > lineLevel || lSen.read() > lineLevel || (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel)) {
      instraight = false;
    }
    } while (instraight == true);
  }
  if(motorSpeed == 1)
  {
    inhighway = true;
    do {
    Serial.println("HIGHQWYAYY");
    Serial.print("Left Sensor: ");
    Serial.println(lSen.read());
    Serial.print("Center Sensor: ");
    Serial.println(cSen.read());
    Serial.print("Right Sensor: ");
    Serial.println(rSen.read());
    
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    
    while (lSen.read() < bgLevel && rSen.read() > lineLevel && cSen.read() > lineLevel) {
      analogWrite(PWM, 255);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      delay(7);
      analogWrite(PWM, 0);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    
    while (lSen.read() > lineLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      analogWrite(PWM, 255);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      delay(7);
      analogWrite(PWM, 0);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    } 
    
    delay(100);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(10);
    
    
    if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inhighway = false;
      inturn = false;
    }
    
    } while (inhighway == true);
  }

  //Left turn
  if(motorSpeed == -1)
  {
    inturn = true;
    do {
    Serial.println("turn left");
    analogWrite(PWM, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    delay(7);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    //delay(40);
    if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inturn = false;
    }
    } while (inturn == true);
  }

  //Right turn
  if(motorSpeed == -2)
  {
    inturn = true;
    do {
    Serial.println("turn right");
    analogWrite(PWM, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(7);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
  if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inturn = false;
    }
    } while (inturn == true);
    }
  if(motorSpeed == -3)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  
}
