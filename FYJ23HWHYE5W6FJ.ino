// Coordinator!

//#define forwardMotor1 A1  //A01
//#define backMotor1 A1  //A02
//#define forwardMotor2 A2  //B01
//#define backMotor2 A2  //B02

#include <SparkFun_TB6612.h>

#include <Servo.h>
// Declare the Servo pin
int servoPin5 = 5;
int servoPin6 = 6;
int servoPin2 = A1;
int servoPin3 = A2;
// Create a servo object
Servo SHOULDER;
Servo ELBOW;
Servo ROTATE;
Servo CLAW;


#define AIN1 9
#define BIN1 8
#define AIN2 7
#define BIN2 10
#define PWMA 12
#define PWMB 4
#define STBY 11

#define VM OUTPUT
#define VCC 5V
#define GND GND

const int offsetA = 1;
const int offsetB = 1;

Motor Motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor Motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

//int claw_ang=0;
//int tilt_ang=15;
//Servo claw;
//Servo tilt;

const int led = 13; //led at pin 13


#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3);

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
  SHOULDER.attach(servoPin5);
  ELBOW.attach(servoPin6);
  ROTATE.attach(servoPin2);
  CLAW.attach(servoPin3);
  //  claw.attach(5);
  //  tilt.attach(6);
  //  pinMode(rightMotor1, OUTPUT);
  //  pinMode(rightMotor2, OUTPUT);
  //  pinMode(leftMotor1, OUTPUT);
  //  pinMode(leftMotor2, OUTPUT);
  //  pinMode(led,OUTPUT);
}

void loop()
{
  if (XBee.available()) {
    char msg = XBee.read(); //contains the message from arduino sender
    //SERVOS ARE A-D
    //value3 is the index-finger

    //ROTATE
    //    if (msg == 'D') {
    //      ROTATE.write(0);
    //      delay(100);
    //      //middle-finger up
    //      Serial.println(msg);
    //    }
    if (msg == 'M') {
      // Make servo go to 90 degrees
      ROTATE.write(90);
      delay(100);
      //middle-finger down
      //      ROTATE.write(360);
      //      delay(100);
      Serial.println(msg);
    }
    if (msg == 'T') {
      // Make servo go to 180 degrees
      ROTATE.write(180);
      delay(100);
      //middle and ring-fingers bent
    }

    //SHOULDER AND ELBOW?
    //  if (msg == 'A') {
    //    SHOULDER.write(0);
    //    delay(100);
    //    ELBOW.write(0);
    //    delay(100);
    //    //ring and pinky up
    //  }
    if (msg == 'B') {
      SHOULDER.write(90);
      delay(100);
      ELBOW.write(90);
      delay(100);
      //ring and pinky bent
    }
    if (msg == 'L') {
      SHOULDER.write(180);
      delay(100);
      ELBOW.write(180);
      delay(100);
      //middle, ring, and pinky bent
      //      SHOULDER.write(360);
      //      delay(100);
      //    ELBOW.write(360);
      //    delay(100);
    }

    //CLAW
    //  if (msg == 'C') {
    //    CLAW.write(0);//index-finger up
    //    delay(100);
    //  }
    if (msg == 'O') {
      // Make servo go to 90 degrees
      //      CLAW.write(90);
      //      delay(100);
      //      // Make servo go to 180 degrees (open)
      CLAW.write(180);
      delay(100);
      //index-finger bent
      Serial.println(msg);
    }

    //MOTORS ARE E-H
    if (msg == 'S') {
      //&& XBee.read() == 'F' && XBee.read() == 'G'&& XBee.read() == 'H') {
      forward(Motor1, Motor2, 255);//all fingers down
      //   digitalWrite(forwardMotor1, HIGH);
      //   digitalWrite(forwardMotor2, HIGH);
      delay(100);
      Serial.println(msg);
    }
    if (msg == 'H') {
      back(Motor1, Motor2, -255);
      //   digitalWrite(backMotor1, HIGH);
      //   digitalWrite(backMotor2, HIGH);
      delay(100);
      //index-finger bent
      Serial.println(msg);
    }

    if (msg == 'G') {
      Motor1.drive(255);
      Motor2.drive(-255);
      delay(100);
      Serial.println(msg);
      //middle-finger bent//right-turn
      //   digitalWrite(forwardMotor1,HIGH);
      //   digitalWrite(backMotor2, HIGH);
    }

    if (msg == 'F') {
      Motor2.drive(255);
      Motor1.drive(-255);
      delay(100);
      Serial.println(msg);
      //ring-finger bent//left-turn
      //   digitalWrite(forwardMotor2,HIGH);
      //   digitalWrite(backMotor1, HIGH);

    }
    if (msg == 'P') {
      brake(Motor1, Motor2);//all fingers up
      delay(50);
      ROTATE.write(0);
      delay(100);
      SHOULDER.write(0);
      delay(100);
      ELBOW.write(0);
      delay(100);
      CLAW.write(0);
      delay(100);
      Serial.println(msg);
    }

  }
}





//
//if (XBee.available() && XBee.read() == 'E'){
//   backMotor1.drive(-255);//ring-finger
//   //digitalWrite(forwardMotor1 == HIGH);
// }
//
//if (XBee.available() && XBee.read() == 'E' && XBee.read() == 'H'){
//   backMotor2.drive(-255);//middle and ring-fingers
//}
//   digitalWrite(forwardMotor1,LOW);
//     digitalWrite(forwardMotor2,LOW);
//     digitalWrite(backMotor1, LOW);
//     digitalWrite(backMotor2, LOW);
//      brake(backMotor1, backMotor2);//all fingers up
//      delay(100);

