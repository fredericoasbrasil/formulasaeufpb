 /* FORMULA SAE UFPB/ FORMULA SAE ELÉTRICO UFPB;
 * DATA DE CRIAÇÃO 04/08/2015;
 * CRIADO POR: JOSIAS FERREIRA SILVEIRA DE SOUZA;
 * MANTIDO POR: JOSIAS FERREIRA SILVEIRA DE SOUZA;
 * DESCRIÇÃO: Descrição geral da biblioteca;
 * FUNÇÕES:  
	ler coordenada - gerar ângulo e aceleração output (Ax°,Ay°,Az°) e (Ix°,Iy°,Iz°);
	ler aceleraração - gerar gráfico de força G output (gráfico força G);
	ler temperatura - gerar temperatura em Kelvin;
 * VERSÃO:0.1
 
 #ifndef giro_h
 #define giro_h
 
 #include "Arduino.h"
 #include "wire.h"
 #define CG= 1 // Constante conversao de força G;
 #define CA= 1 // Constante conversao de angulo;
 #define CT= 1 // Constante de conversão de temperatura; 
 
 class giro
 {
   public:
     void atualizar(void); // Função de aquisição de dados do giro
     //  Funções de dados individuais;
     int AceX(void){return AceleX*CG};
     int AceY(void){return AceleY*CG};
     int AceZ(void){return AceleZ*CG};
     int Temp(void){return Temperatura*CT};
     int AngX (void){return AnguloX*CA);
     int AngY (void){return AnguloY*CA);
     int AngZ (void){return AnguloZ*CA);
     
   private:
     int AceleX, AceleY, AceleZ, Temperatura, AnguloX,AnguloY,AnguloZ;
 }
 endif
