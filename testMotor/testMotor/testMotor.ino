const int AIN1 = 10;
const int AIN2 = 11;
const int PWMA = 13;

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
  delay(100);
  spinMotor(1)
  delay(10000);
}

void spinMotor(int motorSpeed) {
  Serial.println(motorSpeed);
  if(motorSpeed == 1)
    analogWrite(PWM, 75);
  else
    analogWrite(PWM, 150);
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
