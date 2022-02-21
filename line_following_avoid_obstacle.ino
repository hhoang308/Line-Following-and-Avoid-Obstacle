//ARDUINO LINE FOLLOWING CAR//
// YOU HAVE TO INSTALL THE AFMOTOR LIBRARY BEFORE UPLOAD THE CODE//
// GO TO SKETCH >> INCLUDE LIBRARY >> ADD .ZIP LIBRARY >> SELECT AF MOTOR ZIP FILE //
 
//including the libraries
#include <AFMotor.h>
#include <NewPing.h>

//defining pins and variables
#define left A3
#define right A4

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);


void setup() {
  //declaring pin types
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println(digitalRead(left));
  
  Serial.println(digitalRead(right));
  int distance = sonar.ping_cm();
  if(distance == 0){
    distance = 30;
  }
  if(distance <= 4 ){
    Stop();
    delay(100);
    turnRight();
    delay(900);
    moveForward();
    delay(1000);
    turnLeft();
    delay(700);
    moveForward();
    delay(2200);
    turnLeft();
    delay(700);
    moveForward();
    delay(900);
    turnRight();
    delay(900);
  }
  //line detected by both
  if(digitalRead(left)==0 && digitalRead(right)==0){
    //Forward
    moveForward();
  }
  //line detected by left sensor
  else if(digitalRead(left)==0 && !analogRead(right)==0){
    //turn left
    turnLeft();
    
  }
  //line detected by right sensor
  else if(!digitalRead(left)==0 && digitalRead(right)==0){
    //turn right
    turnRight();
   
  }
  //line detected by none
  else if(!digitalRead(left)==0 && !digitalRead(right)==0){
    //stop
    Stop();
  }
  
}

void moveForward(){
    motor1.run(FORWARD);
    motor1.setSpeed(150);
    motor2.run(FORWARD);
    motor2.setSpeed(150);
    motor3.run(FORWARD);
    motor3.setSpeed(150);
    motor4.run(FORWARD);
    motor4.setSpeed(150);
}

void Stop(){
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
}

void turnRight(){
    motor3.run(BACKWARD);
    motor3.setSpeed(200);
    motor2.run(BACKWARD);
    motor2.setSpeed(200);
    motor1.run(FORWARD);
    motor1.setSpeed(200);
    motor4.run(FORWARD);
    motor4.setSpeed(200);
}

void turnLeft(){
    motor2.run(FORWARD);
    motor2.setSpeed(200);
    motor3.run(FORWARD);
    motor3.setSpeed(200);
    motor1.run(BACKWARD);
    motor1.setSpeed(200);
    motor4.run(BACKWARD);
    motor4.setSpeed(200);
}
