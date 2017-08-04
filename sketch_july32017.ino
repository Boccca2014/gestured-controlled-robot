//Constants:
//const int buttonPin = 2;
//const int ledPin = 13;   //pin 3 has PWM funtion
const int FLEX_PIN[] = {A0, A1, A2, A3};

//const int flexPin = A0; //pin A0 to read analog input

//Variables:
int value0; //save analog value
int value1;
int value2;
int value3;
int buttonState = 0;

#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3);


int buttonPin = 2;         // the number of the input pin
int ledPin = 13;       // the number of the output pin
int ledState = HIGH;

//int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 500;   // the debounce time, increase if the output flickers
//checkbutton = digitalRead(buttonPin);

void setup() {
  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);       //Begin serial communication
  XBee.begin(9600);

}

void loop() {
  //  reading = digitalRead(buttonPin);
  //
  //  // if the input just went from LOW and HIGH and we've waited long enough
  //  // to ignore any noise on the circuit, toggle the output pin and remember
  //  // the time
  //  if (reading == HIGH && previous == LOW) { //&& millis() - time > debounce
  //    if (state == HIGH)
  //      state = LOW;
  //    else
  //      state = HIGH;
  //
  //    //time = millis();
  //  }
  //
  //  digitalWrite(ledPin, state);
  //
  //  previous = reading;
  //  Serial.println("button checked");
  // ledState = digitalRead(ledPin);
  //  //buttonState = digitalRead(buttonPin);

  //value3 is the index-finger
  value0 = analogRead(FLEX_PIN[0]);  //Read and save analog value from potentiometer
  value1 = analogRead(FLEX_PIN[1]);
  value2 = analogRead(FLEX_PIN[2]);
  value3 = analogRead(FLEX_PIN[3]);

  value0 = map(value0, 0, 1023, 0, 100);//Map value 0-1023 to 0-255 (PWM)
  value1 = map(value1, 0, 1023, 0, 100);
  value2 = map(value2, 0, 1023, 0, 100);
  value3 = map(value3, 0, 1023, 0, 100);


  //  Serial.println(value0);               //Print value
  //  Serial.println(value1);
  //  Serial.println(value2);
  //  Serial.println(value3);
  //  Serial.println(" ");
  delay(100);

  /*
    value0 = map(value0, 0, 650, 0, 10);//Map value 0-1023 to 0-255 (PWM)
    //value0 = constrain(value0, 0, 100);
    value1 = map(value1, 0, 650, 0, 10);
    //value1 = constrain(value1, 0, 100);
    value2 = map(value2, 0, 650, 0, 10);
    // value2 = constrain(value2, 0, 100);
    value3 = map(value3, 0, 650, 0, 10);
    // value3 = constrain(value3, 0, 100);
  */

  //  analogWrite(ledPin, value0);          //Send PWM value to led
  //  analogWrite(ledPin, value1);
  //  analogWrite(ledPin, value2);
  //  analogWrite(ledPin, value3);
  //Small delay
  sensorcheck();
  //Serial.println("sense");
  checkbutton();
  //Serial.println("toggle");

  //MOTORS
  while (ledState == LOW) {
    sensorcheck();
    //Serial.println("MOTORsense");
    checkbutton();
    //Serial.println("MOTOR");
    delay(300);
    if (value0 < 50 && value1 < 50 && value2 < 50 && value3 < 50) {
      //buttonState == LOW;
      //digitalWrite(ledPin, LOW);
      Serial.print('S');//all fingers down
      XBee.write('S');
    }
    if (value0 < 50 && value1 > 50 && value2 > 50 && value3 > 50) {
      //    buttonState == LOW;
      Serial.println('E');
      XBee.write('E');
      //    digitalWrite(ledPin, LOW);
    }
    if (value1 < 50 && value0 > 50 && value2 > 50 && value3 > 50) {
      //    buttonState == LOW;
      Serial.println('F');
      XBee.write('F');
      //ring-finger bent//left-turn
      //    digitalWrite(ledPin, LOW);
    }
    if (value2 < 50 && value0 > 50 && value1 > 50 && value3 > 50) {
      //    buttonState == LOW;
      Serial.println('G');
      XBee.write('G');
      //middle-finger bent//right-turn
      //    digitalWrite(ledPin, LOW);
    }
    if (value3 < 50 && value0 > 50 && value1 > 50 && value2 > 50) { //backwards= 
      //    buttonState == LOW;
      Serial.println('H');//index-finger bent
      XBee.write('H');
      //    digitalWrite(ledPin, LOW);
    }

    if (value0 > 50 && value1 > 50 && value2 > 50 && value3 > 50) {
      //  buttonState == LOW;
      //digitalWrite(ledPin, LOW);
      Serial.print('P');
      XBee.write('P');
      //all fingers up
    }
  }


  //CLAW or SERVOS
  while (ledState == HIGH) {
    sensorcheck();
    //Serial.println("SERVOsense");
    checkbutton();
    //Serial.println("SERVO");
    delay(300);
    //SHOULDER AND ELBOW???
    //    if (value0 > 50 && value1 > 50 && value2 > 50 && value3 > 50) {
    //      Serial.println('A');
    //      XBee.write('A');
    //      // digitalWrite(ledPin, HIGH);
    //    }
    if (value0 < 50 && value1 < 50 && value2 > 50 && value3 > 50) {
      Serial.println('B');
      XBee.write('B');
      //ring and pinky bent
      // digitalWrite(ledPin, HIGH);
    }
    if (value0 < 50 && value1 < 50 && value2 < 50 && value3 > 50) {
      Serial.println('L');
      XBee.write('L');
      //middle, ring, and pinky bent
      // digitalWrite(ledPin, HIGH);
    }

    //ROTATE
    //    if (value2 > 50) {
    //      Serial.println('D');
    //      XBee.write('D');
    //      //  digitalWrite(ledPin, HIGH);
    //    }
    if (value2 < 50 && value0 > 50 && value1 > 50 && value3 > 50) {
      Serial.println('M');
      XBee.write('M');
      //middle-finger down
      //  digitalWrite(ledPin, HIGH);
    }
    if (value2 < 50 && value1 < 50 && value0 > 50 && value3 > 50) {
      Serial.println('T');
      XBee.write('T');
      //middle and ring-fingers bent
      //  digitalWrite(ledPin, HIGH);
    }

    //CLAW
    //    if (value3 > 50) {
    //      //  buttonState == LOW;
    //      //digitalWrite(ledPin, LOW);
    //      Serial.print('C');
    //      XBee.write('C');
    //    }
    if (value3 < 50 && value0 > 50 && value1 > 50 && value2 > 50) {
      Serial.println('O');
      XBee.write('O');
      //index-finger bent
      // digitalWrite(ledPin, HIGH);
    }

    if (value0 > 50 && value1 > 50 && value2 > 50 && value3 > 50) {
      //  buttonState == LOW;
      //digitalWrite(ledPin, LOW);
      Serial.print('P');
      XBee.write('P');
      //all fingers up
    }
  }

  //  if (value0 > 50 && value1 > 50 && value2 > 50 && value3 > 50) {
  //    //  buttonState == LOW;
  //    //digitalWrite(ledPin, LOW);
  //    Serial.print('');
  //    XBee.write('');
  //  }

}

