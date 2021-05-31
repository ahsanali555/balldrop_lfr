int Motor_A_1 = 8; //right
int Motor_A_2 = 2;
int Motor_B_1 = 5; //left
int Motor_B_2 = 4;
int Enable_A = 3; //right
int Enable_B = 11; //left
int leftforward = 175; //175
int rightforward = 150;
//150 for low charged batteries
#include <Servo.h>
Servo myServo;
Servo myServo2;
volatile int counter = 0;
bool done = false;
int Right_sensor_near = A3;
int Left_sensor_near = A1;
int Center_sensor = A2;
int Right_sensor_far = A4;
int Left_sensor_far = A0;
void setup() {
pinMode(Motor_B_1, OUTPUT);
pinMode(Motor_B_2, OUTPUT);
pinMode(Motor_A_1, OUTPUT);
pinMode(Motor_A_2, OUTPUT);
pinMode(Enable_A, OUTPUT);
pinMode(Enable_B, OUTPUT);
pinMode(Right_sensor_near, INPUT);
pinMode(Left_sensor_near, INPUT);
pinMode(Center_sensor, INPUT);
pinMode(Right_sensor_far, INPUT);
pinMode(Left_sensor_far, INPUT);
analogWrite(Enable_A, 150);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, 150);
Serial.begin(9600);
digitalWrite(Motor_A_1, HIGH);
digitalWrite(Motor_A_2, LOW);
digitalWrite(Motor_B_1, HIGH);
digitalWrite(Motor_B_2, LOW);
analogWrite(Enable_A, leftforward);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, rightforward);
//delay(3000);
myServo.attach(6);
//myServo2.attach(9);
myServo.write(85);
/*while(1){
//myServo.write(85); // myServo2.write(30);
delay(1000);
myServo.write(30);
delay(1000);
myServo.write(85);
}*/
}
void loop() {
//ddrop();
//Serial.println(digitalRead(Right_sensor_far));
//Serial.println(digitalRead(Left_sensor_far));
//Move_Forward();
if (((digitalRead(Right_sensor_far) == 1) && (digitalRead(Left_sensor_far) == 1) && (done == false)) || ((digitalRead(Center_sensor) == 1) && (digitalRead(Left_sensor_far) == 1) && (done == false)) || ((digitalRead(Right_sensor_far) == 1) && (Center_sensor == 1) && (done == false)))
{
counter++;
done = true;
}
else if ((digitalRead(Right_sensor_far) == 0) && (digitalRead(Left_sensor_far) == 0) && (done == true))
{
done = false;
}
/*if (counter>13){
Stop();
delay(30000);
}*/
if(counter==17)
{
Stop();
delay(10);
Stop();
delay(1000);
Turn_Right();
delay(250);
while(digitalRead(Center_sensor) == 1)
{
Serial.print("Here");
Serial.println(digitalRead(Center_sensor));
Turn_Right();
}
Stop();
delay(2000);
myServo.write(30);
//delay(2000);
//myServo.write(85);
//Stop();
//delay(50000);
} //Drop functionality here
if(counter==4 | counter==11| counter==14)
{
delay(40);//10
Stop();
delay(1000);
Turn_Left();
delay(250);//250
//Stop();
//delay(1000);
while(digitalRead(Left_sensor_near) == 1)
{
Serial.print("Here");
Serial.println(digitalRead(Center_sensor));
Turn_Left();
}
//delay(250);
counter++;
//Turn_Left();
//delay(20);
}
if ((digitalRead(Left_sensor_near) == 0) && (digitalRead(Center_sensor) == 0) && (digitalRead(Right_sensor_near) == 0))
{
Move_Forward();
}
else if ((digitalRead(Left_sensor_near) == 1) && (digitalRead(Center_sensor) == 1) && (digitalRead(Right_sensor_near) == 1) && (digitalRead(Right_sensor_far) == 1)&& (digitalRead(Left_sensor_far) == 1))
{
Stop();
}
else if ((digitalRead(Right_sensor_near) == 1) && (digitalRead(Left_sensor_near) == 1) && (digitalRead(Center_sensor) == 0))
{
Serial.println("forward");
Move_Forward();
}
else if(digitalRead(Left_sensor_near) == 1)
{
Serial.println("RIGHT");
Move_Forward_Right();
}
else if(digitalRead(Right_sensor_near) == 1)
{
Serial.println("Left");
Move_Forward_Left();
}
}
void Move_Forward()
{
digitalWrite(Motor_A_1, HIGH);
digitalWrite(Motor_A_2, LOW);
digitalWrite(Motor_B_1, HIGH);
digitalWrite(Motor_B_2, LOW);
analogWrite(Enable_A, rightforward);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, leftforward);
}
void Move_Forward_Right()
{
digitalWrite(Motor_A_1, HIGH);
digitalWrite(Motor_A_2, LOW);
digitalWrite(Motor_B_1, HIGH);
digitalWrite(Motor_B_2, LOW);
analogWrite(Enable_A,rightforward-20);//20 Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, leftforward+75); //75
}
void Move_Forward_Left()
{
digitalWrite(Motor_A_1, HIGH);
digitalWrite(Motor_A_2, LOW);
digitalWrite(Motor_B_1, HIGH);
digitalWrite(Motor_B_2, LOW);
analogWrite(Enable_A, rightforward+50);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, leftforward );
}
void Stop()
{
digitalWrite(Motor_A_1, LOW);
digitalWrite(Motor_A_2, LOW);
digitalWrite(Motor_B_1, LOW);
digitalWrite(Motor_B_2, LOW);
analogWrite(Enable_A, rightforward);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, leftforward);
}
void Turn_Right()
{
digitalWrite(Motor_A_1, LOW);
digitalWrite(Motor_A_2, HIGH);
digitalWrite(Motor_B_1, HIGH);
digitalWrite(Motor_B_2, LOW);
analogWrite(Enable_A, rightforward);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, leftforward);
}
void Turn_Left()
{
digitalWrite(Motor_A_1, HIGH);
digitalWrite(Motor_A_2, LOW);
digitalWrite(Motor_B_1, LOW);
digitalWrite(Motor_B_2, HIGH);
analogWrite(Enable_A, rightforward);//Gets the duty cycle to be 150 out of 255 since 255 is the max value.
analogWrite(Enable_B, leftforward);
}
/*
void drop()
{
delay(1000);
myServo.write(85); //myServo2.write(85);
myServo.write(85); //myServo2.write(30);
myServo.write(85); //myServo2.write(85);
myServo.write(30); //myServo2.write(85);
myServo.write(85); //myServo2.write(85);
}*/
