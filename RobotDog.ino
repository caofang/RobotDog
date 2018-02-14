//#include <Ping.h>
#include <Servo.h> 

//Ping ping = Ping(1, 0, 0);
Servo head; Servo myservo1;  Servo myservo2;  Servo myservo3;  Servo myservo4;  Servo myservo5;  Servo myservo6;  Servo myservo7;  Servo myservo8;


int x = 0;
int sensor = 1;  // 1:forward, 2:sit, 3:stand, 4:left, 5:right, 6:reverse
int al = 0;
int ar = 0;
int b = 30;
int a2=0;
int a6=0;
int speeed=5;
int analogPin = 5;

void setup() 
{ 
  head. attach(2); myservo1.attach(5);  myservo2.attach(6);  myservo3.attach(7);  myservo4.attach(8);  myservo5.attach(9);  myservo6.attach(10);  myservo7.attach(11);  myservo8.attach(12);
  Serial.begin(9600);
} 
 
void loop() 
{  
  //ping.fire(); 
  //int val = analogRead(5);  
  //Serial.print("  ping:  ");
  //Serial.print(ping.centimeters());
  //Serial.print("  A5:  ");
 // Serial.print(val);
  //Serial.println();
  
 
  
  //if (val > 340 && val < 680){sensor = 6;}
  //if (val > 1000){sensor = 3;}
  //if (val < 50 ){sensor = 2;}
  //if (val < 340  && val > 50){sensor = 4;}
 // if (val > 680  && val < 1000){sensor = 5;}
  
 // Serial.print("  sensor:  ");
 // Serial.print(sensor);

  switch(sensor)
  {
      case 1: //reverse
      ar=-1;  al=-1;  a2=0;  a6=0;
      break;
      
      case 2:  //sit
      ar=0;  al=0;  b=0;  a2=-70;  a6=+70;  speeed = 3;
      break;
      
      case 3:  //stand
      ar=0;  al=0;  b=0;  a2=0;  a6=0;  speeed = 3;
      break;
      
      case 4:  //left
      ar=1;  al=-1;  a2=0;  a6=0;
      break;
      
      case 5:  //right
      ar=-1;  al=1;   a2=0;  a6=0;
      break;
      
      default:  //forward
      ar=1;  al=1;  a2=0;  a6=0;
      break;
    }
     
     for (x=-30; x<=30; x++)
  {
  head.write(97+x*ar+a2);  
    myservo1.write(84-x*ar);    //
    myservo2.write(97+x*ar+a2);    //forward: 90 + x, reverse: 90 - x
    myservo3.write(87-x*ar);    //120~60, forward: 90 - x, reverse: 90 + x
    myservo4.write(90+b+x*ar);
  
    myservo5.write(87-b-x*al);       //90~30
    myservo6.write(92+x*al+a6);  //60~120 
    myservo7.write(87-x*al);  //120~60
    myservo8.write(85+x*al);        //60~120
    delay(speeed);
  }
  
 
   
  for (x=30; x>=-30; x--)
  {
      head.write(97+x*ar+a2);  

      myservo1.write(84+b-x*ar);
      myservo2.write(97+x*ar+a2);    //forward: 90 + x, reverse: 90 - x
      myservo3.write(87-x*ar);    //60~120, forward: 90 - x, reverse: 90 + x
      myservo4.write(90+x*ar);
    
      myservo5.write(87-x*al);        //60~120
      myservo6.write(92+x*al+a6);   //60~120
      myservo7.write(87-x*al);   //60~120
      myservo8.write(85-b+x*al);        //90~30
      delay(speeed);
  }
}
