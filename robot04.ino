/* Parker Murphy and Frederick Levins
 */
 #include <Servo.h>
 #include <Wire.h> // Library for I2C communication
 #include <LiquidCrystal_I2C.h> // Library for LCD
 #define DECODE_NEC
 #include <IRremote.hpp>
 #define IR_Pin 10
 #define forward 24
 #define backward 82
 #define stop 28
 #define left 8
 #define right 90

 // Wiring: SDA pin is connected to A4 and SCL pin to A5. for US

 const int RSPD1 = 170;        //Right Wheel PWM.  Change this value so your car will go roughly straight
 const int LSPD1 = 150;        //Left Wheel PWM
 const int RSPD2 = 150;        //Right Wheel PWM
 const int LSPD2 = 150;        //Left Wheel PWM
 
 const int LWhFwdPin = A0;//10;   
 const int LWhBwdPin = 7;//A5;
 const int LWhPWMPin = 6;//11;

 const int RWhFwdPin = A1;//7;
 const int RWhBwdPin = 4;//6;
 const int RWhPWMPin = 5; 

 const int leftInterupt = 3;
 const int rightInterupt = 2;

 const int myServoPin = 11;


 const int pingPin = A2; // trigger
 const int echoPin = A3; // echo

 Servo myServo;  // servo object to control ultrasonic servo
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

 int gain=12;
 int delCntr=0; 
 volatile long cntrL, cntrR;
 volatile long LIntTime, RIntTime;

 long stopTime;
 int code = 0;
 int leftTurn = 0;
 int rndm=1;
// week 4
  long cntrPerDeg = .83; // 74.84 / 90
  long cntrT = 90 * cntrPerDeg + 0.5; 

void setup() 
{
  Serial.begin(9600);
  myServo.attach(myServoPin);
  myServo.write(90);
  lcd.init();
  lcd.backlight();  

  pinMode(LWhFwdPin,OUTPUT);
  pinMode(LWhBwdPin,OUTPUT);
  pinMode(LWhPWMPin,OUTPUT);
  pinMode(RWhFwdPin,OUTPUT);
  pinMode(RWhBwdPin,OUTPUT);
  pinMode(RWhPWMPin,OUTPUT);

  digitalWrite(LWhFwdPin,LOW);
  digitalWrite(LWhBwdPin,LOW);
  digitalWrite(LWhPWMPin,LOW);
  
  digitalWrite(RWhFwdPin,LOW);
  digitalWrite(RWhBwdPin,LOW);
  digitalWrite(RWhPWMPin,LOW);

  attachInterrupt(digitalPinToInterrupt(leftInterupt), leftWhlCnt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightInterupt), rightWhlCnt, CHANGE);
   
  cntrR = 0;
  cntrL = 0;
  LIntTime = 0;
  RIntTime = 0;
 
  //digitalWrite(LWhFwdPin,HIGH);    //run left wheel forward
  //digitalWrite(RWhFwdPin,HIGH);    //run right wheel forward
  analogWrite(RWhPWMPin,RSPD1);     //turn on wheels 
  analogWrite(LWhPWMPin,LSPD1);
  //stopTime = micros() + 10*1000000; 
  pinMode(IR_Pin, INPUT);
  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);

  //Week 4 US
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();
  
}

void loop() 
{

  /*
  // Week 4 Ultra
  long duration, inches;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  delay(100);


  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  if (inches <= 4) {
    hardTurnLeft();
    delay(100); // testing period
  }
  // pushing to screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inches: ");
  lcd.print(inches);
  */
  //delay(2000);
  //hardTurnLeft();
// End Week 4 Ultra

  long tmpLcntr, tmpRcntr;
  tmpLcntr = cntrL;
  tmpRcntr = cntrR;
  delCntr = abs(tmpLcntr - tmpRcntr);
  if(tmpLcntr > tmpRcntr)
  {
    analogWrite(RWhPWMPin,RSPD1);
    analogWrite(LWhPWMPin,max(LSPD1-int(gain*delCntr+.5),0));
  }
  else if(tmpLcntr > tmpRcntr) {
    if(leftTurn == 1) {
      rndm=1;
    }
    else{
      //analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,max(RSPD1-int(gain*delCntr+.5),0));
    }
  }
  else if(tmpLcntr==tmpRcntr)
  {
    leftTurn=0;
    analogWrite(RWhPWMPin,RSPD1);
    analogWrite(LWhPWMPin,LSPD1);
  }
  if (IrReceiver.decode()) {
    cntrL=0;
    cntrR=0;
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
    case left: //8 and 90
      leftTurn=1;
      //while (tmpRcntr < (tmpLcntr + cntrT)) { 
      analogWrite(LWhPWMPin,0);
      analogWrite(RWhPWMPin,RSPD1);
      digitalWrite(LWhFwdPin, HIGH);
      digitalWrite(RWhFwdPin, HIGH); 
      cntrR = 0;
      cntrL = cntrT;
      //}
      //digitalWrite(LWhFwdPin, LOW);
      //digitalWrite(RWhFwdPin, LOW);
    break;
    case stop:
      digitalWrite(LWhFwdPin, LOW);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, LOW);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,RSPD1);
      break;
    }
  IrReceiver.resume();


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
    case left: //8 and 90
      hardTurnLeft();
    case stop:
      digitalWrite(LWhFwdPin, LOW);
      digitalWrite(LWhBwdPin, LOW);
      digitalWrite(RWhFwdPin, LOW);
      digitalWrite(RWhBwdPin, LOW);
      analogWrite(LWhPWMPin,LSPD1);
      analogWrite(RWhPWMPin,RSPD1);
      break;
    }
  IrReceiver.resume();

}

void leftWhlCnt()
{
  long intTime = micros();
  if(intTime > LIntTime + 1000L)
  {
    LIntTime = intTime;
    cntrL++;
  }
}

void rightWhlCnt()  // Complete this ISR
{
  long intTime = micros();
  if(intTime > RIntTime + 1000L)
  {
    RIntTime = intTime;
    cntrR++;
  }
}

/*
// Week 4
void hardTurnRight() { 
  volatile long oldcntrL = cntrL;
  volatile long oldcntrR = cntrR;
  cntrL = 0;
  cntrR = 0;

  // calcs 
  long cntrPerDeg = .83; //change 
  long cntrT = 90 * cntrPerDeg + 0.5; 


  while (cntrL < cntrT) { 
    analogWrite(RWhPWMPin,0);
    analogWrite(LWhPWMPin,LSPD1); 
  }

  cntrL = oldcntrL;
  cntrR = oldcntrR;
}

// Week 4
void hardTurnLeft() { 
  volatile long oldcntrL = cntrL;
  volatile long oldcntrR = cntrR;
  cntrL = 0;
  cntrR = 0;

  // calcs 
  // r = 4.5in, C = 1/4, W = 8.5in/40 (segments of encoder) = dist of 90deg turn:(pi*4.5^2)/4, Cnt = d/C = 74.84 = 75
  long cntrPerDeg = .83; // 74.84 / 90
  long cntrT = 90 * cntrPerDeg + 0.5; 


  while (cntrR < (cntrL + cntrT)) { 
    analogWrite(LWhPWMPin,0);
    analogWrite(RWhPWMPin,RSPD1);
    digitalWrite(LWhFwdPin, HIGH);
    digitalWrite(RWhFwdPin, HIGH); 

  }

  digitalWrite(LWhFwdPin, LOW);
  digitalWrite(RWhFwdPin, LOW);
  cntrL = oldcntrL;
  cntrR = oldcntrR;
}
*/
// Week 4

// keep for ultra
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
