/*
#----------------------------#
|        CHAVEIRO USB        |
|     DIGITADOR DE SENHA     |
|        Ítalo Coelho        |
#----------------------------#
*/
 
//Configurações---------------------------------------------

#include "arduino_secrets.h"
#define Senha1 PASS1
#define Senha2 PASS2
 
#define LongPressDelay 1000 //(in milliseconds)
#define ButtonPin1  0
#define ButtonPin2  2
//----------------------------------------------------------
 
#include <DigiKeyboard.h>
 
void setup() 
{
  //Configurando Pinos dos Botões
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(0 ,INPUT_PULLUP);
  
  //Configurando led indicador
  pinMode(1, OUTPUT); //LED on Model A  or Pro

  //Pisca duas vezes
  digitalWrite(1, HIGH);
  delay(300);          
  digitalWrite(1, LOW); 
  delay(300);  
  digitalWrite(1, HIGH);
  delay(300); 
  digitalWrite(1, LOW); 
}
 
void loop() 
{
  DigiKeyboard.sendKeyStroke(0);
 
  if(!digitalRead(0))                     //Botão foi apertado
  {
    DigiKeyboard.delay(LongPressDelay);
    if(!digitalRead(0))                   //Clique Longo
    {
      digitalWrite(1, HIGH);
      delay(100);          
      digitalWrite(1, LOW);
      DigiKeyboard.print(Senha2);
      DigiKeyboard.delay(500);
    }
    else                                  //Clique Curto
    {
      digitalWrite(1, HIGH);
      delay(100);          
      digitalWrite(1, LOW);
      DigiKeyboard.print(Senha1);
      DigiKeyboard.delay(500);
    }
  }
 
  DigiKeyboard.delay(10);         
}
