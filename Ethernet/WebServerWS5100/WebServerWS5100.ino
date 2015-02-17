/*
Sergio Mokshin
Automação Live - Jan /2015

*/

#include <SPI.h>
#include <Ethernet.h>

#include <Servo.h>
Servo myservo;  // create servo object to cLigadotrol a servo

byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0D, 0xA6, 0x09 }; //physical mac address
byte ip[] = { 
  192, 168, 0, 177 }; // ip in lan
byte gateway[] = { 
  192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 
  255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port


#define CHAVE_1 2
#define CHAVE_2 4
#define CHAVE_3 7

#define PIN_RED 3 
#define PIN_GREEN 6
#define PIN_BLUE 5

String readString;

void setup(){


  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

}

void loop(){

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {

          Serial.println(readString);
          
          if(readString.indexOf("?S1Ligado") >0) { 
            digitalWrite(A0, HIGH);
          }
          if(readString.indexOf("?S1Desligado") >0) { 
            digitalWrite(A0, LOW);
          }

          if(readString.indexOf("?S2Ligado") >0) { 
            digitalWrite(A1, HIGH);
          }
          if(readString.indexOf("?S2Desligado") >0) { 
            digitalWrite(A1, LOW);
          }

          if(readString.indexOf("?S3Ligado") >0) { 
            digitalWrite(A2, HIGH);
          }
          if(readString.indexOf("?S3Desligado") >0) { 
            digitalWrite(A2, LOW);
          }

          if(readString.indexOf("?S4Ligado") >0) { 
            digitalWrite(A3, HIGH);
          }
          if(readString.indexOf("?S4Desligado") >0) { 
            digitalWrite(A3, LOW);
          }

          if(readString.indexOf("?red") >0) { 
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 0);              
            analogWrite(PIN_BLUE, 0);
          }

          if(readString.indexOf("?green") >0) { 
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 255);              
            analogWrite(PIN_BLUE, 0);
          }

          if(readString.indexOf("?blue") >0) { 
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 0);              
            analogWrite(PIN_BLUE, 255);
          }

          if(readString.indexOf("?white") >0) { 
            analogWrite(PIN_RED, 255);
            analogWrite(PIN_GREEN, 255);              
            analogWrite(PIN_BLUE, 255);
          }


          if(readString.indexOf("?rgboff") >0) { 
            analogWrite(PIN_RED, 0);
            analogWrite(PIN_GREEN, 0);              
            analogWrite(PIN_BLUE, 0);
          }

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

          client.println(F("HTTP/1.1 200 OK")); //send new page
          client.println(F("Content-Type: text/html"));
          client.println();

          client.println(F("<HTML>"));
          client.println(F("<HEAD>"));
          client.println(F("<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css' rel='stylesheet'></link>"));
          client.println(F("</head>"));
          client.println(F("<body>"));
          client.println(F("<div class='jumbotron'>"));
          client.println(F("<h2>Interface de comando</h2>"));
          client.println(F("<div class='row'>"));
          client.println(F("<div class='col-md-10'>"));
          client.println(F("<table class='table table-bordered'>"));
          client.println(F("<tbody>"));
          //S 1
          client.println(F("<tr><td width=130px>S 1 - "));
          if(S1 == HIGH)
          {
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S1Desligado'>Desligar</buttLigado>"));
          }
          else
          {
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S1Ligado'>Ligar</buttLigado>"));        
          }        
          client.println(F("</td></tr>"));


          //S 2
          client.println(F("<tr><td width=130px>S 2 - "));
          if(S2 == HIGH)
          {
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S2Desligado'>Desligar</buttLigado>"));
          }
          else
          {
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S2Ligado'>Ligar</buttLigado>"));        
          }        
          client.println(F("</td></tr>"));


          //S 3
          client.println(F("<tr><td width=130px>S 3 - "));
          if(S3 == HIGH)
          {
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S3Desligado'>Desligar</buttLigado>"));
          }
          else
          {
            client.println(F("Desligado"));
            client.println(F("</b></td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S3Ligado'>Ligar</buttLigado>"));        
          }        
          client.println(F("</td></tr>"));


          //S 4
          client.println(F("<tr><td width=130px>S 4 - "));
          if(S4 == HIGH)
          {
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S4Desligado'>Desligar</buttLigado>"));
          }
          else
          {
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S4Ligado'>Ligar</buttLigado>"));        
          }        
          client.println(F("</td></tr>"));


          //RGB
          client.println(F("<tr><td>RGB</td><td>"));
          client.println(F("<a class='btn btn-primary btn-lg' href='?blue' >Azul</a>&nbsp;"));
          client.println(F("<a class='btn btn-danger btn-lg' href='?red' >Vermelho</a>&nbsp;"));        
          client.println(F("<a class='btn btn-success btn-lg' href='?green' >Verde</a>&nbsp;"));        
          client.println(F("<a class='btn btn-default btn-lg' href='?white' >Branco</a>&nbsp;"));                    
          client.println(F("<a class='btn btn-link' href='?rgboff' >Desligar</a>&nbsp;"));                                                            
          client.println(F("</td></tr>"));




          client.println(F("<tr><td colspan=2>Chave 1 - "));
          if(Chave1 == HIGH)
          {
            client.println(F("<span class='glyphicon glyphicon-ok-circle' aria-hidden='true'></span>"));    
          }
          else
          {
            client.println(F("<span class='glyphicon glyphicon-ban-circle' aria-hidden='true'></span>"));    
          }

          client.println(F("<br>"));      

          client.println(F("Chave 2 - "));
          if(Chave2 == HIGH)
          {
            client.println(F("<span class='glyphicon glyphicon-ok-circle' aria-hidden='true'></span>"));    
          }
          else
          {
            client.println(F("<span class='glyphicon glyphicon-ban-circle' aria-hidden='true'></span>"));    
          }


          client.println(F("<br>"));      
          client.println(F("Chave 3 - "));

          if(Chave3 == HIGH)
          {
            client.println(F("<span class='glyphicon glyphicon-ok-circle' aria-hidden='true'></span>"));    
          }
          else
          {
            client.println(F("<span class='glyphicon glyphicon-ban-circle' aria-hidden='true'></span>"));    
          }

          client.println(F("<br>"));      
          client.println(F("<a class='btn btn-link' href='/'>Verificar status chaves</a>"));                                                            
          
          
          client.println(F("</td></tr>"));  
          
		  
          client.println(F("</tbody>"));
          client.println(F("</table>"));
          client.println(F("</div>"));

          client.println(F("</body>"));
          client.println(F("</html>"));

          delay(1);
          //stopping client
          client.stop();

          //clearing string for next read
          readString="";

        }
      }
    }
  }
}













