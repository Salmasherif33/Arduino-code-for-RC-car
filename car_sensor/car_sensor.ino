//#include <SoftwareSerial.h>
#define in1 7   //motor1
#define in2 8   //motor1
#define ena 5   //motor1

#define in3 2   //motor2
#define in4 4   //motor2
#define enb 6   //motor2
int serialA; 
int Speed=150;
//ultrasonic & servo
const int trigpin = 9;
const int echopin =10;

//defines variables
#include<Servo.h>
Servo myservo;
int angle = 90;
 long duration;
int distance;


//SoftwareSerial bluetooth(10,11); 
void setup() 
{ 
  Serial.begin(9600);
  //bluetooth.begin(9600);
   pinMode(in1 , OUTPUT );
   pinMode(in2 , OUTPUT );
   pinMode(in3 , OUTPUT );
   pinMode(in4 , OUTPUT );
   pinMode(ena , OUTPUT );
   pinMode(enb , OUTPUT );

   pinMode(trigpin,OUTPUT);//sets the trigpin as an output 
  pinMode(echopin,INPUT);//sets the echo as an input 
  myservo.attach(11);
  Serial.begin(9600);//start the serial communication
}

void loop()
{
  if (Serial.available() > 0 )
  {
    serialA = Serial.read();
   
    }
 
 if(serialA<60&&serialA>48){ 
  Speed=(serialA-48)*25;
 
  } 
 else {
 switch(serialA){

  case 'V':// if the driver click the horn , use ultrasonic
  while(1)
  {
  
while(1){
  //clears the trigpin
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
//sets the trigpin on HIGH state for 10 microseconds
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
//read the echopin,returns the sound wave travel time in microseconds 
duration = pulseIn(echopin,HIGH);
//calculating the distance
distance= duration*0.034/2;
//prints the distance on the serial monitor 
Serial.print("distance:");
Serial.println(distance);

if(distance>8) 
{
 
move1(1,1,Speed,Speed); // forward
}

 else
 {
  move1(0,0,0,0);
  myservo.write (angle=180);
  break; //// if the car found wall
 }
}
while(1){
//clears the trigpin
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
//sets the trigpin on HIGH state for 10 microseconds
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
//read the echopin,returns the sound wave travel time in microseconds 
duration = pulseIn(echopin,HIGH);
//calculating the distance
distance= duration*0.034/2;
//prints the distance on the serial monitor 
Serial.print("distance:");
Serial.println(distance);
  
if (distance>12) //right
 {
  
  move1(0,1,0,140); 
  move1(1,1,Speed,Speed); 

 }
 else {
  move1(0,0,0,0);
  myservo.write(angle=0);
  break;//blocked from the right
 }
}
while(1) //left
{
  //clears the trigpin
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
//sets the trigpin on HIGH state for 10 microseconds
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
//read the echopin,returns the sound wave travel time in microseconds 
duration = pulseIn(echopin,HIGH);
//calculating the distance
distance= duration*0.034/2;
//prints the distance on the serial monitor 
Serial.print("distance:");
Serial.println(distance);

  if(distance < 12)
  {
    move1(1,0,140,0);
    move1(1,1,Speed,Speed);
  }
else
{
  move1(0,0,0,0);
  break; //blocked from the left
}
 }
 break; //blocked from all the directions
  }
  //forward
 case 'F':
 
 move1(1,1,Speed,Speed);
  
  break; 

   //fleft
 case 'G':
 move1(1,1,Speed,Speed);
  
   break ;

   //fright
  case 'I':
  move1(1,1,Speed,Speed);
  
   break ;

    //left
 case 'L': 
 move1(1,0,40,0);
  
   break ;

  //right
  case 'R':
  move1(0,1,0,140);
 
   break ;

  //reverse()
  case 'B':
  move1(0,0,Speed,Speed);
  
  break; 

  //rleft()
  case 'H':
  move1(1,0,Speed,0.5*Speed);
 
  break; 

  //rright()
 
  case 'J':
  move1(0,1,0.5*Speed,Speed);
  
  
  break; 

  //off  
  case 'S' :
  move1(0,0,0,0);
  
 break;
 
 }}
}
void move1 (bool m1 , bool m2, int sp1,int sp2)
{
  digitalWrite(in1 , m1);
  digitalWrite(in2 , !m1);
  digitalWrite(in4 , m2);
  digitalWrite(in3 , !m2);
  analogWrite (ena , sp1);
  analogWrite (enb , sp2);
  
}
