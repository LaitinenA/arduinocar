#include <SPI.h>  
#define joyX A0
#define joyY A1



int id=1;
int xValue = 512;
int yValue = 512;


void setup() {
  Serial.begin(9600);

}

void loop() {
  //luetaan joystick arvot
  int x = analogRead(joyX);
  int y = analogRead(joyY);
  if(x!=xValue || y!=yValue)
  {
    Serial.print("J "); //J joystick
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    xValue = x;
    yValue = y;
    
  }
  


  delay(10);

}
