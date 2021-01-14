#include <Servo.h>
//#include <SoftwareSerial.h>
#define in1 7   //motor1
#define in2 8   //motor1
#define ena 5   //motor1

#define in3 2   //motor2
#define in4 4   //motor2
#define enb 9   //motor2

void move1 (bool m1 , bool m2, int sp1, int sp2);


Servo baseservo;
Servo shoulderservo;
Servo gripperservo;
Servo elbowservo;
char serialA;

void setup() {
  // put your setup code here, to run once:
  
  //the pins of servos on the arduino
Serial.begin (9600);
pinMode(in1 , OUTPUT );
   pinMode(in2 , OUTPUT );
   pinMode(in3 , OUTPUT );
   pinMode(in4 , OUTPUT );
   pinMode(ena , OUTPUT );
   pinMode(enb , OUTPUT );

  
   
baseservo.attach(9);
shoulderservo.attach(10);
elbowservo.attach(11);
gripperservo.attach(3);

//initial position of the 4 servos
baseservo.write(0);
shoulderservo.write(150);
elbowservo.write(110);
gripperservo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0 )
  {
    serialA = Serial.read();
   
    }
 
switch (serialA){

  case 'W'://move the base
  if (serialA == '0'){
    
  for(int angle1=0; angle1 <= 180; angle1+=20) // 0 is the initial angle & 180(inital pos + 180) is the max angle of this servo
  {
    baseservo.write(angle1);
    delay(500);
    if (serialA == 'w') 
      break;
   
  }
  }
  else if (serialA == 'q'){
     for(int angle1=180; angle1 >= 0; angle1-=20) // 0 is the initial angle & 180(inital pos + 180) is the max angle of this servo
  {
    baseservo.write(angle1);
    delay(500);
    if (serialA == 'w') 
      break;
  }
  }
  

  break;
  
  case'w': //stop the base
 int currentpos1 = baseservo.read();
  baseservo.write(currentpos1);
  break;

  

  case 'U':
  if (serialA == '0'){// move the shoulder forward
  for(int angle2=150; angle2 <= 240; angle2+=20) // 150 is the min angle & 240(initial pos + 90) is the max angle of this servo
  {
    shoulderservo.write(angle2);
    delay(500);
    if (serialA == 'u')
    {
      
      break;
    }
  }
  }
  else if (serialA == 'q'){
    for(int angle2=currentpos1; angle2 >= 0; angle2-=20) // 0 is the initial angle & 180(inital pos + 180) is the max angle of this servo
  {
    baseservo.write(angle2);
    delay(500);
    if (serialA == 'w') 
      break;
  }
  }
  break;
  
  case 'u': // stop the shoulder
  int currentpos2 = shoulderservo.read(); 
  shoulderservo.write(currentpos2);
  break;
  

  case 'V':
  if (serialA == '0'){ // move the elbow
  
  for(int angle3=110; angle3 <= 200; angle3+=20) // 110 is the min angle & 200(initial pos + 90) is the max angle of this servo
  {
    elbowservo.write(angle3);
    delay(500);
    if (serialA == 'v')
    {
       
      break;
    }
  }
  }
  else if (serialA=='q'){
    for(int angle3=currentpos2; angle3 >= 180; angle3-=20) // 0 is the initial angle & 180(inital pos + 180) is the max angle of this servo
  {
    baseservo.write(angle3);
    delay(500);
    if (serialA == 'w') 
      break;
  }
  }
  break;

  
  case 'v': // stop the elbow
  int currentpos3 = elbowservo.read();
  elbowservo.write(currentpos3);
  break;
  


case 'X': // move the gripper
 if (serialA == '0'){
   
  for(int angle4=0; angle4 <= 180; angle4+=20) // 0 is the min angle & 180(initial pos + 180) is the max angle of this servo
  {
    gripperservo.write(angle4);
    delay(500);
    if (serialA == 'x')
    {
     
      break;
    }
  }
 }
  else if(serialA == 'q'){
     for(int angle4=currentpos3; angle4 >= 0; angle4-=20) // 0 is the initial angle & 180(inital pos + 180) is the max angle of this servo
  {
    baseservo.write(angle4);
    delay(500);
    if (serialA == 'w') 
      break;
  }
  }
  break;
  
  case 'x': // stop the grippper
   int currentpos4 = gripperservo.read(); 
  gripperservo.write(currentpos4);
  break;

//forward
      case 'F':

        move1(1, 1, 150, 150);

        break;

      //fleft
      case 'G':
        move1(1, 1, 175, 100);

        break ;

      //fright
      case 'I':
        move1(1, 1, 100, 175);

        break ;

      //left
      case 'L':
        move1(1, 0, 100, 0);

        break ;

      //right
      case 'R':
        move1(0, 1, 0, 100);

        break ;

      //reverse()
      case 'B':
        move1(0, 0, 150, 150);

        break;

      //rleft()
      case 'H':
        move1(0, 0, 175, 100);

        break;

      //rright()

      case 'J':
        move1(0, 0, 100, 175);


        break;

      //off
      case 'S' :
        move1(0, 0, 0, 0);

        break;

 
}
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
