#ifndef ADC_H
#define ADC_H

//clock do conversor A/D
#define CLOCK_AD 0x70 //clock RC

//prototipos
void ADC_Init();
unsigned int ADC_Read(unsigned char channel);

#endif