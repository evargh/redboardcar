#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
//#include <SharpIR.h>

//SharpIR LSensor = SharpIR(A3, 1080);
//SharpIR RSensor = SharpIR(A4, 1080);
//SharpIR CSensor = SharpIR(A5, 1080);

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
int distance = 0;
int duration = 0;
const int trigPin = 3; // idk what pins we have avialbe but set these to open pins
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
const int Somevalue = 16;

int whichExit = 0;

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

void setup() {

 
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);
}

void loop() {

  
 

distance = calculateDistance();

Serial.print("Distance ");
Serial.println(distance);
delay(2000);
  

  
}
