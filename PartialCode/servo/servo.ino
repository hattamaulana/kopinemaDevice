//// Include the Servo library 
//#include <Servo.h> 
//// Declare the Servo pin 
//int servoPin = A0; 
//// Create a servo object 
//Servo Servo1; 
//void setup() { 
//   // We need to attach the servo to the used pin number 
//   Servo1.attach(servoPin); 
//}
//void loop(){ 
//   // Make servo go to 0 degrees 
//   Servo1.write(0); 
//   delay(1000); 
//   // Make servo go to 90 degrees 
//   Servo1.write(90);  
//   delay(1000);
//   // Make servo go to 180 degrees 
//   Servo1.write(180); 
//   delay(1000);
//   Servo1.write(90);
//   delay(1000);
//   Servo1.write(0);
//   delay(1000);
//}

/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(A0);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}
