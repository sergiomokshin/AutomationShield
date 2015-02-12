 
/*
Sergio Mokshin
Automação Livre
Fev/2015

*/
 
#include <EtherCard.h>
#include <EEPROM.h>
#include <avr/wdt.h>

#define PIN_RED 6  
#define PIN_GREEN 5
#define PIN_BLUE 3
#define PIN_ALARM 3

#define CHAVE_1 2
#define CHAVE_2 4
#define CHAVE_3 7

int MemSaveSaida1 = 1;
int MemSaveSaida2 = 2;
int MemSaveSaida3 = 3;
int MemSaveSaida4 = 4;

int ValueSaveSaida1 = 0;
int ValueSaveSaida2 = 0;
int ValueSaveSaida3 = 0;
int ValueSaveSaida4 = 0;

// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[1000]; // tcp/ip send and receive buffer
BufferFiller bfill;

void setup(){  
  
   wdt_enable(WDTO_8S); //Watchdog 8 Segundos
   
  //Setup Inicial / descomentar build / comentar
  //EEPROM.write(MemSaveSaida1, 0);  
  //EEPROM.write(MemSaveSaida2, 0);
  //EEPROM.write(MemSaveSaida3, 0);          
  //EEPROM.write(MemSaveSaida4, 0);  
  
  
  Serial.begin(57600);
  Serial.println("Iniciando Setup");      
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(PIN_ALARM, OUTPUT);
    
  ValueSaveSaida1 = EEPROM.read(MemSaveSaida1);
  ValueSaveSaida2 = EEPROM.read(MemSaveSaida2);
  ValueSaveSaida3 = EEPROM.read(MemSaveSaida3);
  ValueSaveSaida4 = EEPROM.read(MemSaveSaida4);
    
  digitalWrite(A0, ValueSaveSaida1);
  digitalWrite(A1, ValueSaveSaida2);
  digitalWrite(A2, ValueSaveSaida3);
  digitalWrite(A3, ValueSaveSaida4);  
  
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
  {
    Serial.println( "Failed to access Ethernet controller");
  }

  ether.staticSetup(myip, gwip);
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
   

  analogWrite(6, 0);  
  analogWrite(5, 0);    
  analogWrite(3, 0);  
   
  Serial.println("Finalizando Setup");      
}

