#include <Servo.h>
 Servo myServo;
 const int piezo = A0;
 const int switchPin = 2;
 const int yellowLed = 3;
 const int orangeLed=6;
 const int greenLed = 4;
 const int redLed = 5;
 const int slideSwitch=10;             
 int knockVal;
 int reqKnock=3;
 int tmp;
 int tmp2;
 int switchVal;
 int slideSwitchVal;
 const int quietKnock = 10;
 const int loudKnock = 100;
 boolean locked = false;
 int numberOfKnocks = 0;
void setup(){
 myServo.attach(9);
 pinMode(slideSwitch,INPUT);
 pinMode(yellowLed, OUTPUT);
 pinMode(orangeLed, OUTPUT);
 pinMode(redLed, OUTPUT);
 pinMode(greenLed, OUTPUT);
 pinMode(switchPin, INPUT);
 Serial.begin(9600);
 digitalWrite(greenLed, HIGH);
 digitalWrite(orangeLed,LOW);
 myServo.write(0);
 Serial.println("the box is unlocked!");
 }
void loop(){
 slideSwitchVal=digitalRead(slideSwitch);
 if(slideSwitchVal==LOW){
  Serial.println("In working stage "); 
 if(locked == false){
 switchVal = digitalRead(switchPin);
 if(switchVal == HIGH){
 locked = true;
 digitalWrite(greenLed,LOW);
 digitalWrite(redLed,HIGH);
 myServo.write(90);
 Serial.println("the box is locked!");
 delay (1000);
 }
 }
 if(locked == true){
 knockVal = analogRead(piezo);
 if(numberOfKnocks < 3 && knockVal > 0){
 if(checkForKnock(knockVal) == true){
 numberOfKnocks++;
 }
 Serial.print(3 - numberOfKnocks);
 Serial.println(" more knocks to go");
 }
 if(numberOfKnocks >= reqKnock){
 locked = false;
 myServo.write(0);
 delay(20);
 digitalWrite(greenLed,HIGH);
 digitalWrite(redLed,LOW);
 Serial.println("the box is unlocked!");
 }
 }
 }
 else {
  Serial.println("In password change state ");
  digitalWrite(greenLed,LOW);
  digitalWrite(orangeLed,HIGH);
  tmp2=digitalRead(slideSwitch);
  while(tmp2!=LOW){
  knockVal = analogRead(piezo);
  if(knockVal>0){
  reqKnock=0;
  Serial.println("Resetting knock value now input new kock value ");
  while(true){
  if(checkForKnock(knockVal)==true){
   reqKnock++; 
   Serial.print("Required knock value = ");
   Serial.println(reqKnock);
  }
  delay(100);
  knockVal = analogRead(piezo);
  tmp=digitalRead(slideSwitch);
  if(tmp==LOW){
    digitalWrite(orangeLed,LOW);
    Serial.println("Done Resetting");
    break;
  }
 }
 }
 tmp2=digitalRead(slideSwitch);
 }
 }
 }
 boolean checkForKnock(int value){
 if(value > quietKnock && value < loudKnock){
 digitalWrite(yellowLed, HIGH);
 delay(50);
 digitalWrite(yellowLed, LOW);
 Serial.print("Valid knock of value ");
 Serial.println(value);
return true;
 }
 else {
 Serial.print("Bad knock value ");
 Serial.println(value);
return false;
 }
 }
