
//KEEP YOUR DISTANCE.....

#include<Servo.h>
#define unpress_angle 90
#define press_angle_1 0
#define press_angle_2 180

const int in1=2;
const int in2=3;
const int en1=4;
const int in3=6;
const int in4=7;
const int en2=5;
const int trigPIN=10;
const int echoPIN=9;

Servo servo;

//Configuration
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(trigPIN, OUTPUT);
  pinMode(echoPIN, INPUT);
  servo.attach(8);
  servo.write(unpress_angle);
  Serial.begin(9600);
}

//Calculates the Distance from Obstacle through Ultrasonic Sensor
long distCalc(int trigPIN, int echoPIN){
  digitalWrite(trigPIN,LOW);
  delay(2);
  digitalWrite(trigPIN,HIGH);
  delay(10);
  digitalWrite(trigPIN,LOW);
  long duration = pulseIn(echoPIN,HIGH);
  return (duration*0.034)/2;
}

//For Stopping the Car
void stop(){
  analogWrite(en1,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(en2,255);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

//Turn Right
void turnRight(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(en1,255);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(en2,255);
}

//Turn Left
void turnLeft(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(en1,255);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(en2,255);
}

//Move Forward
void moveStraight(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(en1,255);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(en2,255);
}

//All the logic when dist < 20, Car stops, looks to left and right , if no obstacle is detected, then moves in that diresction else if dist > 20 (from obstacle) => keep Moving Straight...... :)
void loop() {
  int dist=distCalc(trigPIN, echoPIN);
  Serial.println(dist);
  if(dist<20){
    stop();
    servo.write(press_angle_1);
    delay(1000);
    dist=distCalc(trigPIN, echoPIN);
    Serial.println(dist);
    servo.write(unpress_angle);
    delay(1000);
    if(dist>20){
      turnRight();
      delay(300);
      moveStraight();
    }
    else{
      servo.write(press_angle_2);
      delay(1000);
      dist=distCalc(trigPIN, echoPIN);
      Serial.println(dist);
      servo.write(unpress_angle);
      delay(1000);
      if(dist>20){
        turnLeft();
        delay(300);
        moveStraight();  
      }
    }
  }
  else{
    moveStraight();
  }
  delay(100);
}