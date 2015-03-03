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
  
 */

#define PIN_RED 6
#define PIN_GREEN 5
#define PIN_BLUE 3

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
  analogWrite(6, 0);  
  analogWrite(5, 0);    
  analogWrite(3, 0);  
  
}

void loop() 
{    
   aguardacomandos();
}

void aguardacomandos()
{    
    char ch;    
    while(Serial.available()) {
        ch = Serial.read();
        if(ch == '|')
        {         
          if(inicioucomando == 1)
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
  if(comando[0] == 'D')
  {    
      int port = (comando[1]- '0'); 
      int value = (comando[2]- '0'); 
      
      if(port == 1)
      {
        digitalWrite(A0, value);    
      }
      else if(port == 2)
      {
        digitalWrite(A1, value);    
      }
      else if(port == 3)
      {
        digitalWrite(A2, value);    
      }
      else if(port == 4)
      {
        digitalWrite(A3, value);    
      }
  }
  else if(comando[0] == 'A')
  {    
    
      int port = (comando[1]- '0'); 
      int value = (comando[2]- '0'); 
      value = value * 28;      
      
      analogWrite(port, value);       
  }
  else
  {
      Serial.println("Error");    
  }
  
  comando = "";
  
}



  
