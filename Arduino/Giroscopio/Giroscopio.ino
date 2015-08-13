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


void setup() {
  class giro{
    public:
      int AcX (void);
      int AcY (void);
      int AcZ (void);
      int GX (void);
      int GY (void);
      int GZ (void);
      int temp (void);
    private:
    int AX,AY,AZ,IX,IY,IZ,TEMP;
    void leitura (int, int);
  }
}

void loop() {
  // CÓDIGO QUE SERÁ EXECUTADO REPETIDAMENTE
  // ROTINAS DETERMINADAS PARA O ARDUINO

}

void  giro::leitura (int a, int b) {
//Executar protocolo I²C
pinMode(a,OUTPUT); // OUTPUT para saída do clock do Arduíno para o Giroscópio;
pinMode(b.INPUT); //  INMPUT para recepção de dados do Giroscópio para o Arduíno
}

