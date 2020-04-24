#include <SPI.h> 
#define Jmin 0  
#define Jmax 1023
#define Jstop 512
#define Jtolerance 50

long xValue = 512;
long yValue = 512;
bool valo = false;
int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  Serial.begin(9600);
  //kaikki releet pois päältä eli moottorit ei pyäri
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  
}


void loop() 
{
  int command;
  
  if ( Serial.available() > 0) 
  {
      command = Serial.read();
      if ( command == 'J') {
        xValue = Serial.parseInt();
        yValue = Serial.parseInt();
        Serial.read(); //rivinvaihto
        //kuvan mukainen ehto moottorin pyörittämiselle
        int raja1 = Jstop - Jtolerance;
        int raja2 = Jstop + Jtolerance;
        
        if(xValue > raja1 && xValue < raja2 ) { 
          //if lauseessa määritetty alue jossa moottorit ei pyöri eli tatti on keskiasennossaan y ja x
          if(yValue>raja1 && yValue < raja2) {
              digitalWrite(relay1, HIGH);
              digitalWrite(relay2, HIGH);
              digitalWrite(relay3, HIGH);
              digitalWrite(relay4, HIGH);
          } else

          if(yValue <= raja2){ // Eteenpäin
            digitalWrite(relay1, HIGH);//vasen pyörä eteen
            digitalWrite(relay2, LOW);//vasen pyörä eteen
            digitalWrite(relay3, HIGH);  //oikee Eteen
            digitalWrite(relay4, LOW);//oikee eteen 
          }      else  
          if(yValue >= raja2){ // Taaksepäin
            digitalWrite(relay1, LOW);//vasen pyörä taakse
            digitalWrite(relay2, HIGH);//vasen pyörä taakse (toisinpäin eteen)
            digitalWrite(relay3, LOW);  //oikee taakse
            digitalWrite(relay4, HIGH);//oikee taakse

          }
          
        }
        if( xValue<=raja1){ // pyörii vasen
            digitalWrite(relay1, LOW);//vasen pyörä taakse
            digitalWrite(relay2, HIGH);//vasen pyörä taakse
            digitalWrite(relay3, HIGH);  //oikee Eteen
            digitalWrite(relay4, LOW);//oikee eteen     
        }
        if( xValue>=raja2){ // pyörii oikee
            digitalWrite(relay1, HIGH);//vasen pyörä eteen
            digitalWrite(relay2, LOW);//vasen pyörä eteen
            digitalWrite(relay3, LOW);  //oikee taakse
            digitalWrite(relay4, HIGH);//oikee taakse   
        }
        // vilkutetaan kortin valoa loopissa olon merkiksi
        if (valo) {
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          valo = false;
        } else {
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
          valo = true;
        } 
      }
  }
}
