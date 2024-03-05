//Parker Murphy and Frederick Levins
/* Run Wheels and Servo
 */
 const int RSPD1 = 255;        //Right Wheel PWM
 const int LSPD1 = 255;        //Left Wheel PWM
 const int RSPD2 = 255;        //Right Wheel PWM
 const int LSPD2 = 255;        //Left Wheel PWM

 
 const int LWhFwdPin = 7;
 const int LWhBwdPin = 5;
 const int LWhPWMPin = 10;

 const int RWhFwdPin = 4;
 const int RWhBwdPin = 2;
 const int RWhPWMPin = 9; 

 const int ultraServoPin = 8;
 #include <Servo.h>
 #include <Wire.h> // Library for I2C communication
 #include <LiquidCrystal_I2C.h> // Library for LCD
 Servo ultraServo;  // servo object to control ultrasonic servo
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() 
{
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
  ultraServo.attach(ultraServoPin);
  lcd.init();
  lcd.backlight();  
}


void loop() 
{
  delay(1000);
  digitalWrite(LWhFwdPin,HIGH);    //run left wheel forward
  analogWrite(LWhPWMPin,LSPD1);
  digitalWrite(RWhFwdPin,HIGH);   //run right wheel forward
  analogWrite(RWhPWMPin,RSPD1);
  delay(1000);
  analogWrite(LWhPWMPin,0);       // stop left wheel
  analogWrite(RWhPWMPin,0);       // stop right wheel
  delay(1000);
  digitalWrite(LWhFwdPin,LOW);    //run left wheel backward
  digitalWrite(LWhBwdPin,HIGH);
  analogWrite(LWhPWMPin,LSPD2);
  digitalWrite(RWhFwdPin,LOW);    //run right wheel backward
  digitalWrite(RWhBwdPin,HIGH);
  analogWrite(RWhPWMPin,RSPD2);
  delay(1000);
  analogWrite(RWhPWMPin,0);       //stop right wheel
  analogWrite(LWhPWMPin,0);       //stop left wheel
  delay(1000);
  ultraServo.write(90);          //turn to 0 degrees
 while(true)
  { //run servo
    /*lcd.clear();
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("Servo Position"); // Print the string "Hello World!"
    lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("0 Degree");
//    ultraServo.write(0);          //turn to 0 degrees
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("Servo Position"); // Print the string "Hello World!"
    lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("180 Degree");    
//    ultraServo.write(180);        //turn to 180 degrees
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("Servo Position"); // Print the string "Hello World!"
    lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("90 Degree");
 //   ultraServo.write(90);         //turn to straight ahead
    delay(3000);*/
  }  
}
