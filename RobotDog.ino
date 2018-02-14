// 06/14/2016
// support serial command 
// 1:forward, 2:sit, 3:stand, 4:left, 5:right, 6:reverse
// h: help

#include <Servo.h> 
Servo head, myservo1, myservo2, myservo3, myservo4, myservo5, myservo6, myservo7, myservo8;

int x = 0;
int motion = 1;  // 1:forward, 2:sit, 3:stand, 4:left, 5:right, 6:reverse
int enablePin=4;  // low: motion=3; high: motion=1
int al = 0;
int ar = 0;
int b = 30;
int a2=0;
int a6=0;
int speeed=5;
int analogPin = 5;

long timeout=1000; // us
int pingPin=3;  // 
void setup() 
{ 
    head. attach(2); 
    myservo1.attach(5);  
    myservo2.attach(6);  
    myservo3.attach(7);  
    myservo4.attach(8);  
    myservo5.attach(9); 
    myservo6.attach(10);  
    myservo7.attach(11);  
    myservo8.attach(12);
    Serial.begin(9600);
//    while (!Serial) 
//    {
//        digitalWrite(13,1);
//        delay(10);
//        digitalWrite(13,0);
//        delay(10);
//    }

    pinMode(enablePin,INPUT);
} 
 
void loop() 
{  
    while(digitalRead(enablePin) == 0) 
    {
        Serial.println("Robot Disabled");
        while(Serial.available())
        {
            Serial.write(Serial.read());
        }
        delay(100);
    }
    if(Serial.available())
    {
         int b = Serial.read();
         if(b=='h') Serial.println("1:forward, 2:sit, 3:stand, 4:left, 5:right, 6:reverse, h:help");
         else if(b == 0x0a || b == 0x0d) Serial.println("Ignoring LF and CR");
         else if(b >= '1' && b <= '5') 
         {
            motion = b - 0x30;
            //Serial.println(motion);
         }
         else 
         {
            Serial.println("wrong command, default mode");
            Serial.println("1:forward, 2:sit, 3:stand, 4:left, 5:right, 6:reverse, h:help");
         }
    }
    Serial.println(motion);
    switch(motion)
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
    
    head.write(90);   
    for (x=-30; x<=30; x++)
    {
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

int getPing(int pingPin,long timeout)
{
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    pinMode(pingPin, INPUT);
    long duration = pulseIn(pingPin, HIGH,timeout);
    return duration;
}

long microsecondsToCentimeters(long microseconds) 
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}




