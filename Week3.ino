/* Run Wheels and Servo
 */
 const int RSPD1 = 150;        //Right Wheel PWM.  Change this value so your car will go roughly straight
 const int LSPD1 = 115;        //Left Wheel PWM
 const int RSPD2 = 150;        //Right Wheel PWM
 const int LSPD2 = 150;        //Left Wheel PWM
 
 const int LWhFwdPin = 9;   
 const int LWhBwdPin = 8;
 const int LWhPWMPin = 11;

 const int RWhFwdPin = 7;
 const int RWhBwdPin = 6;
 const int RWhPWMPin = 5; 

 const int leftInterupt = 3;
 const int rightInterupt = 2;

 const int ultraServoPin = 4;
 #include <Servo.h>
 #include <Wire.h> // Library for I2C communication
 #include <LiquidCrystal_I2C.h> // Library for LCD
 Servo ultraServo;  // servo object to control ultrasonic servo
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

 int gain=12;
 int delCntr=0; 
 volatile long cntrL, cntrR;
 volatile long LIntTime, RIntTime;
 long stopTime;

void setup() 
{
  Serial.begin(9600);
  ultraServo.attach(ultraServoPin);
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
  pinMode(leftInterupt, INPUT_PULLUP);
  pinMode(rightInterupt, INPUT_PULLUP);
  attachInterrupt(leftInterupt, leftWhlCnt, CHANGE);
  attachInterrupt(rightInterupt, rightWhlCnt, CHANGE);
   
  cntrR = 0;
  cntrL = 0;
  LIntTime = 0;
  RIntTime = 0;
 
  digitalWrite(LWhFwdPin,HIGH);    //run left wheel forward
  digitalWrite(RWhFwdPin,HIGH);    //run right wheel forward
  analogWrite(RWhPWMPin,RSPD1);     //turn on wheels 
  analogWrite(LWhPWMPin,LSPD1);
  stopTime = micros() + 5*1000000; 
}

void loop() 
{
  delay(100);
  long tmpLcntr, tmpRcntr;
  tmpLcntr = cntrL;
  tmpRcntr = cntrR;
  delCntr = abs(tmpLcntr - tmpRcntr);
  Serial.print("Left Counter: ");
  Serial.println(tmpLcntr);
  Serial.print("Right Counter: ");
  Serial.println(tmpLcntr);
  if(micros() > stopTime)
  {
    analogWrite(RWhPWMPin,0);
    analogWrite(LWhPWMPin,0);
    while(true)
    {
    }
  }
  if(tmpLcntr > tmpRcntr) // Change code within bracket
  {
    analogWrite(RWhPWMPin,RSPD1);
    analogWrite(LWhPWMPin,max(LSPD1-int(gain*delCntr+.5),0));
    //Serial.println("adjusting right");
  }
  else if(tmpLcntr<tmpRcntr) // Change code within braket
  {
    analogWrite(LWhPWMPin,LSPD1);
    analogWrite(RWhPWMPin,max(RSPD1-int(gain*delCntr+.5),0));
    //Serial.println("adjusting left");
  }
  else
  {
    analogWrite(RWhPWMPin,RSPD1);
    analogWrite(LWhPWMPin,LSPD1);
    //Serial.println("adjusted");
  }
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
