/* FORMULA SAE UFPB/ FORMULA SAE ELÉTRICO UFPB;
 * DATA DE CRIAÇÃO 04/08/2015;
 * CRIADO POR: JOSIAS FERREIRA SILVEIRA DE SOUZA;
 * MANTIDO POR: JOSIAS FERREIRA SILVEIRA DE SOUZA;
 * DESCRIÇÃO: Biblioteca de leitura de Giroscópio GY 521 utilizando protocolo I²C;
 * FUNÇÕES:  
	ler coordenada - gerar ângulo e aceleração output (Ax°,Ay°,Az°) e (Ix°,Iy°,Iz°);
	ler aceleraração - gerar gráfico de força G output (gráfico força G);
	ler temperatura - gerar temperatura em Kelvin;
 * VERSÃO:0.1
 * Entradas:PINO SCL, PINO SDA;
 * Saídas: AX,AY,AZ,IX,IY,IZ,TEMP; 
 */
 #include"Wire.h"

 void setup(
 
 class giro{
  public:
    void atualizar (void);
    int AcX void{return AceleX};
    int AcY void{return AceleY};
    int AcZ void{return AceleZ};
    int AnX void{return AnguloZ};
    int AnY void{return AnguloY};
    int AnZ void{return AnguloZ};
    int Temp void{return Temperatura};
  private:
    int AceleX, AceleY, AceleZ, Temperatura, AnguloX,AnguloY,AnguloZ;  
          }
}

void giro::atualizar (void){
  Wire.write(0); 
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AceleX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AceleY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AceleZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temperatura=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  AnguloX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  AnguloY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  AnguloZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}



