/* FORMULA SAE UFPB
 * DATA DE CRIAÇÃO: 20/08/2015
 * CRIADO POR: Frederico Augusto Santos Brasil
 * MANTIDO POR: Frederico Augusto Santos Brasil
 * DESCRIÇÃO: Utilizando as bibliotecas TinyGPS++ e SoftwareSerial, imprime os dados DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES
 * FUNÇÕES: Imprimir os valores obtidos através do módulo GPS no console serial, salvar em cartao SD e transmitir via xbee.
 * VERSÃO: 0.1
 */

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//GPS 5V
//RXPin ligado ao pino TX do GPS 1
//TXPin ligado ao pino RX do GPS 1
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;


//GPS 3.3V
//RXPin ligado ao pino TX do GPS 2
//TXPin ligado ao pino RX do GPS 2
static const int RXPin2 = 7, TXPin2 = 6;
static const uint32_t GPSBaud2 = 4800;


// O objeto TinyGPS++
TinyGPSPlus gps;
TinyGPSPlus gps2;

// A coneão serial com o modulo
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial ss2(RXPin2, TXPin2);

void setup() {

  Serial.begin(115200);
  ss.begin(GPSBaud);
  ss2.begin(GPSBaud2);
  Serial.println("Formula UFPB - Sensoriamento");
  Serial.println("Demonstrando leitura de campos NMEA utilizando a biblioteca TinyGPS++");
  Serial.println("Formato dos campos gravados no cartao SD e transmissao por Xbee");
  Serial.println("###DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES###");
  Serial.println("__________________________________________________________________________");
}

void loop() 
{
  

  
  if (gps.satellites.isUpdated())
  {
    Serial.print("###");
    Serial.print(gps.date.value()); // Data no formato DDMMYY
    Serial.print(",");
    Serial.println(gps.time.value()); // Hora no formato HHMMSSCC
    Serial.print(",");
    Serial.print(gps.speed.kmph()); // Velocidade instantanea em Km/h
    Serial.print(",");
    Serial.print(gps.location.lat(), 6); // Latitude em graus
    Serial.print(",");
    Serial.print(gps.location.lng(), 6); // Longitude em graus
    Serial.print(",");
    Serial.print(gps.altitude.meters());  // Altitude em metros
    Serial.print(",");
    Serial.print(gps.satellites.value()); // Quantidade de satelites rastreados
    Serial.println("###");
  }
  
  
    if (gps2.satellites.isUpdated())
  {
    Serial.print("$$$");
    Serial.print(gps2.date.value()); // Data no formato DDMMYY
    Serial.print(",");
    Serial.println(gps2.time.value()); // Hora no formato HHMMSSCC
    Serial.print(",");
    Serial.print(gps2.speed.kmph()); // Velocidade instantanea em Km/h
    Serial.print(",");
    Serial.print(gps2.location.lat(), 6); // Latitude em graus
    Serial.print(",");
    Serial.print(gps2.location.lng(), 6); // Longitude em graus
    Serial.print(",");
    Serial.print(gps2.altitude.meters());  // Altitude em metros
    Serial.print(",");
    Serial.print(gps2.satellites.value()); // Quantidade de satelites rastreados
    Serial.println("$$$");
  }
  

  while (ss.available() > 0)
    gps.encode(ss.read());
    
  while (ss2.available() > 0)
    gps2.encode(ss2.read());    
    
    
      //Codigo de debug, imprime o valor RAW obtido no console. Usar apenas para testes
 
 /* while (true) {// infinite loop
    if (ss.available() > 0) // any data coming in?
      Serial.write(ss.read());
  } */
}
