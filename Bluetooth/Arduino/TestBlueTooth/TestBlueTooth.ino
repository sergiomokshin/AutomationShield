/*
  Software serial multple serial test

    https://drive.google.com/file/d/0B0t-Nu1Eo1b8OFdOWkg5QkMwMVE/view?usp=sharing

  VCC 3V
  GND  GND
  TX  RX
  RX  TX



  Protocolo
  |D21|
  |D20|

  |A64|

  Versão 1.1 -> Incluido persitencia de comandos na EEPROM e WACHTDOG

  */


#include <EEPROM.h>
#include <avr/wdt.h>

#define PIN_RED 6
#define PIN_GREEN 5
#define PIN_BLUE 3


int MemSaveSaida1 = 1;
int MemSaveSaida2 = 2;
int MemSaveSaida3 = 3;
int MemSaveSaida4 = 4;
int MemSaveRed    = 5;
int MemSaveBlue   = 6;
int MemSaveGreen  = 7;

int ValueSaveSaida1 = 0;
int ValueSaveSaida2 = 0;
int ValueSaveSaida3 = 0;
int ValueSaveSaida4 = 0;
int ValueSaveRed    = 0;
int ValueSaveBlue   = 0;
int ValueSaveGreen  = 0;

int inicioucomando;
String comando = "";

void setup()
{

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  inicioucomando = 0;
  comando = "";

  Serial.begin(9600);

  ValueSaveSaida1 = EEPROM.read(MemSaveSaida1);
  ValueSaveSaida2 = EEPROM.read(MemSaveSaida2);
  ValueSaveSaida3 = EEPROM.read(MemSaveSaida3);
  ValueSaveSaida4 = EEPROM.read(MemSaveSaida4);
  ValueSaveRed = EEPROM.read(MemSaveRed);
  ValueSaveBlue = EEPROM.read(MemSaveBlue);
  ValueSaveGreen = EEPROM.read(MemSaveGreen);

  digitalWrite(A0, ValueSaveSaida1);
  digitalWrite(A1, ValueSaveSaida2);
  digitalWrite(A2, ValueSaveSaida3);
  digitalWrite(A3, ValueSaveSaida4);

  analogWrite(5, ValueSaveRed);
  analogWrite(6, ValueSaveGreen);
  analogWrite(3, ValueSaveBlue);

  wdt_enable(WDTO_8S); //Watchdog 8 Segundos
}

void loop()
{
  aguardacomandos();
  wdt_reset(); //Reset WatchDog
  RetornaComandos();

}

void aguardacomandos()
{
  char ch;
  while (Serial.available()) {
    ch = Serial.read();
    if (ch == '|')
    {
      if (inicioucomando == 1)
      {
        inicioucomando = 0;
        disparacomando();
      }
      else
      {
        inicioucomando = 1;
      }
    }
    else
    {
      comando.concat(ch);
    }
  }
}


void disparacomando()
{

  Serial.println(comando);
  if (comando[0] == 'D')
  {
    int port = (comando[1] - '0');
    int value = (comando[2] - '0');

    if (port == 1)
    {
      ValueSaveSaida1 = value;
      EEPROM.write(MemSaveSaida1, ValueSaveSaida1);
      digitalWrite(A0, ValueSaveSaida1);
    }
    else if (port == 2)
    {
      ValueSaveSaida2 = value;
      EEPROM.write(MemSaveSaida2, ValueSaveSaida2);
      digitalWrite(A1, ValueSaveSaida2);
    }
    else if (port == 3)
    {
      ValueSaveSaida3 = value;
      EEPROM.write(MemSaveSaida3, ValueSaveSaida3);
      digitalWrite(A2, ValueSaveSaida3);
    }
    else if (port == 4)
    {
      ValueSaveSaida4 = value;
      EEPROM.write(MemSaveSaida4, ValueSaveSaida4);
      digitalWrite(A3, ValueSaveSaida4);
    }
  }
  else if (comando[0] == 'A')
  {
    int port = (comando[1] - '0');
    int value = (comando[2] - '0');
    value = value * 28;

    if ( port == 6 )
    {
      ValueSaveRed = value;
      EEPROM.write(MemSaveRed, ValueSaveRed);
      analogWrite(port, value);
    }
    else if ( port == 5 )
    {
      ValueSaveGreen = value;
      EEPROM.write(MemSaveGreen, ValueSaveGreen);
      analogWrite(port, value);
    }
    else if ( port == 3 )
    {
      ValueSaveBlue = value;
      EEPROM.write(MemSaveBlue, ValueSaveBlue);
      analogWrite(port, value);
    }
  }
  else
  {
    Serial.println("Error");
  }
  comando = "";
}

void RetornaComandos()
{
  String retorno = "|COMANDOS#";
  retorno.concat(ValueSaveSaida1);
  retorno.concat("#");
  retorno.concat(ValueSaveSaida2);
  retorno.concat("#");
  retorno.concat(ValueSaveSaida3);
  retorno.concat("#");
  retorno.concat(ValueSaveSaida4);
  retorno.concat("#");
  retorno.concat(ValueSaveRed);
  retorno.concat("#");
  retorno.concat(ValueSaveGreen);
  retorno.concat("#");
  retorno.concat(ValueSaveBlue);
  retorno.concat("#");

  Serial.println(retorno);
}

