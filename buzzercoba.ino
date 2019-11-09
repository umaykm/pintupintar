/* + : 5volt
 *  - : i/o
 */
 //----------
#include <ESP32Servo.h>
Servo myservo;
int pos = 0;
int servopin = 15;
//-----------
int freq = 2000;
int channel = 0;
int resolution = 10;
int buzzer = 19;

int merah = 18;
int hijau = 21;


void alarmbuka(){
  digitalWrite(hijau, HIGH); 
  ledcAttachPin(buzzer, channel);
  ledcWrite(channel, 1024);
  ledcWriteTone(channel, 4000);

  for (pos = 0; pos <= 90; pos=+1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(15);
  }
  delay(2000);
  ledcWriteTone(channel, 0);
  digitalWrite(hijau, LOW); 

  for (pos = 90; pos >= 0; pos=-1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(15);
  }
}


void alarmtutup(){
  for (int i=0; i<=10; i++){
  digitalWrite(merah, HIGH); 
  ledcAttachPin(19, channel);
  ledcWrite(channel, 1024);
  ledcWriteTone(channel, 4000);
  delay(50);
  ledcWriteTone(channel, 0);
  digitalWrite(merah, LOW);
  delay(50);
  } 
}


void setup() {
 
  Serial.begin(115200);
  myservo.attach(15);
  
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(19, channel);

  pinMode(merah, OUTPUT);
  pinMode(hijau, OUTPUT);
  alarmbuka();
  alarmtutup();
}


void loop() {
 /*
  ledcWriteTone(channel, 2000);
 
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle=dutyCycle+10){
 
    Serial.println(dutyCycle);
 
    ledcWrite(channel, dutyCycle);
    delay(1000);
  }
 */

 /*
  ledcAttachPin(19, channel);
  ledcWrite(channel, 1024);
  ledcWriteTone(channel, 4000);
  delay(100);
  ledcWriteTone(channel, 0);
  delay(100);
  */
  
 /*
  for (int freq = 255; freq < 10000; freq = freq + 250){
 
     Serial.println(freq);
 
     ledcWriteTone(channel, freq);
     delay(1000);
  }
 */
}
