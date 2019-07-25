#include "Arduino.h"
#include "RTClib.h"
RTC_DS3231 rtc;

// Debugging
#undef DEBUG

//Define starting time here
uint8_t hour = 0;
uint8_t lasthour = 0;

String state = "";

void setup()
{
  Serial.begin(9600);
  pinMode(12,OUTPUT);

  #ifdef DEBUG 
  Serial.println("DEBUG MODE");
  #endif

  if(! rtc.begin())
  {
    Serial.println("DS3231 not found");
  }
  if(rtc.lostPower())
  {
    Serial.println("DS3231 OK!"); 
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2018, 9, 29, 15, 00, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  delay(100);   
}

void loop()
{
  lasthour = hour;

  #ifdef DEBUG
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    Serial.println(); //QUEBRA DE LINHA NA SERIAL
    delay(1000); //INTERVALO DE 1 SEGUNDO
    Serial.println((String)hour+ "h - "+ state);
    delay(10000);
    
    if(hour < 23)
    {
      hour++;
    }
    else
    {
      hour=0;
    }

  #else
    DateTime now = rtc.now();
    hour = (uint8_t)now.hour();
  #endif

  if(hour > 22 || hour < 8)
  {
    digitalWrite(12, LOW);
    state = "Noite"; //Noite 
  }
  else if ( (hour >= 9 && hour <= 12) || (hour >= 16 && hour < 19) )
  {
    digitalWrite(12, HIGH);
    state = "Ligado"; //Ligado
  }
  else
  {
    digitalWrite(12, LOW);
    state = "Desligado"; //Desligado 
  }

  if(lasthour!=hour)
  {
    Serial.println((String)hour+ "h - "+ state);
  }
} 