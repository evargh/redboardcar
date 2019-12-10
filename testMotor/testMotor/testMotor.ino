
const int AIN1 = 11;
const int AIN2 = 10;
const int BIN1 = 6;
const int BIN2 = 5;
const int PWM = 13;

int motorSpeed = 0;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  spinMotor(2);
  delay(250);
  spinMotor(1);
  delay(40);
}

void spinMotor(int motorSpeed) {
  Serial.println(motorSpeed);
  if(motorSpeed == 1)
    analogWrite(PWM, 0);
  else
    analogWrite(PWM, 175);
  if(motorSpeed >= 0)
  {
    Serial.println(motorSpeed);
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
