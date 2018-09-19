#include <AFMotor.h> 
#include <Servo.h>    
#include <NewPing.h>/*
  Front Motor (Steering) => Channel A
  Back Motor => Channel B

  Since the motor shield hijacks 6 pins for the motors'
  control, they are declared in the MotorShieldR3 library.
*/

// Defining pins for the two motors (A & B)

#define AiA 9 // PWM
#define AiB 6
#define BiA 10 // PWM
#define BiB 11

//Defining pins for the HSR04 servo obstacle detection
#define trigPin 3
#define echoPin 2


Servo myservo;
int pos = 0;

char command = 'S';
int velocity = 255; //max velocity
int speed = 0; //starting speed
bool drvFlag = false;

int gamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

uint16_t j;
int dir;
unsigned long oldtime;
int mode;
bool turboFlag = false;

#define DEFAULT 0
#define BABE 7



void setup()
{
  Serial.begin(9600);  //Set the baud rate to that of your Bluetooth module.
  
  //Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void SA() { // stop A
  digitalWrite(AiA,  LOW);
  digitalWrite(AiB,  LOW);
}
// void FA(){ // forward A
//   digitalWrite(AiA,  HIGH);
//   digitalWrite(AiB,  LOW);
// }
void FA() { // forward A PWM
  analogWrite(AiA,  speed);
  digitalWrite(AiB,  LOW);
}
void RA() { // reverse A
  analogWrite(AiA,  255 - speed);
  digitalWrite(AiB,  HIGH);
}
void SB() { // stop B
  digitalWrite(BiA,  LOW);
  digitalWrite(BiB,  LOW);
}
// void FB(){ // forward B
//   digitalWrite(BiB,  HIGH);
//   digitalWrite(BiA,  LOW);
// }
void FB() { // forward B PWM
  digitalWrite(BiB,  HIGH);
  analogWrite(BiA,  255 - speed);
}
void RB() { // reverse B
  digitalWrite(BiB,  LOW);
  analogWrite(BiA,  speed);
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
  
  // code for Servo detection
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    // if car is too close to object it will move backwards
    if (distance <= 10) {
      Serial.println("A thing");
      int oldspd = speed; // store the old spd
      speed = 255; // set max speed
      RA();
      RB();
      drvFlag = true;
      delay(750); // wait
      SB(); SA(); drvFlag = false; // stop motors
      speed = oldspd; // restore the old spd
    }
  }

  if (Serial.available() > 0) {
    command = Serial.read();
    //Change pin mode only if new command is different from previous.
    //Serial.println(command);
    switch (command) {
      case 'F':
        FA(); FB(); drvFlag = true;
        break;
      case 'B':
        RA(); RB(); drvFlag = true;
        break;
      case 'L':
        RB(); FA(); drvFlag = true;
        break;
      case 'R':
        FB(); RA(); drvFlag = true;
        break;
      case 'S':
        SB(); SA(); drvFlag = false;
        break;
      case 'I':  //FR
        SA(); FB(); drvFlag = true;
        break;
      case 'J':  //BR
        SA(); RB(); drvFlag = true;
        break;
      case 'G':  //FL
        FA(); SB(); drvFlag = true;
        break;
      case 'H':  //BL
        RA(); SB(); drvFlag = true;
        break;
      case 'W':  //Font ON

        break;
      case 'w':  //Font OFF

        break;
      case 'U':  //Back ON

        break;
      case 'u':  //Back OFF

        break;
      case 'V':  //Horn ON
        turboFlag = true;
        break;
      case 'v':  //Horn OFF
        turboFlag = false;
        break;
      case 'X':  //Extra ON
        mode = BABE;
        break;
      case 'x':  //Extra OFF
        mode = DEFAULT;
        break;
      case 'D':  //Everything OFF
        SB(); SA(); drvFlag = false;
        break;

      default:  //Get velocity
        if (command == 'q') {
          velocity = 255;  //Full velocity

        }
        else {
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
          if ((command >= 48) && (command <= 57)) {
            //Subtracting 48 changes the range from 48-57 to 0-9.
            //Multiplying by 25 changes the range from 0-9 to 0-225.
            velocity = (command - 48) * 25;

          }
        }
    }


    // acceleration ramping
    if (drvFlag) {
      speed += 7;
      if (speed > velocity) {
        speed = velocity;
      }
    } else {
      speed = 35;
    }

    if (turboFlag) {
      speed = 255;
    }

  }

}

