/* FORMULA SAE UFPB
 * DATA DE CRIAÇÃO: 20/08/2015
 * CRIADO POR: Frederico Augusto Santos Brasil
 * MANTIDO POR: Frederico Augusto Santos Brasil
 * DESCRIÇÃO: Utilizando as bibliotecas TinyGPS++ e SoftwareSerial, imprime os dados DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES
 * FUNÇÕES: Imprimir os valores obtidos através do módulo GPS no console serial, salvar em cartao SD e transmitir via xbee.
 * VERSÃO: 0.1
 */

#include <TinyGPS++.h>
// O objeto TinyGPS++
TinyGPSPlus gps;

void setup() {

  Serial.begin(115200);
  //GPS Conectado a Hardware Serial1(TX 18, RX 19)
  Serial1.begin(4800);
  
  Serial.println("Formula UFPB - Sensoriamento");
  Serial.println("Demonstrando leitura de campos NMEA utilizando a biblioteca TinyGPS++");
  Serial.println("Formato dos campos gravados no cartao SD e transmissao por Xbee");
  Serial.println("###DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES###");
  Serial.println("__________________________________________________________________________");
}

void loop() 
{
	while(Serial1.available()){
		if(gps.encode(Serial1.read())){
		
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
	}

}
