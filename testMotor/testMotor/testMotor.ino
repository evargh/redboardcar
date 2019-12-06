const int AIN1 = 10;
const int AIN2 = 11;
const int PWMA = 13;

int motorSpeed = 0;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

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
  }
  else if(motorSpeed < 0)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
}
