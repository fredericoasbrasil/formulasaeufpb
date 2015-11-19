#include <nmea.h>

NMEA gps(GPRMC);
float ultima_lat;
float ultima_lon;
double odometro;

void setup(){
  Serial1.begin(4800); // Conectado ao GPS
  Serial.begin(9600); // Saida Serial para impressao na tela
  delay(2000);

  Serial.println("********************************************************");
  Serial.println("*         Formula SAE UFPB - Equipe Combustao          *");
  Serial.println("*   Datalogger - Sessao iniciada em: 19/09/2015 10:05  *");
  Serial.println("********************************************************");
  Serial.println("");
  Serial.println("");
  Serial.println("");

    Serial.print("Verificando Cartao SD");
    delay(500);
    Serial.print(" - - - ");
    delay(500);
    Serial.println(" OK");
    Serial.println("");

    Serial.print("Verificando conexao XBEE");
    delay(500);
    Serial.print(" - - - ");
    delay(500);
    Serial.println(" OK");
    Serial.println("");

    Serial.print("Verificando Acelerometro/Giroscopio");
    delay(500);
    Serial.print(" - - - ");
    delay(500);
    Serial.println(" OK");
    Serial.println("");

    delay(300);
    Serial.print("Calibrando Acelerometro/Giroscopio");
    delay(500);

  for (int i = 1; i < 6; i++){
    Serial.print("...");
    Serial.print(i);
    delay(1000);
  }
  Serial.println(" OK");
  Serial.println("");
  delay(300);

  Serial.print("Verificando GPS");
  delay(500);
  Serial.print(" - - - ");
  delay(200);
  Serial.println(" OK");
  Serial.println("");
  delay(300);

  Serial.println("Aguardando 'FIX' do GPS");

  while (Serial1.available()) {
  //  Serial.println("Entrou");
    char c = Serial1.read();
    if (gps.decode(c)) {
      if (gps.gprmc_status() == 'A') {
        Serial.println("Status OK");
        break;
      }
    }
  }

  for (int i = 1; i < 6; i++){
    Serial.print("...");
    Serial.print(i);
    delay(1000);
  }
  Serial.println(" OK");
  Serial.println("");
  delay(300);
  
  

  Serial.println("Sistema pronto e gravando. Iniciando Datalog.");
  Serial.println("Padrão dos dados:");

}

void loop(){

  // Verifica se a Serial1 conectada ao GPS está disponivel
  if (Serial1.available()) {

    //Le a Serial1
    if (gps.decode(Serial1.read())) {
      //Se encontrar sentença GPS válida, executa as medições, caso contrário inicia o loop novamente
      if (gps.gprmc_status() == 'A') {

      // Rotinas do GPS
      String dados = "";
      
      float latitude, longitude;
      char lat[12];
      char lon[12];
      longitude = gps.gprmc_longitude();
      latitude = gps.gprmc_latitude();
      dtostrf(latitude,1,5,lat);
      dtostrf(longitude,1,5,lon);

      dados += String(lon);
      dados += ",";
      dados += String(lat);
      dados += ",";
      dados += gps.gprmc_speed(KMPH);
      dados += ",";
      odometro += gps.gprmc_distance_to(ultima_lat, ultima_lon, MTR);
      ultima_lon = longitude;
      ultima_lat = latitude;
      dados += odometro;
      dados += ",";

      //Rotinas do RTC

      // Rotinas do Acelerometro/Giroscopio

      // Rotinas do Cartão SD

      // Rotinas do XBEE


      //Saida dos dados
      Serial.println(dados);



      }
    }
  }
}
