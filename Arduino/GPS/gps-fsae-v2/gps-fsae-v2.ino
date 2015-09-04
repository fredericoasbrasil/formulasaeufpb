/* FORMULA SAE UFPB
 * DATA DE CRIAÇÃO: 20/08/2015
 * CRIADO POR: Frederico Augusto Santos Brasil
 * MANTIDO POR: Frederico Augusto Santos Brasil
 * DESCRIÇÃO: Utilizando as bibliotecas TinyGPS++ e SoftwareSerial, imprime os dados DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES
 * FUNÇÕES: Imprimir os valores obtidos através do módulo GPS no console serial, salvar em cartao SD e transmitir via xbee.
 * VERSÃO: 0.1
 */

#include <TinyGPS++.h>


//GPS 5V
//RXPin ligado ao pino TX do GPS 1
//TXPin ligado ao pino RX do GPS 1
static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 4800;



// O objeto TinyGPS++
TinyGPSPlus gps;



// A coneão serial com o modulo
//SoftwareSerial ss(RXPin, TXPin);
//HardwareSerial ss = Serial1;;

void setup() {

  Serial.begin(115200);
  //ss.begin(GPSBaud);
  Serial1.begin(9600);
  Serial.println("Formula UFPB - Sensoriamento");
  Serial.println("Demonstrando leitura de campos NMEA utilizando a biblioteca TinyGPS++");
  Serial.println("Formato dos campos gravados no cartao SD e transmissao por Xbee");
  Serial.println("###DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES###");
  Serial.println("__________________________________________________________________________");
}

void loop() 
{
  
    //Serial.println(Serial1.read());
    //delay(300);
    
    gps.encode(Serial1.read());
  
    delay(100);
    
    Serial.print(gps.date.value()); // Data no formato DDMMYY
    Serial.print(",");
    Serial.print(gps.time.value()); // Hora no formato HHMMSSCC
    Serial.print(",");
    Serial.print(gps.speed.kmph()); // Velocidade instantanea em Km/h
    Serial.print(",");
    Serial.print(gps.location.lat(), 6); // Latitude em graus
    Serial.print(",");
    Serial.print(gps.location.lng(), 6); // Longitude em graus
    Serial.print(",");
    Serial.print(gps.altitude.meters());  // Altitude em metros
    Serial.print(",");
    Serial.println(gps.satellites.value()); // Quantidade de satelites rastreados


}