static word homePage() {
  
  Serial.println("Gerando Home Page");  
 
  int S1 = digitalRead(A0);
  int S2 = digitalRead(A1);
  int S3 = digitalRead(A2);
  int S4 = digitalRead(A3);  
  
  int Chave1 = digitalRead(CHAVE_1);  
  int Chave2 = digitalRead(CHAVE_2);  
  int Chave3 = digitalRead(CHAVE_3);  
  
  int LedR = analogRead(6);  
  int LedG = analogRead(5);  
  int LedB = analogRead(3);  
  
  int AL = digitalRead(PIN_ALARM);  
            
  bfill = ether.tcpOffset();
  
  bfill.emit_p(PSTR("<html><head>"));
  bfill.emit_p(PSTR("<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css' rel='stylesheet'></link>"));
  bfill.emit_p(PSTR("</head>"));
  bfill.emit_p(PSTR("<body>"));
  bfill.emit_p(PSTR("<div class='jumbotron'>"));
  bfill.emit_p(PSTR("<h2>Interface de comando</h2>"));
  bfill.emit_p(PSTR("<div class='row'>"));
  bfill.emit_p(PSTR("<div class='col-md-6'>"));
  bfill.emit_p(PSTR("<table class='table table-bordered'>"));
  bfill.emit_p(PSTR("<tbody>"));
  
  //SAIDA 1
  bfill.emit_p(PSTR("<tr><td width=200px>Saida 1 - "));
  if(S1 == HIGH)
  {
    bfill.emit_p(PSTR("On"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-danger btn-lg' href='/S1/OFF' type='button'>Desligar</button>"));
  }
  else
  {
    bfill.emit_p(PSTR("Off"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-success btn-lg' href='/S1/ON' type='button'>Ligar</button>"));        
  }        
  bfill.emit_p(PSTR("</td></tr>"));
  
  
  //SAIDA 2
  bfill.emit_p(PSTR("<tr><td width=200px>Saida 2 - "));
  if(S2 == HIGH)
  {
    bfill.emit_p(PSTR("On"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-danger btn-lg' href='/S2/OFF' type='button'>Desligar</button>"));
  }
  else
  {
    bfill.emit_p(PSTR("Desligado"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-success btn-lg' href='/S2/ON' type='button'>Ligar</button>"));        
  }        
  bfill.emit_p(PSTR("</td></tr>"));


  //SAIDA 3
  bfill.emit_p(PSTR("<tr><td width=200px>Saida 3 - "));
  if(S3 == HIGH)
  {
    bfill.emit_p(PSTR("Off"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-danger btn-lg' href='/S3/OFF' type='button'>Desligar</button>"));
  }
  else
  {
    bfill.emit_p(PSTR("Desligado"));
    bfill.emit_p(PSTR("</b></td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-success btn-lg' href='/S3/ON' type='button'>Ligar</button>"));        
  }        
  bfill.emit_p(PSTR("</td></tr>"));


  //SAIDA 4
  bfill.emit_p(PSTR("<tr><td width=200px>Saida 4 - "));
  if(S4 == HIGH)
  {
    bfill.emit_p(PSTR("Ligado"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-danger btn-lg' href='/S4/OFF' type='button'>Desligar</button>"));
  }
  else
  {
    bfill.emit_p(PSTR("Desligado"));
    bfill.emit_p(PSTR("</td><td>"));
    bfill.emit_p(PSTR("<a class='btn btn-success btn-lg' href='/S4/ON' type='button'>Ligar</button>"));        
  }        
  bfill.emit_p(PSTR("</td></tr>"));

  bfill.emit_p(PSTR("<tr><td colspan=2>Chave 1 - "));
  if(Chave1 == HIGH)
  {
    bfill.emit_p(PSTR("On"));    
  }
  else
  {
    bfill.emit_p(PSTR("Off"));        
  }

  bfill.emit_p(PSTR("<br>"));      
  bfill.emit_p(PSTR("Chave 2 - "));
  if(Chave2 == HIGH)
  {
    bfill.emit_p(PSTR("On"));    
  }
  else
  {
    bfill.emit_p(PSTR("Off"));        
  }
  
  bfill.emit_p(PSTR("<br>"));      
  bfill.emit_p(PSTR("Chave 3 - "));
  if(Chave3 == HIGH)
  {
    bfill.emit_p(PSTR("On"));    
  }
  else
  {
    bfill.emit_p(PSTR("Off"));        
  }
 

  bfill.emit_p(PSTR("</td></tr>"));  
    
  bfill.emit_p(PSTR("</tbody>"));
  bfill.emit_p(PSTR("</table>"));
  bfill.emit_p(PSTR("</div>"));
  bfill.emit_p(PSTR("</body>"));
  bfill.emit_p(PSTR("</html>"));
      
  return bfill.position();
}
 
 
void loop(){    
  
  WebServer();
  wdt_reset(); //diReset WatchDog
}
void WebServer()
{
 word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
 // char* dados =(char *)Ethernet::buffer + pos;  
 // if(pos >0)
 // {
 //    Serial.println(dados);  
 // }
  
    if(strstr((char *)Ethernet::buffer + pos, "GET /S1/ON") != 0) {
      Serial.println("Received ON command");
      digitalWrite(A0, HIGH);
      EEPROM.write(MemSaveSaida1, 1);
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /S1/OFF") != 0) {
      Serial.println("Received OFF command");
      digitalWrite(A0, LOW);
      EEPROM.write(MemSaveSaida1, 0);
    }
    
  if(strstr((char *)Ethernet::buffer + pos, "GET /S2/ON") != 0) {
      Serial.println("Received ON command");
       digitalWrite(A1, HIGH);
       EEPROM.write(MemSaveSaida2, 1);
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /S2/OFF") != 0) {
      Serial.println("Received OFF command");
       digitalWrite(A1, LOW);
       EEPROM.write(MemSaveSaida2, 0);   
    }

  if(strstr((char *)Ethernet::buffer + pos, "GET /S3/ON") != 0) {
      Serial.println("Received ON command");
       digitalWrite(A2, HIGH);
       EEPROM.write(MemSaveSaida3, 1); 
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /S3/OFF") != 0) {
      Serial.println("Received OFF command");
       digitalWrite(A2, LOW);
       EEPROM.write(MemSaveSaida3, 0);
       
    }

  if(strstr((char *)Ethernet::buffer + pos, "GET /S4/ON") != 0) {
      Serial.println("Received ON command");
       digitalWrite(A3, HIGH);
       EEPROM.write(MemSaveSaida4, 1);       
    }
  if(strstr((char *)Ethernet::buffer + pos, "GET /S4/OFF") != 0) {
      Serial.println("Received OFF command");
      digitalWrite(A3, LOW);
      EEPROM.write(MemSaveSaida4, 0);
   }     
   
  if(strstr((char *)Ethernet::buffer + pos, "GET /R/ON") != 0) {
      Serial.println("Received OFF command");
      analogWrite(5, 255);  
   }
   
   if(strstr((char *)Ethernet::buffer + pos, "GET /R/OFF") != 0) {
      Serial.println("Received OFF command");
      analogWrite(5, 0);  
   }
   
   if(strstr((char *)Ethernet::buffer + pos, "GET /G/ON") != 0) {
      Serial.println("Received OFF command");
      analogWrite(6, 255);  
   }
   
   if(strstr((char *)Ethernet::buffer + pos, "GET /G/OFF") != 0) {
      Serial.println("Received OFF command");
      analogWrite(6, 0);  
   }
   
   if(strstr((char *)Ethernet::buffer + pos, "GET /B/ON") != 0) {
      Serial.println("Received OFF command");
      analogWrite(3, 255);  
   }
   
   if(strstr((char *)Ethernet::buffer + pos, "GET /B/OFF") != 0) {
      Serial.println("Received OFF command");
      analogWrite(3, 0);  
   }
   
   
   if (pos) 
   {
    ether.httpServerReply(homePage());   
   }   
}

