#include <IRremote.hpp>
#define PIN_SEND 3
#define xPin A0
#define yPin A1
#define button 2
int x=511;
int y=511;
int b=1;
void setup()
{
Serial.begin(9600);
IrSender.begin(PIN_SEND);
pinMode(button, INPUT);
digitalWrite(button, HIGH);
}

void loop() {
  x=analogRead(xPin);
  y=analogRead(yPin);
  b=digitalRead(button);
  Serial.print("x");
  Serial.println(x);
  Serial.print("y");
  Serial.println(y);
  Serial.print("b");
  Serial.println(b);
  if(x>=400 && x<=600 && y>=400 && y<=600){ //Stop
    IrSender.sendNEC(0x00FF00FF, 0,1);
    delay(100);

  }else if(x>=400 && x<=600 && y<400 && y>=300) { //SF
    IrSender.sendNEC(0x00FF00FF, 1,1);
    delay(100);

  }else if(x>=400 && x<=600 && y<300 && y>=100) { //F
    IrSender.sendNEC(0x00FF00FF, 2,1);
    delay(100);
    
  }else if(x>=400 && x<=600 && y<100) { //FF
    IrSender.sendNEC(0x00FF00FF, 3,1);
    delay(100);
    
  }else if(x>=400 && x<=600 && y>600 && y<=700) { //SB
    IrSender.sendNEC(0x00FF00FF, 4,1);
    delay(100);
    
  }else if(x>=400 && x<=600 && y>700 && y<=900) { //B
    IrSender.sendNEC(0x00FF00FF, 5,1);
    delay(100);
    
  }else if(x>=400 && x<=600 && y>900) { //FB
    IrSender.sendNEC(0x00FF00FF, 6,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y>=400 && y<=600) { //SL
    IrSender.sendNEC(0x00FF00FF, 7,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y>=400 && y<=600) { //L
    IrSender.sendNEC(0x00FF00FF, 8,1);
    delay(100);
    
  }else if(x<100 && y>=400 && y<=600) { //FL
    IrSender.sendNEC(0x00FF00FF, 9,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y>=400 && y<=600) { //SR
    IrSender.sendNEC(0x00FF00FF, 10,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y>=400 && y<=600) { //R
    IrSender.sendNEC(0x00FF00FF, 11,1);
    delay(100);
    
  }else if(x>900 && y>=400 && y<=600) { //FR
    IrSender.sendNEC(0x00FF00FF, 12,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y<400 && y>=300) { //SF SL
    IrSender.sendNEC(0x00FF00FF, 13,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y<400 && y>=300) { //SF L
    IrSender.sendNEC(0x00FF00FF, 14,1);
    delay(100);
    
  }else if(x<100 && y<400 && y>=300) { //SF FL
    IrSender.sendNEC(0x00FF00FF, 15,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y<400 && y>=300) { //SF SR
    IrSender.sendNEC(0x00FF00FF, 16,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y<400 && y>=300) { //SF R
    IrSender.sendNEC(0x00FF00FF, 17,1);
    delay(100);
    
  }else if(x>900 && y<400 && y>=300) { //SF FR
    IrSender.sendNEC(0x00FF00FF, 18,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y<300 && y>=100) { //F SL
    IrSender.sendNEC(0x00FF00FF, 19,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y<300 && y>=100) { //F L
    IrSender.sendNEC(0x00FF00FF, 20,1);
    delay(100);
    
  }else if(x<100 && y<300 && y>=100) { //F FL
    IrSender.sendNEC(0x00FF00FF, 21,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y<300 && y>=100) { //F SR
    IrSender.sendNEC(0x00FF00FF, 22,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y<300 && y>=100) { //F R
    IrSender.sendNEC(0x00FF00FF, 23,1);
    delay(100);
    
  }else if(x>900 && y<300 && y>=100) { //F FR
    IrSender.sendNEC(0x00FF00FF, 24,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y<100) { //FF SL
    IrSender.sendNEC(0x00FF00FF, 25,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y<100) { //FF L
    IrSender.sendNEC(0x00FF00FF, 26,1);
    delay(100);
    
  }else if(x<100 && y<100) { //FF FL
    IrSender.sendNEC(0x00FF00FF, 27,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y<100) { //FF SR
    IrSender.sendNEC(0x00FF00FF, 28,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y<100) { //FF R
    IrSender.sendNEC(0x00FF00FF, 29,1);
    delay(100);
    
  }else if(x>900 && y<100) { //FF FR
    IrSender.sendNEC(0x00FF00FF, 30,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y>600 && y<=700) { //SB SL
    IrSender.sendNEC(0x00FF00FF, 31,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y>600 && y<=700) { //SB L
    IrSender.sendNEC(0x00FF00FF, 32,1);
    delay(100);
    
  }else if(x<100 && y>600 && y<=700) { //SB FL
    IrSender.sendNEC(0x00FF00FF, 33,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y>600 && y<=700) { //SB SR
    IrSender.sendNEC(0x00FF00FF, 34,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y>600 && y<=700) { //SB R
    IrSender.sendNEC(0x00FF00FF, 35,1);
    delay(100);
    
  }else if(x>900 && y>600 && y<=700) { //SB FR
    IrSender.sendNEC(0x00FF00FF, 36,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y>700 && y<=900) { //B SL
    IrSender.sendNEC(0x00FF00FF, 37,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y>700 && y<=900) { //B L
    IrSender.sendNEC(0x00FF00FF, 38,1);
    delay(100);
    
  }else if(x<100 && y>700 && y<=900) { //B FL
    IrSender.sendNEC(0x00FF00FF, 39,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y>700 && y<=900) { //B SR
    IrSender.sendNEC(0x00FF00FF, 40,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y>700 && y<=900) { //B R
    IrSender.sendNEC(0x00FF00FF, 41,1);
    delay(100);
    
  }else if(x>900 && y>700 && y<=900) { //B FR
    IrSender.sendNEC(0x00FF00FF, 42,1);
    delay(100);
    
  }else if(x<400 && x>=300 && y>900) { //FB SL
    IrSender.sendNEC(0x00FF00FF, 43,1);
    delay(100);
    
  }else if(x<300 && x>=100 && y>900) { //FB L
    IrSender.sendNEC(0x00FF00FF, 44,1);
    delay(100);
    
  }else if(x<100 && y>900) { //FB FL
    IrSender.sendNEC(0x00FF00FF, 45,1);
    delay(100);
    
  }else if(x>600 && x<=700 && y>900) { //FB SR
    IrSender.sendNEC(0x00FF00FF, 46,1);
    delay(100);
    
  }else if(x>700 && x<=900 && y>900) { //FB R
    IrSender.sendNEC(0x00FF00FF, 47,1);
    delay(100);
    
  }else if(x>900 && y>900) { //FB FR
    IrSender.sendNEC(0x00FF00FF, 48,1);
    delay(100);
    
  }

}
