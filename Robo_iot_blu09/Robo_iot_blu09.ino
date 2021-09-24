#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
#include <pico/bootrom.h>
#include "arduino_secrets.h"
 
char auth[] = SECRET_BLYNK;
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
 
#define EspSerial Serial1
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
 
Servo servo;
int angulo = 0;

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

   //**Pedro** Inicializa LED Verde
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
 
  //Prepara servo
  servo.attach(SERVO);
  servo.write(110);
  delay(2000);
  servo.write(40);
  delay(2000);
  servo.write(180);
  delay(2000);
  servo.write(110);
   
  EspSerial.setPinout(0,1);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);

  //**Pedro** Apaga Leds 
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);

  //Pisca LED azul
  for (int i=0; i<3; i++){
    digitalWrite(BLUE,HIGH);
    delay(1000);
    digitalWrite(BLUE,LOW);
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
    digitalWrite(RED,HIGH);
    digitalWrite(BLUE,LOW);
    digitalWrite(GREEN,LOW);
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
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH); 
  }
}

 
//AMARELO
BLYNK_WRITE(V6)
{ 
  int button = param.asInt();
  if (button == 1) {
    digitalWrite(RED,HIGH);
    digitalWrite(BLUE,LOW);
    digitalWrite(GREEN,HIGH);
  }
  else {
    noTone(BUZZER);
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
  }
}

//SERVO
BLYNK_WRITE(V5)
{
 servo.write(param.asInt());
}

//SOFT RESET (BOOTSEL)

BLYNK_WRITE(V7)
{
  //melodia do MARIO THEME
  int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
   
  //duraçao de cada nota
  int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};

  //pausa depois das notas
  int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
              
  //for para tocar as 156 notas começando no 0 ate 156 ++ incrementado
  for (int nota = 0; nota < 156; nota++) {
    //led cor aleatoria
    analogWrite(RED,random(0,255));
    analogWrite(GREEN,random(0,255));
    analogWrite(BLUE,random(0,255));
    
    //toca nota
    int duracaodanota = duracaodasnotas[nota];
    tone(BUZZER, melodia[nota],duracaodanota);
    delay(pausadepoisdasnotas[nota]);
  }
  noTone(BUZZER);
  
  //comando botão bootsel
  reset_usb_boot(0, 0);
}
