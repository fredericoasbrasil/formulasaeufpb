#include <nmea.h>

NMEA gps(GPRMC);

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
    Serial.println("Entrou");
    char c = Serial1.read();
    if (gps.decode(c)) {
      if (gps.gprmc_status() == 'A') {
        Serial.println("FIX obtido");
      } else {
        Serial.println("Sem FIX");
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

}

void loop(){



}
