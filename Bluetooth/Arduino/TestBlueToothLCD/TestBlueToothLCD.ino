/*
Sergio Mokshin
Automação Live - Abril/2015

init()                              Init the LCD and library functions, Clears the display, turns off the cursors
commandWrite(command)      Write a command not supported yet in the library to the display
position(Row, Column)      Move the cursor to position valid range is Row[0-3], Column[0,19]
print(char)                        Send the single character char to the display at the cursor position.
println(string)                  Send the String to the display at the cursor position.
clear()                        Clear the display and place the cursor at 0,0
home()                        Home the cursor to 0,0 but do not clear the display
on()                              Turn the LCD display on
off()                              Turn the LCD display off
cursor_on()                  Turn the blinking line cursor on
cursor_off()                  Turn the blinking line cursor off
blink_on()                        Turn the blinking block cursor on
blink_off()                        Turn the blinking block cursor on
left()                              Move the cursor to the left
right()                        Move the cursor to the right
keypad()                        Read a value from the keypad. Returns 0 if no key press is in the buffer

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
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <OneWire.h> // Importar biblioteca!!!!!!!
#include "Wire.h"
#include <LiquidCrystal_I2C.h>	// For the LCD

LiquidCrystal_I2C lcd(0x27,16,2);// set the LCD address to 0x27 for a 16 chars and 2 line display
#define DS1307_I2C_ADDRESS 0x68

OneWire ds(2);  // pin 2 (with 4.7K resistor)


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
int countLcd = 0;

int inicioucomando;
String comando = "";
float celsius;

byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;


void setup()
{

  Wire.begin();
  int countLcd = 0;   
   
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
  
  lcd.init();
//  lcd.begin(20, 4);
  lcd.clear();

// Change these values to what you want to set your clock to.
  // You probably only want to set your clock once and then remove
  // the setDateDs1307 call.
  second = 00;
  minute = 40;
  hour = 19;
  dayOfWeek = 3;
  dayOfMonth = 19;
  month = 5;
  year = 15;
  
  //Comentar novamente apos ajuste da data
 // setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);


}

void loop()
{
   ///SEMPRE DESLIGAR BLUETOOTH OU TX / RX DURANTE UPLOAD
   getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
   GetTemp();
   aguardacomandos();
   RetornaComandos();
   PrintLcd();
}

void PrintLcd() {

  lcd.backlight();

  lcd.setCursor(0, 0);
  if (dayOfMonth < 10)
    lcd.print("0");
  lcd.print(dayOfMonth);
  lcd.print("/");
  if (month < 10)
    lcd.print("0");
  lcd.print(month);
//  lcd.print("/");
//  lcd.print(year);
  lcd.print(" ");
  if (hour < 10)
    lcd.print("0");
  lcd.print(hour);
  lcd.print(":");
  if (minute < 10)
    lcd.print("0");
  lcd.print(minute);
  lcd.print(":");
  if (second < 10)
    lcd.print("0");
  lcd.print(second);

  countLcd++;
  
  if (countLcd <= 5)
  {

    lcd.setCursor(0, 1);
    lcd.print("Temp:");
    lcd.print(celsius);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Saidas:");
    if (ValueSaveSaida1 == 1 )
      lcd.print("1");
    else
      lcd.print(" ");
    if (ValueSaveSaida2 == 1 )
      lcd.print("2");
    else
      lcd.print(" ");
    if (ValueSaveSaida3 == 1 )
      lcd.print("3");
    else
      lcd.print(" ");
    if (ValueSaveSaida4 == 1 )
      lcd.print("4");
    else
      lcd.print(" ");

    if (ValueSaveRed > 10 )
      lcd.print("R");
    else
      lcd.print(" ");
    if (ValueSaveGreen > 10 )
      lcd.print("G");
    else
      lcd.print(" ");

    if (ValueSaveBlue > 10 )
      lcd.print("B     ");
    else
      lcd.print("      ");
  }
 
  if(countLcd >=5)
    countLcd = 0;

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



void getDateDs1307(byte * second,
                   byte * minute,
                   byte * hour,
                   byte * dayOfWeek,
                   byte * dayOfMonth,
                   byte * month,
                   byte * year)
{

  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  *second     = bcdToDec(Wire.read() & 0x7f);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());

}

byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

void setDateDs1307(byte second,        // 0-59
                   byte minute,        // 0-59
                   byte hour,          // 1-23
                   byte dayOfWeek,     // 1-7
                   byte dayOfMonth,    // 1-28/29/30/31
                   byte month,         // 1-12
                   byte year)          // 0-99
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second));    // 0 to bit 7 starts the clock
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));      // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void GetTemp() {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }

  switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      //Serial.println("Device is not a DS18x20 family device.");
      return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44);

  delay(1000);     // maybe 750ms is enough, maybe not  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;
    else if (cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  celsius = (float)raw / 16.0;
}


