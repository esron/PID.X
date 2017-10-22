#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

char UART_Init(const long int);
void UART_Write(char);
char UART_Read();
void UART_Write_Text(char);


#endif	/* XC_HEADER_TEMPLATE_H */

