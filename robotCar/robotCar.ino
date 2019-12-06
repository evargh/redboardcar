// test
#include <RedBot.h>
RedBotSensor cSen = RedBotSensor();
RedBotSensor lSen = RedBotSensor();
RedBotSensor rSen = RedBotSensor();

RedBotSoftwareSerial swsp;

const int bgLevel = 600;
const int lineLevel = 700;

void setup() {
  swsp.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // Case 1: both white. Drive forward!
  if(lSen.read() < bgLevel && rSen.read() < bgLevel && cSen.read() > lineLevel) 
    motors.drive(100);
    
  //Case 2: center sensor is empty
  if(cSen.read() < bgLevel) {
    //pivot 90 to the left
      //if line found, loop
    //pivot 90 to the right
      //if line found, loop
    //else
      //take tunnel
  }
  
  //Case 3: all sensors see dark
  if (lSen.read() > lineLevel && rSen.read()> lineLevel && cSen.read > lineLevel)
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
    //when three lines are found, run this function to speed up
    //when the two outside sensors lose their input, return to loop
    if(cSen.read() > lineLevel && rSen.read() < bgLevel && lSen.read() < bgLevel)
      loop();
  }
}

void takeTunnel() {
  while(true) {
    //when the black line is missing, check and follow the walls using sonar
    //when the black line returns, return to loop
    if(cSen.read() > lineLevel && rSen.read() < bgLevel && lSen.read() < bgLevel)
      loop();
  }
}
