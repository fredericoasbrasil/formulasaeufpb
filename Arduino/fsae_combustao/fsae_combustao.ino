

#include <TinyGPS++.h>

/* FORMULA SAE UFPB
 * DATA DE CRIAÇÃO: 04/09/2015
 * CRIADO POR: Frederico Augusto Santos Brasil
 * MANTIDO POR: Frederico A. S. Brasil | Filipe Cavalcanti | Josias Ferreira
 * DESCRIÇÃO: Versão final do software respsonsável pela telemetria e sensoriamento da equipe Formula UFPB - Combustão na competição 2015
 * FUNÇÕES: Data/Hora, Velocidade Instantânea, Latitude, Longitude, Inclinação, Aceleração linear e lateral
 * VERSÃO: 1.0
 * FRITZING: fsae_combustao.fzz
 */

 

// ------------------------------------------------------
// Declarações e bibliotecas relativas ao GPS e RTC
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <TinyGPS++.h>

TinyGPSPlus gps;


// ------------------------------------------------------
// Declarações e bibliotecas relativas ao Giroscópio e Acelerômetro
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ------------------------------------------------------
// Declarações e bibliotecas relativas ao Xbee e Cartão SD
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++

 void setup() {

	//Inicializa o console serial
	Serial.begin(115200);
	
	
	// ------------------------------------------------------
	// Configurações relativas ao GPS e RTC
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	//GPS conectado a Serial1 do arduino Mega
	Serial1.begin(4800);

	// ------------------------------------------------------
	// Configurações relativas ao Giroscópio e Acelerômetro
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++


	// ------------------------------------------------------
	// Configurações relativas ao Xbee e Cartão SD
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++

}

void loop() {

// ------------------------------------------------------
// Rotinas relativas ao GPS e RTC
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
	while(Serial1.available()){
		if(gps.encode(Serial1.read())){
			Serial.print(gps.date.value()); // Data no formato DDMMYY
			Serial.print(";");
			Serial.print(gps.time.value()); // Hora no formato HHMMSSCC
			Serial.print(";");
			Serial.print(gps.speed.kmph()); // Velocidade instantanea em Km/h
			Serial.print(";");
			Serial.print(gps.location.lat(), 6); // Latitude em graus
			Serial.print(";");
			Serial.print(gps.location.lng(), 6); // Longitude em graus
			Serial.print(";");
			Serial.print(gps.altitude.meters());  // Altitude em metros
			Serial.print(";");
			Serial.print(gps.satellites.value()); // Quantidade de satelites rastreados
			Serial.println(";");
			break;
		}
		break;
	}

// ------------------------------------------------------
// Rotinas relativas ao Giroscópio e Acelerômetro
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ------------------------------------------------------
// Rotinas relativas ao Xbee e Cartão SD
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++



}
