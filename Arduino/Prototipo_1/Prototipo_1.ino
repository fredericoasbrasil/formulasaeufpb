/* FORMULA SAE UFPB
 * DATA DE CRIAÇÃO: 20/08/2015
 * CRIADO POR: Filipe do Ó Cavalcanti, Frederico Augusto Santos Brasil e Josias Ferreira Silveira de Souza;
 * MANTIDO POR: Filipe do Ó Cavalcanti, Frederico Augusto Santos Brasil e Josias Ferreira Silveira de Souza;
 * DESCRIÇÃO: Utilizando as bibliotecas TinyGPS++ e SoftwareSerial, imprime os dados DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES  (alterar)
  * FUNÇÕES: Imprimir os valores obtidos através do módulo GPS e Giroscópio GY-80, salvar os valores em um cartão SD, transmitir via Xbee;  
 * VERSÃO: 0.1
 */


#include <TinyGPS++.h>

#include <Wire.h> // Inclue biblioteca serial;
#include <math.h> // Inclue biblioteca matemática;
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

// Variáveis definidas para acelerômetro/giroscopio
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

TinyGPSPlus gps;
// O objeto TinyGPS++
// A coneão serial com o modulo
//SoftwareSerial ss(RXPin, TXPin);
//HardwareSerial ss = Serial1;;
//GPS 5V
//RXPin ligado ao pino TX do GPS 1
//TXPin ligado ao pino RX do GPS 1
static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 4800;

// variáveis para acelerômetro

int ADXAddress = 0x53;  // the default 7-bit slave address
int reading = 0;
int val=0;
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg;

// Variáveis para giroscópio
int x = 0; 
int y = 0;
int z = 0;

//Endereco I2C do L3G4200D
int L3G4200D_Address = 105;

//Const do SD
const int chipSelect = 4;


void setup()
{
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Formula UFPB - Sensoriamento");
  Serial.println("Demonstrando leitura de campos NMEA utilizando a biblioteca TinyGPS++");
  Serial.println("Formato dos campos gravados no cartao SD e transmissao por Xbee");
  Serial.println("###DATA,HORA,VELOCIDADE,LATITUDE,LONGITUDE,ALTITUDE,SATELITES###");
  Serial.println("__________________________________________________________________________");


  Serial.println("Inicializando o L3G4200D");
  // Configura o L3G4200 para 200, 500 ou 2000 graus/seg
  setupL3G4200D(2000);
  Wire.begin(); 
  delay(100);
  // enable to measute g data
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);                //measuring enable
  Wire.endTransmission();     // stop transmitting 

  // Aguarda a resposta do sensor
  delay(1500); 
    
  //Testa o SD
  Serial.println("--Formula SAE-E UFPB 2016--");
  Serial.print("\nInicializando SD Card...");
  pinMode(10, OUTPUT);
  //verifica se o cartao SD esta conectado
  if (!SD.begin(chipSelect)) {
    Serial.println("Erro!");
    Serial.end();
  }
  else
    Serial.println("Conectado!");

}


void loop()
{
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
  gps.encode(Serial.read());
  
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
  
  String dados = "";
  dados += (Xg);
  dados += (",");
  dados += (Yg);
  dados += (",");
  dados += (Zg);
  dados += (",");
//  Serial.print("Aceleracao    X= ");
//  Serial.print(Xg);
//  Serial.print("    Y= ");
//  Serial.print(Yg);
//  Serial.print("    Z= ");
//  Serial.print(Zg);
//  delay(200);
  dados += (x);
  dados += (",");
  dados += (y);
  dados += (",");
  dados += (z);
  
  Serial.println(dados);
  
  File dataFile = SD.open("testeprot1.txt", FILE_WRITE);
  //escreve os dados e fecha o arquivo
  if (dataFile) {
    dataFile.println(dados);
    dataFile.close();

  delay (250);

//  Serial.print("           Inclinacao   X:");
//  Serial.print(x);
//  Serial.print("   Y:");
//  Serial.print(y);
//  Serial.print("   Z:");
//  Serial.println(z); 
//delay(250);
}
}



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



