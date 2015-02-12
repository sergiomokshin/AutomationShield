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
  delay(500);
  digitalWrite(A0, LOW);    
  digitalWrite(A1, HIGH);      
  delay(500);
  digitalWrite(A1, LOW);    
  digitalWrite(A2, HIGH);      
  delay(500);
  digitalWrite(A2, LOW);    
  digitalWrite(A3, HIGH);      
  delay(500);
  digitalWrite(A3, LOW);    
  analogWrite(PIN_RED, 255); 
  delay(500);
  digitalWrite(PIN_RED, 0);    
  analogWrite(PIN_GREEN, 255); 
  delay(500);
  digitalWrite(PIN_GREEN, 0);    
  analogWrite(PIN_BLUE, 255); 
  delay(500);
  analogWrite(PIN_BLUE, 255);    
  analogWrite(PIN_RED, 255);    
  analogWrite(PIN_GREEN, 255);      
  delay(500);
  analogWrite(PIN_BLUE, 0);    
  analogWrite(PIN_RED, 0);    
  analogWrite(PIN_GREEN, 0);      
    
  
  
}



  
