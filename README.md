

Desenvolvido com o objetivo de simplificar a criação de projetos de automação. É compatível com o Arduino Nano V3 e pode ser usada em diversos projetos de automação, monitoramento, temporizadores, entre outros. 

![Automation Shield](https://github.com/sergiomokshin/AutomationHome/blob/master/Imagens/AutomationHomePCB.png)\

Os IOs da placa possuem Jumpers que permitem a inativação ou troca do pino utilizado no Arduino, permitindo expansão ou troca de funcionalidades.

A placa incorpora as seguintes funcionalidades:
Agilidade na integração de componentes de um projeto.
Barra de terminais para conexão direta com o Arduino nano, eliminando ligações adicionais.
Jumpers que permitem inativação ou troca do pino utilizado no Arduino, permitindo expansão ou troca de funcionalidades.
Barra de terminais integrados com todos os pinos do Arduino para integração com outros Shields e sensores.
Alimentação regulada para o Arduino.
Born KRE e barra de terminais com saída regulada de 5V x 1A para alimentação de sensores, lcd, motores, servores, entre outros.
4 saídas de relés 120V 15A / 220V 10A;
3 saídas transistorizadas TIP 120 - 5A PWM para RGB.
Dimensões: 97 x 150 x 40 mm (Largura x Comprimeto x Altura) 

![Automation Shield](http://3.bp.blogspot.com/-B60DkR16E_A/VMQuYUDE4KI/AAAAAAAAHfY/bxB8-eHgN7M/s1600/esquema%2Bde%2Bliga%C3%A7%C3%B5es.png)

Pinos utilizados 
A0, A1, A2 e A3: utilizados para saídas com relés *.
D3, D5 e D6: utilizados para saídas PWM de potência *.
*Os pinos possuem jumpers que permitem a inativação ou troca do pino do Arduino nano utilizado.

Exemplos de projetos desenvolvidos com o Shield

WebServer de automação com enc28j60.
![Automation Shield](http://4.bp.blogspot.com/-H1HWUSNyQPk/VNZYdfWpdfI/AAAAAAAAHrw/bjMMNj8l8OM/s1600/enc.png)

WebServer de automação com WS5100.
![Automation Shield](http://4.bp.blogspot.com/-H1HWUSNyQPk/VNZYdfWpdfI/AAAAAAAAHrw/bjMMNj8l8OM/s1600/enc.png)

Temporizador de saídas.
![Automation Shield](http://2.bp.blogspot.com/-xuz5d9oZ_Q8/VNZYcAItJpI/AAAAAAAAHrk/O4r85BD7HoU/s1600/Ethernet.png)

Cada projeto tem características individuais, que exigem recursos diferenciados de processamento, memória, comunicação serial, leituras digitais, analógicas, PWM entre outros. Quando usamos a plataforma Arduino, devemos avaliar entre as versões disponíveis, qual atende os requisitos funcionais do nosso projeto.

Vamos publicar uma série de artigos de projetos úteis, com código fonte aberto, integrando com LCD, RTC, BlueTooth, WiFi, Ethernet, WebServer, WebCliente, Android, entre outros.

Teste Básico de acionamento das saídas do Shield 

/*
Sergio Mokshin
Automação Livre
Jan/2015
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
