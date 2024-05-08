//Parker Murphy and Frederick Levins
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#define DECODE_NEC
#include <Servo.h>
#include <IRremote.hpp>
#define IR_Pin 10
#define sf 1
#define f 2
#define ff 3
#define sb 4
#define b 5
#define fb 6
#define sl 7
#define l 8
#define fl 9
#define sr 10
#define r 11
#define fr 12
#define sf_sl 13
#define sf_l 14
#define sf_fl 15
#define sf_sr 16
#define sf_r 17
#define sf_fr 18
#define f_sl 19
#define f_l 20
#define f_fl 21
#define f_sr 22
#define f_r 23
#define f_fr 24
#define ff_sl 25
#define ff_l 26
#define ff_fl 27
#define ff_sr 28
#define ff_r 29
#define ff_fr 30
#define sb_sl 31
#define sb_l 32
#define sb_fl 33
#define sb_sr 34
#define sb_r 35
#define sb_fr 36
#define b_sl 37
#define b_l 38
#define b_fl 39
#define b_sr 40
#define b_r 41
#define b_fr 42
#define fb_sl 43
#define fb_l 44
#define fb_fl 45
#define fb_sr 46
#define fb_r 47
#define fb_fr 48
#define stop 0


int code = 0;
int slowr = 110;
int slowl = 90;
int regr = 140;
int regl = 120;
int fastr = 150;
int fastl = 140;


const int LWhFwdPin = A0;
const int LWhBwdPin = 7;
const int LWhPWMPin = 6;

