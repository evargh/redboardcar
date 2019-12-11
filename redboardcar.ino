#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
//#include <SharpIR.h>

//SharpIR LSensor = SharpIR(A3, 1080);
//SharpIR RSensor = SharpIR(A4, 1080);
//SharpIR CSensor = SharpIR(A5, 1080);

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

int distance =0;
int tiger = 0;
int duration =0;
const int trigPin = 3;
const int echoPin = 4;

const int PWM = 13;

int motorSpeed = 0;

RedBotSensor lSen = RedBotSensor(A2);
RedBotSensor cSen = RedBotSensor(A1);
RedBotSensor rSen = RedBotSensor(A0);

const int bgLevel = 500;
const int lineLevel = 700;
const int stopFloor = 500;
const int stopCeiling = 600;
const int exitLevel = 0;
const int Somevalue = 20;

int whichExit = 0;

void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM, OUTPUT);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);
}

void loop() {

  Serial.print("Left Sensor: ");
  Serial.println(lSen.read());
  Serial.print("Center Sensor: ");
  Serial.println(cSen.read());
  Serial.print("Right Sensor: ");
  Serial.println(rSen.read());
  

  tiger = calculateDistance();
  
  Serial.print("distance: ");
  Serial.println(distance);
  delay(1000);
if (0 < tiger < 13) //replace somevalue with an actual value
  {
    uturn();
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

  //Case 4: all sensors see nothing
  if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel)
  {
    Serial.println("taking tunnel");
//    takeTunnel();
  }

  //Case 5: all sensors see red
  if (lSen.read() > stopFloor && rSen.read() > stopFloor && cSen.read() > stopFloor && lSen.read() < stopCeiling && rSen.read() < stopCeiling && cSen.read() < stopCeiling)
  {
    spinMotor(-3);
  }
  Serial.println(motorSpeed);
}

void takeExit() {
  //after counting a certain amount of exits, run this function to turn off of the line
  //return to loop after the function is done

}

/*void takeTunnel() {
  int lbound = 100;
  int rbound = 100;
  while(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() < bgLevel) {
    ldist = LSensor.distance();
      rdist = RSensor.distance();
  if(ldist < lbound) {
      spinMotor(-2);
    }
    if(rdist < rbound) {
      spinMotor(-1);
    }
  }
}*/
void uturn() 
{
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
    digitalWrite(BIN2, LOW);
    //delay(40);
    if (lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      inturn = false;
    }
    } while (inturn == true);
}

int calculateDistance(){ 
 digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void spinMotor(int motorSpeed) {
  Serial.print("SpinMotor motorspeed: ");
  Serial.println(motorSpeed);
  if(motorSpeed == 0)
  {
    instraight = true;
    do {
    analogWrite(PWM, 150);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(5);
    analogWrite(PWM, 0);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(40);
    if (rSen.read() > lineLevel || lSen.read() > lineLevel) {
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
      analogWrite(PWM, 150);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      delay(6);
      analogWrite(PWM, 0);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    
    while (lSen.read() > lineLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) {
      analogWrite(PWM, 150);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      delay(6);
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
    analogWrite(PWM, 150);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    delay(6);
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
    analogWrite(PWM, 150);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(6);
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
