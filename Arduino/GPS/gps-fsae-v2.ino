#include <TinyGPS++.h>
#include <SoftwareSerial.h>


//RXPin ligado ao pino TX do GPS
//TXPin ligado ao pino RX do GPS
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;

// O objeto TinyGPS++
TinyGPSPlus gps;

// A coneão serial com o modulo
SoftwareSerial ss(RXPin, TXPin);

void setup() {

  Serial.begin(115200);
  ss.begin(GPSBaud);
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
  }*/

  while (ss.available() > 0)
    gps.encode(ss.read());
    
    
      //Codigo de debug, imprime o valor RAW obtido no console. Usar apenas para testes
 
 /* while (true) {// infinite loop
    if (ss.available() > 0) // any data coming in?
      Serial.write(ss.read());
  } */
}
