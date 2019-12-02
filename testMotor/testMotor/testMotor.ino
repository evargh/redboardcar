const int AIN1 = 11;
const int AIN2 = 10;

const int BIN1 = 6;
const int BIN2 = 5;

const int PWM = 13;


int motorSpeed = 0;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);
  Serial.println("Enter motor speed (0-255)...");
}

void loop() {
  if(Serial.available() > 0){
    motorSpeed = Serial.parseInt();
    Serial.print("Motor Speed: ");
    Serial.println(motorSpeed);
  }

  spinMotor(motorSpeed);
}

void spinMotor(int motorSpeed)
{
  if(motorSpeed > 0)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else if(motorSpeed < 0)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWM, abs(motorSpeed));
}
