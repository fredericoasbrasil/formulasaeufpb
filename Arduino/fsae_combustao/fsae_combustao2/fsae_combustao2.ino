
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
//#include <stdlib.h>
#include <SdFat.h>
char latit[10];
char longit[10];


// ------------------------------------------------------
// Declarações e bibliotecas relativas ao Giroscópio e Acelerômetro
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Wire.h> // Inclue biblioteca serial;

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24


int ADXAddress = 0x53;  // the default 7-bit slave address
int reading = 0;
int val=0;
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg;
int x; 
int y;
int z;

//Endereco I2C do L3G4200D
int L3G4200D_Address = 105;

// ------------------------------------------------------
// Declarações e bibliotecas relativas ao Xbee e Cartão SD
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

const int chipSelect = 53;

void setup() {

	//Inicializa o console serial
	Serial.begin(9600);
	
	
	// ------------------------------------------------------
	// Configurações relativas ao GPS e RTC
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	//GPS conectado a Serial1 do arduino Mega
	Serial1.begin(4800);

	// ------------------------------------------------------
	// Configurações relativas ao Giroscópio e Acelerômetro
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
        Serial.println("Inicializando o L3G4200D"); // Configura o L3G4200 para 200, 500 ou 2000 graus/seg
        setupL3G4200D(2000);
        Wire.begin(); 
        delay(100);
        // enable to measute g data
        Wire.beginTransmission(ADXAddress); //Envia Endereço;
        Wire.write(Register_2D);
        Wire.write(8);                // measuring enable
        Wire.endTransmission();       // Encerra a transmissão 
        delay(1500);                  // Aguarda a resposta do sensor

	// ------------------------------------------------------
	// Configurações relativas ao Xbee e Cartão SD
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
          Serial.print("Inicializando SD Card...");
          //pinMode(10, OUTPUT);
          //Verifica se o cartão SD está conectado
          if (!SD.begin(chipSelect))
          Serial.println(" Erro!");
          else
          Serial.println(" OK!");
          
}

void loop() {
// ------------------------------------------------------
// Rotinas relativas ao GPS e RTC
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
String dados = "";
               while(Serial1.available()){
		if(gps.encode(Serial1.read())){
			/*Serial.print(gps.date.value()); // Data no formato DDMMYY
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
			Serial.println(";");*/
                        dtostrf((gps.location.lat()), 5, 5, latit);
                        dtostrf((gps.location.lng()), 5, 5, longit);
                        
// ------------------------------------------------------
// Rotinas relativas ao Giroscópio e Acelerômetro
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++

//--------------X
        Wire.beginTransmission(ADXAddress); // transmit to device
        Wire.write(Register_X0);
        Wire.write(Register_X1);
        Wire.endTransmission();
        Wire.requestFrom(ADXAddress,2); 
          if(Wire.available()<=2)   
          {
            X0 = Wire.read();
            X1 = Wire.read(); 
            X1=X1<<8;
            X_out=X0+X1;   
          }

//------------------Y
        Wire.beginTransmission(ADXAddress); // transmit to device
        Wire.write(Register_Y0);
        Wire.write(Register_Y1);
        Wire.endTransmission();
        Wire.requestFrom(ADXAddress,2); 
          if(Wire.available()<=2)   
          {
            Y0 = Wire.read();
            Y1 = Wire.read(); 
            Y1=Y1<<8;
            Y_out=Y0+Y1;
          }
//------------------Z
        Wire.beginTransmission(ADXAddress); // transmit to device
        Wire.write(Register_Z0);
        Wire.write(Register_Z1);
        Wire.endTransmission();
        Wire.requestFrom(ADXAddress,2); 
          if(Wire.available()<=2)   
            {
            Z0 = Wire.read();
            Z1 = Wire.read(); 
            Z1=Z1<<8;
            Z_out=Z0+Z1;
            }
  //
  Xg=X_out/256.0;
  Yg=Y_out/256.0;
  Zg=Z_out/256.0;

  
// Atualiza os valores de X, Y e Z  da inclinação;
 getGyroValues();
 //Escreve todos os dados na string;
 dados += (gps.date.value()); dados += (";"); dados += (gps.time.value()); dados += (";");  dados += (gps.speed.kmph()); dados += (";");  
 dados += (latit); dados += (";"); dados += (longit); dados += (";");  dados += (gps.altitude.meters()); dados += (";");  
 dados += (gps.satellites.value()); dados += (";");
 dados += (Xg); dados += (";"); dados += (Yg); dados += (";"); dados += (Zg); dados += (";");dados += (x); dados += (";"); dados += (y); dados += (";"); dados += (z);


// ------------------------------------------------------
// Rotinas relativas ao Xbee e Cartão SD
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
Serial.println(dados);
File dataFile = SD.open("testeprot8.txt", FILE_WRITE);
  //escreve os dados e fecha o arquivo
  if (dataFile) {
    dataFile.println(dados);
    dataFile.close();
  }
 }
}
}
               
               
// Colocar comentários sobre as subfunções do giro;

void getGyroValues()
{
  // Rotina para leitura dos valores de X, Y e Z
  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  x = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  y = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  z = ((zMSB << 8) | zLSB);
}

int setupL3G4200D(int scale)
{
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:
  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void writeRegister(int deviceAddress, byte address, byte val) 
{
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address)
{
    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) 
    {
        // waiting
    }
    v = Wire.read();
    return v;
}
