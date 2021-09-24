#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
 
char auth[] = "insira-aqui-o-token-enviado-para-seu-email";
char ssid[] = "insira-aqui-o-nome-da-rede-wifi";
char pass[] = "insira-aqui-a-senha-da-rede-wifi";
 
#define EspSerial Serial1
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
 
Servo servo;
 
#define MOTORA_1     2
#define MOTORA_2     3
#define MOTORB_1     4
#define MOTORB_2     5
#define SERVO        6
#define BUZZER       7
#define RED          8
#define GREEN        9
#define BLUE         10
 
void setup(){
   
  Serial.begin(115200);
  delay(5000);
 
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
   
  digitalWrite(MOTORA_1, LOW);
  digitalWrite(MOTORA_2, LOW);
  digitalWrite(MOTORB_1, LOW);
  digitalWrite(MOTORB_2, LOW);
   
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
 
  //Prepara servo
  servo.attach(SERVO);
  servo.write(90);
  delay(2000);
  servo.write(0);
  delay(2000);
  servo.write(180);
  delay(2000);
  servo.write(90);
   
  EspSerial.setPinout(0,1);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);
 
  //Pisca LED vermelho
  for (int i=0; i<5; i++){
    digitalWrite(RED,LOW);
    delay(1000);
    digitalWrite(RED,HIGH);
    delay(1000);
  }
   
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
}
 
void loop(){
  Blynk.run();
}
 
// FORWARD
BLYNK_WRITE(V0) {
  int button = param.asInt();
  if (button == 1) {
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,HIGH);
  }
  else {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
}
 
//RIGHT
BLYNK_WRITE(V1) {
  int button = param.asInt();
  if (button == 1) {
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,HIGH);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,HIGH);
  }
  else {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
}
 
// BACKWARD
BLYNK_WRITE(V2) {
  int button = param.asInt();
  if (button == 1) {
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,HIGH);
    digitalWrite(MOTORB_1,HIGH);
    digitalWrite(MOTORB_2,LOW);
  }
  else {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
}
 
// LEFT
BLYNK_WRITE(V3) {
  int button = param.asInt();
  if (button == 1) {
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,HIGH);
    digitalWrite(MOTORB_2,LOW);
  }
  else {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
}
 
//BUZZER
BLYNK_WRITE(V4)
{ 
  int button = param.asInt();
  if (button == 1) {
    digitalWrite(BLUE,LOW);
    tone(BUZZER, 330);
    delay(100);
    noTone(BUZZER);
    delay(100);
    tone(BUZZER, 330);
    delay(100);
    noTone(BUZZER);
    delay(100);
    tone(BUZZER, 330);
    delay(500);
    noTone(BUZZER);
    delay(100);
  }
  else {
    noTone(BUZZER);
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,HIGH);
  }
}
 
//SERVO
BLYNK_WRITE(V5)
{
 servo.write(param.asInt());
}
