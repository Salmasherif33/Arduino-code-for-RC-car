#include <Servo.h>
Servo myservo;


void setup() {
  // put your setup code here, to run once:
myservo.attach(9);


}

void loop() {
  // put your main code here, to run repeatedly:
 int lightvalue;
lightvalue = analogRead(A0);



lightvalue = map(lightvalue , 0 , 1023,0 , 180);

myservo.write(lightvalue);
}
