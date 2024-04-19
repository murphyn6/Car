/* Fred, Parker*/
#include <Servo.h>
#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD
#define DECODE_NEC
#include <IRremote.hpp>
#define IR_Pin 10
#define forward 24
#define backward 82
#define stop 28
#define left 8
#define right 90

const int RSPD1 = 160;  //Right Wheel PWM.  Change this value so your car will go roughly straight
const int LSPD1 = 140;  //Left Wheel PWM
const int RSPD2 = 150;  //Right Wheel PWM
const int LSPD2 = 150;  //Left Wheel PWM

const int LWhFwdPin = A0;  //10;
const int LWhBwdPin = 7;   //A5;
const int LWhPWMPin = 6;   //11;

const int RWhFwdPin = A1;  //7;
const int RWhBwdPin = 4;   //6;
const int RWhPWMPin = 5;

const int leftInterupt = 3;
const int rightInterupt = 2;

const int myServoPin = 11;

const int pingPin = 13;  // trigger
const int echoPin = 12;  // echo

Servo myServo;  // servo object to control ultrasonic servo
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int gain=5;
int delCntr = 0;
volatile long cntrL, cntrR;
volatile long LIntTime, RIntTime;
long stopTime;
int code = 0;
int oldcntrL;
int oldcntrR;

void setup() {
  Serial.begin(9600);
  myServo.attach(myServoPin);
  myServo.write(90);

  pinMode(LWhFwdPin, OUTPUT);
  pinMode(LWhBwdPin, OUTPUT);
  pinMode(LWhPWMPin, OUTPUT);
  pinMode(RWhFwdPin, OUTPUT);
  pinMode(RWhBwdPin, OUTPUT);
  pinMode(RWhPWMPin, OUTPUT);

  digitalWrite(LWhFwdPin, LOW);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(LWhPWMPin, LOW);

  digitalWrite(RWhFwdPin, LOW);
  digitalWrite(RWhBwdPin, LOW);
  digitalWrite(RWhPWMPin, LOW);

  attachInterrupt(digitalPinToInterrupt(leftInterupt), leftWhlCnt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightInterupt), rightWhlCnt, CHANGE);

  cntrR = 0;
  cntrL = 0;
  LIntTime = 0;
  RIntTime = 0;
  analogWrite(RWhPWMPin, RSPD1);  //turn on wheels
  analogWrite(LWhPWMPin, LSPD1);
  pinMode(IR_Pin, INPUT);
  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);

  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();
}

void loop() {
  /*lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Left: ");
  lcd.print(cntrL);
  lcd.setCursor(0, 1);
  lcd.print("Right: ");
  lcd.print(cntrR);*/


  long duration, inches;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inches: ");
  lcd.print(inches);

  long tmpLcntr, tmpRcntr;
  tmpLcntr = cntrL;
  tmpRcntr = cntrR;
  delCntr = abs(tmpLcntr - tmpRcntr);

  if(inches<7 && inches!=0){
    stopCar();
    delay(1000);
    turnLeft();
    stopCar();
    delay(1000);
    goForward();
  }

  if (tmpLcntr > tmpRcntr) {
    analogWrite(RWhPWMPin, RSPD1);
    analogWrite(LWhPWMPin, max(LSPD1 - int(gain * delCntr + .5), 0));
  } else if (tmpLcntr < tmpRcntr) {
    analogWrite(LWhPWMPin, LSPD1);
    analogWrite(RWhPWMPin, max(RSPD1 - 1.16*int(gain * delCntr + .5), 0));
  } else {
    analogWrite(RWhPWMPin, RSPD1);
    analogWrite(LWhPWMPin, LSPD1);
  }
  
  if (IrReceiver.decode()) {
    cntrL = 0;
    cntrR = 0;
    remoteDrive();
  }
}

void remoteDrive() {
  Serial.print("code=");
  code = IrReceiver.decodedIRData.command;
  Serial.println(code);
  switch (code) {
    case forward:
      goForward();
      break;
    case left:
      turnLeft();
      break;
    case backward:
      goBackward();
      break;
    case stop:
      stopCar();
      break;
  }
  IrReceiver.resume();
}

void leftWhlCnt() {
  long intTime = micros();
  if (intTime > LIntTime + 5000L) {
    LIntTime = intTime;
    cntrL++;
  }
}

void rightWhlCnt()  // Complete this ISR
{
  long intTime = micros();
  if (intTime > RIntTime + 5000L) {
    RIntTime = intTime;
    cntrR++;
  }
}

void turnLeft() {
  digitalWrite(LWhFwdPin, HIGH);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(RWhFwdPin, HIGH);
  digitalWrite(RWhBwdPin, LOW);
  oldcntrL = cntrL;
  oldcntrR = cntrR;
  cntrL = 0;
  cntrR = 0;
  while (cntrR < (cntrL + 40)) {
    analogWrite(RWhPWMPin, RSPD1);
    analogWrite(LWhPWMPin, 0);
  }
  cntrL = oldcntrL;
  cntrR = oldcntrR;
}

void goForward() {
  digitalWrite(LWhFwdPin, HIGH);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(RWhFwdPin, HIGH);
  digitalWrite(RWhBwdPin, LOW);
  analogWrite(LWhPWMPin, LSPD1);
  analogWrite(RWhPWMPin, RSPD1);
}
void goBackward() {
  digitalWrite(LWhFwdPin, LOW);
  digitalWrite(LWhBwdPin, HIGH);
  digitalWrite(RWhFwdPin, LOW);
  digitalWrite(RWhBwdPin, HIGH);
  analogWrite(LWhPWMPin, LSPD1);
  analogWrite(RWhPWMPin, RSPD1);
}
void stopCar() {
  digitalWrite(LWhFwdPin, LOW);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(RWhFwdPin, LOW);
  digitalWrite(RWhBwdPin, LOW);
  analogWrite(LWhPWMPin, LSPD1);
  analogWrite(RWhPWMPin, RSPD1);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
