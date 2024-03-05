//Parker Murphy and Frederick Levins

#define DECODE_NEC
#include <Servo.h>
#include <IRremote.hpp>
#define IR_Pin 8
#define forward 24
#define backward 82
#define right 90
#define left 8
#define stop 28
//#define slow 7
//#define fast 21
//#define resetSpeed 9

Servo myservo;

int code = 0;
int RSPD1 = 255;  //Right Wheel PWM
int LSPD1 = 255;  //Left Wheel PWM
int RSPD2 = 255;  //Right Wheel PWM
int LSPD2 = 255;  //Left Wheel PWM


const int LWhFwdPin = 7;
const int LWhBwdPin = 5;
const int LWhPWMPin = 10;

const int RWhFwdPin = 4;
const int RWhBwdPin = 2;
const int RWhPWMPin = 9;

void setup() {
  myservo.attach(6);
  myservo.write(90);
  //Serial.begin(9600);

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

  analogWrite(LWhPWMPin,LSPD1);
  analogWrite(RWhPWMPin,RSPD1);

  pinMode(IR_Pin, INPUT);
  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);
  
}


void loop() {
  if (IrReceiver.decode()) {
    
    remoteDrive();
  }
}

void remoteDrive() {
  Serial.print("code=");
  code = IrReceiver.decodedIRData.command;
  Serial.println(code);
  switch (code) {
    case forward:
      digitalWrite(LWhFwdPin, HIGH);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, HIGH);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,RSPD1);
      break;
    case backward:
      digitalWrite(LWhFwdPin, LOW);
      digitalWrite(LWhBwdPin, HIGH);
      digitalWrite(RWhFwdPin, LOW);
      digitalWrite(RWhBwdPin, HIGH);
      analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,RSPD1);
      break;
    case right:
      digitalWrite(LWhFwdPin, HIGH);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, LOW);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin,LSPD2);
      analogWrite(RWhPWMPin,RSPD1);
      break;
    case left:
      digitalWrite(LWhFwdPin, LOW);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, HIGH);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,RSPD2);
      break;
    case stop:
      digitalWrite(LWhFwdPin, LOW);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, LOW);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,RSPD1);
      break;
    /*case slow:
      if(RSPD1<2) {
        break;
      }
      if(LSPD1<2) {
        break;
      }
      RSPD1=RSPD1/2;
      LSPD1=LSPD1/2;
      break;
    case fast:
      if(RSPD1>170) {
        break;
      }
      if(LSPD1>170) {
        break;
      }
      RSPD1=RSPD1*1.5;
      LSPD1=LSPD1*1.5;
      break;
    case resetSpeed:
      RSPD1=130;
      LSPD1=230;
      break;
      */
  }
  IrReceiver.resume();

}