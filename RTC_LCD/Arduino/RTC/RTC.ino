/*
Sergio Mokshin
Automação Livre
Fev/2015
*/

//Referencia de apoio http://www.glacialwanderer.com/hobbyrobotics

#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68
#include <LiquidCrystal.h>


//Inicializando LCD
LiquidCrystal lcd(12, 11, 8, 9, 10, 7);

//Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

//Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}

// 1) Sets the date and time on the ds1307
// 2) Starts the clock
// 3) Sets hour mode to 24 hour clock
// Assumes you're passing in valid numbers
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

// Gets the date and time from the ds1307
void getDateDs1307(byte *second,
          byte *minute,
          byte *hour,
          byte *dayOfWeek,
          byte *dayOfMonth,
          byte *month,
          byte *year)
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  // A few of these need masks because certain bits are control bits
  *second     = bcdToDec(Wire.read() & 0x7f);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());
}


void setup()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  Wire.begin();
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
    
  // Change these values to what you want to set your clock to.
  // You probably only want to set your clock once and then remove
  // the setDateDs1307 call.
  second = 00;
  minute = 8;
  hour = 22;
  dayOfWeek = 1;
  dayOfMonth = 1;
  month = 2;
  year = 15;
 // setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}

void loop()
{
  MostraData();
  AtualizaSaidas();
  delay(1000);
}


void MostraData(){
    
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    
  lcd.setCursor(0, 1);   
  if (hour < 10){
  lcd.print("0");       
  }
  lcd.print(hour,DEC);   
  lcd.setCursor(2, 1); 
  lcd.print(":");
  lcd.setCursor(3, 1); 
  if (minute < 10){
  lcd.print("0");       
  }
  lcd.print(minute,DEC); 
  lcd.setCursor(5, 1); 
  lcd.print(":");             
  lcd.setCursor(6, 1); 
  if (second < 10){
  lcd.print("0");       
  }
  lcd.print(second,DEC);

  lcd.setCursor(8, 1); 
  lcd.print("  ");
  lcd.setCursor(10, 1);
  if (dayOfMonth < 10){
  lcd.print("0");         
  }
  lcd.print(dayOfMonth,DEC);
  lcd.setCursor(12, 1);
  lcd.print("/"); 
  lcd.setCursor(13, 1);
  if (month < 10){
  lcd.print("0");       
  }
  lcd.print(month,DEC);
  lcd.setCursor(15, 1);


  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(minute, DEC);
  Serial.print(":");
  Serial.print(second, DEC);
  Serial.print("  ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.println(year, DEC);
  Serial.print("Day of week ");
  Serial.println(dayOfWeek, DEC);
}


void AtualizaSaidas(){
    
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);  
 
  //Saída S1: Ligada entre 00:00 e 11:59 todos os dias
  if (hour <= 11)  
  {
    Serial.println("S1 Off");
    digitalWrite(A0, HIGH);    
  }
  else
  {
    Serial.println("S1 On");    
    digitalWrite(A0, LOW);            
  }
    
  //Saída S2: Ligada entre 12:00 e 23:59 todos os dias
  if (hour >=12 )  
  {
    Serial.println("S2 On");
    digitalWrite(A1, HIGH);    
  }
  else
  {
    Serial.println("S2 Off");    
    digitalWrite(A1, LOW);            
  }

  //Saída S3: Ligada entre 08:00 e 17:00 de segunda a sexta
  if (hour >=8 && hour <=17 && dayOfWeek >= 2  && dayOfWeek <= 6)  
  {
    Serial.println("S3 On");
    digitalWrite(A2, HIGH);    
  }
  else
  {
    Serial.println("S3 Off");
    digitalWrite(A2, LOW);            
  }
  
  //Saída S4: Ligada entre 08:00 e 17:00 sábado e domingo
  if (hour >=8 && hour <=17  && (dayOfWeek == 1 || dayOfWeek == 7))  
  {
    Serial.println("S4 On");
    digitalWrite(A3, HIGH);    
  }
  else
  {
    Serial.println("S4 Off");    
    digitalWrite(A4, LOW);            
  }  
          
  //RGB Branco:  Ligado entre 18:00 e 22:00 todos os dias
  //RGB Azul:    Ligado entre 22:00 e 23:59 todos os dias
  if (hour <18 )  
  {
     Serial.println("RG Off");    
     analogWrite(5, 0);
     analogWrite(6, 0);
     analogWrite(3, 0);     
  }
  else if (hour >=18 && hour < 22 )  
  {
     Serial.println("RGB Branco");        
     analogWrite(5, 255);
     analogWrite(6, 255);
     analogWrite(3, 255);     
  }
  else if (hour >=22)  
  {
     Serial.println("RGB Azul");            
     analogWrite(5, 255);
     analogWrite(6, 0);
     analogWrite(3, 0);     
  }

}