void checkbutton() {
  reading = digitalRead(buttonPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW) { //&& millis() - time > debounce
    if (ledState == HIGH)
      ledState = LOW;
    else
      ledState = HIGH;

    //time = millis();
  }

  digitalWrite(ledPin, ledState);
  previous = reading;
  Serial.println("working");
  Serial.println(ledState);
}

void sensorcheck() {
  value0 = analogRead(FLEX_PIN[0]);  //Read and save analog value from potentiometer
  value1 = analogRead(FLEX_PIN[1]);
  value2 = analogRead(FLEX_PIN[2]);
  value3 = analogRead(FLEX_PIN[3]);

  value0 = map(value0, 0, 1023, 0, 100);//Map value 0-1023 to 0-255 (PWM)
  value1 = map(value1, 0, 1023, 0, 100);
  value2 = map(value2, 0, 1023, 0, 100);
  value3 = map(value3, 0, 1023, 0, 100);


  Serial.println(value0);               //Print value
  Serial.println(value1);
  Serial.println(value2);
  Serial.println(value3);
  Serial.println(" ");
  delay(100);
}





//  if (FLEX_PIN[0] < 50 && buttonState == HIGH){
//    buttonState == HIGH;
//    Serial.print('E');
//    XBee.write('E');
//    digitalWrite(ledPin, HIGH);
//  }
//  if (FLEX_PIN[1] < 50 && buttonState == HIGH){
//    buttonState == HIGH;
//    Serial.print('F');
//    XBee.write('F');
//    digitalWrite(ledPin, HIGH);
//    }
// if (FLEX_PIN[2] < 50){
//    buttonState == HIGH;
//    Serial.print('G');
//    XBee.write('G');
//    digitalWrite(ledPin, HIGH);
//  }
// if (FLEX_PIN[3] < 50){
//   buttonState == HIGH;
//   Serial.print('H');
//   XBee.write('H');
//   digitalWrite(ledPin, HIGH);
//  }

