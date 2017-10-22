#include<htc.h>
#include<pic.h>
#include "lib.h"
#include "adc.h"

void ADC_Init(){
	bitset(TRISA, 0); //habilita RA0 como entrada
	bitset(ANSEL, 0); //habilita RA0 como anal�gico
	//config o A/D para clock RC
	ADCON1 = CLOCK_AD;
	//ajustado � direita, com VDD de Vref, AN0 
	ADCON0 = 0x81;
}                       
               
unsigned int ADC_Read(unsigned char channel){
  GO_nDONE = 1; //Inicializa a convers�o A/D
  while(GO_nDONE); //espera a convers�o ser completada
  return ((ADRESH<<8)+ADRESL); //Retorna os resultados
} 