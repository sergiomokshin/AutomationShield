/*
  Software serial multple serial test
    
 */

#define PIN_RED 6
#define PIN_GREEN 5
#define PIN_BLUE 3

void setup()  
{

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  Serial.begin(9600);  
  analogWrite(6, 0);  
  analogWrite(5, 0);    
  analogWrite(3, 0);  
  
}

void loop() 
{    

  digitalWrite(A0, HIGH);    
  delay(100);
  digitalWrite(A0, LOW);    
  digitalWrite(A1, HIGH);      
  delay(100);
  digitalWrite(A1, LOW);    
  digitalWrite(A2, HIGH);      
  delay(100);
  digitalWrite(A2, LOW);    
  digitalWrite(A3, HIGH);      
  delay(100);
  digitalWrite(A3, LOW);    
  analogWrite(PIN_RED, 255); 
  delay(100);
  digitalWrite(PIN_RED, 0);    
  analogWrite(PIN_GREEN, 255); 
  delay(100);
  digitalWrite(PIN_GREEN, 0);    
  analogWrite(PIN_BLUE, 255); 
  delay(100);
  analogWrite(PIN_BLUE, 255);    
  analogWrite(PIN_RED, 255);    
  analogWrite(PIN_GREEN, 255);      
  delay(100);
  analogWrite(PIN_BLUE, 0);    
  analogWrite(PIN_RED, 0);    
  analogWrite(PIN_GREEN, 0);    


 int valA4 = analogRead(A4); 
 Serial.print("A4=");            
 Serial.println(valA4);            
 
  int valA5 = analogRead(A5); 
 Serial.print("A5=");            
 Serial.println(valA5);            
 
  int valA6 = analogRead(A6); 
 Serial.print("A6=");            
 Serial.println(valA6);            
 
 int valA7 = analogRead(A7); 
 Serial.print("A7=");            
 Serial.println(valA7);            
 
 
 int valD2 = digitalRead(2); 
 Serial.print("D2=");            
 Serial.println(valD2);            
 
 int valD3 = digitalRead(3); 
 Serial.print("D3=");            
 Serial.println(valD3);            
 
 int valD4 = digitalRead(4); 
 Serial.print("D4=");            
 Serial.println(valD4);            
 
 int valD5 = digitalRead(5); 
 Serial.print("D5=");            
 Serial.println(valD5);            
 
 int valD6 = digitalRead(6); 
 Serial.print("D6=");            
 Serial.println(valD6);            
 
 int valD7 = digitalRead(7); 
 Serial.print("D7=");            
 Serial.println(valD7);            
 
 int valD8 = digitalRead(8); 
 Serial.print("D8=");            
 Serial.println(valD8);            
 
 int valD9 = digitalRead(9); 
 Serial.print("D9=");            
 Serial.println(valD9);            
 
 int valD10 = digitalRead(10); 
 Serial.print("D10=");            
 Serial.println(valD10);            
 
 int valD11 = digitalRead(11); 
 Serial.print("D11=");            
 Serial.println(valD11);            
 
 int valD12 = digitalRead(12); 
 Serial.print("D12=");            
 Serial.println(valD12);            
 
 int valD13 = digitalRead(13); 
 Serial.print("D13=");            
 Serial.println(valD13);            
    
  
  
}



  