//    if (value1 < 50) {
//      Serial.println('B');
//      XBee.write('B');
//      // digitalWrite(ledPin, HIGH);
//    }










//flat0= 5,flat1= 3,flat2= 3,flat3= 3
//bend0= 9,bend1= 6,bend2= 6,bend3= 6

//flat0= 656,flat1= 366,flat2= 391,flat3= 583
//bend0= 440,bend1= 280,bend2= 320,bend3= 360

//flat(B)= flex1 is -20, flex2 is 76, flex3 is 63, flex4 is -5
//bentdown(B)= flex1 is 70, flex2 is 158, flex3 is 124, flex4 is 85

//flat(R)= flex1 is 25000, flex2 is 81000, flex3 is 74000, flex4 is 34000
//bentdown(R)= flex1 is 80000, flex2 is 120000, flex3 is 100000, flex4 is 89000


/*
  const int FLEX_PIN[] = {A0, A1, A2, A3};

  // Measure the voltage at 5V and the actual resistance of your
  // 47k resistor, and enter them below:
  const float VCC = 4.98; // Measured voltage of Ardunio 5V line
  const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor

  // Upload the code, then try to adjust these values to more
  // accurately calculate bend degree.
  const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
  const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

  void setup()
  {
  Serial.begin(9600);
  pinMode(FLEX_PIN[0], INPUT);
  pinMode (FLEX_PIN[1], INPUT);
  pinMode (FLEX_PIN[2], INPUT);
  pinMode (FLEX_PIN[3], INPUT);
  }

  //when bent down, A0 (gray) goes up, A1 (green) goes down, A2 (purple) goes down, A3 (black) goes up
  void loop()
  {
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC0 = analogRead(FLEX_PIN[0]);
  int flexADC1 = analogRead(FLEX_PIN[1]);
  int flexADC2 = analogRead(FLEX_PIN[2]);
  int flexADC3 = analogRead(FLEX_PIN[3]);


  float flexV0 = flexADC0 * VCC / 1023.0;
  float flexR0 = R_DIV * (VCC / flexV0 - 1.0);
  Serial.println("Resistance: " + String(flexR0) + " ohms");

   float flexV1 = flexADC1 * VCC / 1023.0;
  float flexR1 = R_DIV * (VCC / flexV1 - 1.0);
  Serial.println("Resistance: " + String(flexR1) + " ohms");

   float flexV2 = flexADC2 * VCC / 1023.0;
  float flexR2 = R_DIV * (VCC / flexV2 - 1.0);
  Serial.println("Resistance: " + String(flexR2) + " ohms");

   float flexV3 = flexADC3 * VCC / 1023.0;
  float flexR3 = R_DIV * (VCC / flexV3 - 1.0);
  Serial.println("Resistance: " + String(flexR3) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle0 = map(flexR0, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);
  float angle1 = map(flexR1, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);
  float angle2 = map(flexR2, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);
  float angle3 = map(flexR3, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);
  Serial.println("Bend: " + String(angle0) + " degrees");
  Serial.println("Bend: " + String(angle1) + " degrees");
  Serial.println("Bend: " + String(angle2) + " degrees");
  Serial.println("Bend: " + String(angle3) + " degrees");
  Serial.println();

  delay(1500);
  }
*/