//void loop(){
//  if (XBee.available()){
//    Serial.println(XBee.read());
//  }
//}
//Motor backMotor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
//Motor backMotor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
//
//if (XBee.available() && XBee.read() == 'c')
//{
//  Serial.print('c');
//
//}
//
//if (XBee.available() && XBee.read() == 'W'){
//  Serial.print('W');
//}
//
//if (XBee.available() && XBee.read() == 'S'){
//  Serial.print('S');
//}
//
//if (XBee.available() && XBee.read() == 'E'){
//  Serial.print('E');
//}
// Serial.println("working");


//while(Serial.available()>0) {
//           msg=Serial.read();
//           if(msg=='H') {
//               digitalWrite(led,HIGH);
//           }
//           if(msg=='L') {
//                digitalWrite(led,LOW);
//           }
//delay(100 );
//}
//
//  if (Serial.available() >=5 ) {
//   char incomingByte1 = Serial.read();
//   char incomingByte2 = Serial.read();
//   char incomingByte3 = Serial.read();
//   char incomingByte4 = Serial.read();
//   char incomingByte5 = Serial.read();
//
//   if(incomingByte1=='e'){  // if the first byte is an 'e' then we going to control the motors
//   int val_1 = incomingByte2-'0';
//   int val_2 = incomingByte3-'0';
//   int val_3 = incomingByte4-'0';
//   int val_4 = incomingByte5-'0';
//
//    // For debugging
//      Serial.println("Motor mode");
//      Serial.println(val_1);
//      Serial.println(val_2);
//      Serial.println(val_3);
//      Serial.println(val_4);
//      Serial.println();
//

//Drive forwards
//   if(val_1==0 && val_2==0 && val_3==0 && val_4==0 ){
//    digitalWrite(rightMotor1, LOW);
//    digitalWrite(rightMotor2, HIGH);
//    digitalWrite(leftMotor2, HIGH);
//    digitalWrite(leftMotor1, LOW);
//   }
//   //Drive backwards
//   else if(val_1==0 && val_2>0 && val_3>0 && val_4>0){
//    digitalWrite(rightMotor1, HIGH);
//    digitalWrite(rightMotor2, LOW);
//    digitalWrite(leftMotor2, LOW);
//    digitalWrite(leftMotor1, HIGH);
//   }
//   //Drive right
//     else if(val_1==0 && val_2>0 && val_3>0 && val_4==0){
//    digitalWrite(rightMotor1, LOW);
//    digitalWrite(rightMotor2, HIGH);
//    digitalWrite(leftMotor2, LOW);
//    digitalWrite(leftMotor1, LOW);
//   }
//   //Drive left
//      else if(val_1==0 && val_2>0 && val_3==0 && val_4==0){
//    digitalWrite(rightMotor1, LOW);
//    digitalWrite(rightMotor2, LOW);
//    digitalWrite(leftMotor2, HIGH);
//    digitalWrite(leftMotor1, LOW);
//   }
//
//   else if (val_1>0 && val_2>0 && val_3>0 && val_4>0){
//    digitalWrite(rightMotor1, LOW);
//    digitalWrite(rightMotor2, LOW);
//    digitalWrite(leftMotor2, LOW);
//    digitalWrite(leftMotor1, LOW);
//   }
//
//  }
//
//  else if (incomingByte1=='s'){ // if the first byte is 's' then we will control the robot arm
//   int val_1 = incomingByte2-'0';  // val_1 corresponds to the thumb
//   int val_2 = incomingByte3-'0';  // val_2 corresponds to index finger
//   int val_3 = incomingByte4-'0';  // val_3 corresponds to the middle finger
//   int val_4 = incomingByte5-'0';  // val_4 corresponds to the pinky
//
//     //For debugging
//      Serial.println("Robot arm mode");
//      Serial.println(val_1);
//      Serial.println(val_2);
//      Serial.println(val_3);
//      Serial.println(val_4);
//      Serial.println();
//
//
//    // Close claw
//    if(val_1==0 && val_2==0 && val_3==0 && val_4==0){
//     claw_ang-=5;
//     }
//     // Open claw
//     else if (val_1==0 && val_2>0 && val_3>0 && val_4>0){
//     claw_ang+=5;
//     }
//     // Tilt forward
//     else if (val_1==0 && val_2>0 && val_3>0 && val_4==0){
//     tilt_ang+=10;
//     }
//     //Tilt backward
//     else if (val_1==0 && val_2>0 && val_3==0 && val_4==0){
//     tilt_ang-=10;
//     }
//
//    if(claw_ang<0){
//       claw_ang=0;
//     }
//    if (claw_ang>145){
//       claw_ang=145;
//     }
//    if (tilt_ang<15){
//      tilt_ang=15;
//    }
//    if(tilt_ang>180){
//      tilt_ang=180;
//    }
//
//    // For debugging
//    Serial.println("Claw angle:");
//    Serial.println(claw_ang);
//    Serial.println();
//    Serial.println("Tilt angle:");
//    Serial.println(tilt_ang);
//    Serial.println();
//
//
//    claw.write(claw_ang);
//    delay(10);
//    tilt.write(tilt_ang);
//    delay(10);
//
//  }
//
//  }
//  delay(10);


