//library
#include <Servo.h>
 
//pin ultrasonik
const int trigPin = D4;
const int echoPin = D3;

// Variables
long duration;
int distance;

//inisiasi servo
Servo myServo; 

//setup
void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  //pin servo
  myServo.attach(D2); 
}

//loop
void loop() {
  //rotasi servo
  int i;
  for(i=0;i<=180;i+=1){  
  myServo.write(i);
  delay(5);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(i=180;i>=0;i-=1){  
  myServo.write(i);
  delay(5);
  distance = calculateDistance();
  }
}

//hitung jarak
int calculateDistance(){ 

  //ultrasonik
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