const int RWhFwdPin = A1;
const int RWhBwdPin = 4;
const int RWhPWMPin = 5;

 Servo myServo;  // servo object to control ultrasonic servo
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {

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

  analogWrite(LWhPWMPin, regl);
  analogWrite(RWhPWMPin, regr);

  pinMode(IR_Pin, INPUT);
  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);

  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();
  lcd.print("PlantBot By F&P");
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
    case stop:
      digitalWrite(LWhFwdPin, LOW);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, LOW);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, regr);
      break;
    case sf:
      fwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, slowr);
      break;
    case f:
      fwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, regr);
      break;
    case ff:
      fwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, fastr);
      break;
    case sb:
      bwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, slowr);
      break;
    case b:
      bwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, regr);
      break;
    case fb:
      bwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, fastr);
      break;
    case sl:
      lft();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, slowr+20);
      break;
    case l:
      lft();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, regr+20);
      break;
    case fl:
      lft();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, fastr+20);
      break;
    case sr:
      rgt();
      analogWrite(LWhPWMPin, slowl+20);
      analogWrite(RWhPWMPin, slowr);
      break;
    case r:
      rgt();
      analogWrite(LWhPWMPin, regl+20);
      analogWrite(RWhPWMPin, regr);
      break;
    case fr:
      rgt();
      analogWrite(LWhPWMPin, fastl+20);
      analogWrite(RWhPWMPin, fastr);
      break;
    case sf_sl:
      fwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, (slowr+20));
      break;
    case sf_l:
      fwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, (slowr+20));
      break;
    case sf_fl:
      fwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, (slowr+20));
      break;
    case sf_sr:
      fwd();
      analogWrite(LWhPWMPin, (slowl+20));
      analogWrite(RWhPWMPin, slowr);
      break;
    case sf_r:
      fwd();
      analogWrite(LWhPWMPin, (slowl+20));
      analogWrite(RWhPWMPin, slowr);
      break;
    case sf_fr:
      fwd();
      analogWrite(LWhPWMPin, (slowl+20));
      analogWrite(RWhPWMPin, slowr);
      break;
    case f_sl:
      fwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, (regr+20));
      break;
    case f_l:
      fwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, (regr+20));
      break;
    case f_fl:
      fwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, (regr+20));
      break;
    case f_sr:
      fwd();
      analogWrite(LWhPWMPin, (regl+20));
      analogWrite(RWhPWMPin, regr);
      break;
    case f_r:
      fwd();
      analogWrite(LWhPWMPin, (regl+20));
      analogWrite(RWhPWMPin, regr);
      break;
    case f_fr:
      fwd();
      analogWrite(LWhPWMPin, (regl+20));
      analogWrite(RWhPWMPin, regr);
      break;
    case ff_sl:
      fwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, (fastr+20));
      break;
    case ff_l:
      fwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, (fastr+20));
      break;
    case ff_fl:
      fwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, (fastr+20));
      break;
    case ff_sr:
      fwd();
      analogWrite(LWhPWMPin, (fastl+20));
      analogWrite(RWhPWMPin, fastr);
      break;
    case ff_r:
      fwd();
      analogWrite(LWhPWMPin, (fastl+20));
      analogWrite(RWhPWMPin, fastr);
      break;
    case ff_fr:
      fwd();
      analogWrite(LWhPWMPin, (fastl+20));
      analogWrite(RWhPWMPin, fastr);
      break;
    case sb_sl:
      bwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, (slowr+20));
      break;
    case sb_l:
      bwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, (slowr+20));
      break;
    case sb_fl:
      bwd();
      analogWrite(LWhPWMPin, slowl);
      analogWrite(RWhPWMPin, (slowr+20));
      break;
    case sb_sr:
      bwd();
      analogWrite(LWhPWMPin, (slowl+20));
      analogWrite(RWhPWMPin, slowr);
      break;
    case sb_r:
      bwd();
      analogWrite(LWhPWMPin, (slowl+20));
      analogWrite(RWhPWMPin, slowr);
      break;
    case sb_fr:
      bwd();
      analogWrite(LWhPWMPin, (slowl+20));
      analogWrite(RWhPWMPin, slowr);
      break;
    case b_sl:
      bwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, (regr+20));
      break;
    case b_l:
      bwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, (regr+20));
      break;
    case b_fl:
      bwd();
      analogWrite(LWhPWMPin, regl);
      analogWrite(RWhPWMPin, (regr+20));
      break;
    case b_sr:
      bwd();
      analogWrite(LWhPWMPin, (regl+20));
      analogWrite(RWhPWMPin, regr);
      break;
    case b_r:
      bwd();
      analogWrite(LWhPWMPin, (regl+20));
      analogWrite(RWhPWMPin, regr);
      break;
    case b_fr:
      bwd();
      analogWrite(LWhPWMPin, (regl+20));
      analogWrite(RWhPWMPin, regr);
      break;
    case fb_sl:
      bwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, (fastr+20));
      break;
    case fb_l:
      bwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, (fastr+20));
      break;
    case fb_fl:
      bwd();
      analogWrite(LWhPWMPin, fastl);
      analogWrite(RWhPWMPin, (fastr+20));
      break;
    case fb_sr:
      bwd();
      analogWrite(LWhPWMPin, (fastl+20));
      analogWrite(RWhPWMPin, fastr);
      break;
    case fb_r:
      bwd();
      analogWrite(LWhPWMPin, (fastl+20));
      analogWrite(RWhPWMPin, fastr);
      break;
    case fb_fr:
      bwd();
      analogWrite(LWhPWMPin, (fastl+20));
      analogWrite(RWhPWMPin, fastr);
      break;
  }
  IrReceiver.resume();
}
void fwd() {
  digitalWrite(LWhFwdPin, HIGH);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(RWhFwdPin, HIGH);
  digitalWrite(RWhBwdPin, LOW);
}
void bwd() {
  digitalWrite(LWhFwdPin, LOW);
  digitalWrite(LWhBwdPin, HIGH);
  digitalWrite(RWhFwdPin, LOW);
  digitalWrite(RWhBwdPin, HIGH);
}
void lft() {
  digitalWrite(LWhFwdPin, LOW);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(RWhFwdPin, HIGH);
  digitalWrite(RWhBwdPin, LOW); 
}
void rgt() {
  digitalWrite(LWhFwdPin, HIGH);
  digitalWrite(LWhBwdPin, LOW);
  digitalWrite(RWhFwdPin, LOW);
  digitalWrite(RWhBwdPin, LOW);
}