
// PIC16F917 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT/T1OSO pin, I/O function on RA7/OSC1/CLKIN/T1OSI)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdlib.h>

#include "lcd.h"
#include "lib.h"

#define _XTAL_FREQ 8000000


char UART_Init(const long int baudrate) {
    unsigned int x;

    x = (_XTAL_FREQ - baudrate * 16) / (baudrate * 16); //SPBRG for High Baud Rate
    BRGH = 1; //Setting High Baud Rate

    SPBRG = x; //Writing SPBRG Register
    SYNC = 0; //Setting Asynchronous Mode, ie UART
    SPEN = 1; //Enables Serial Port
    TRISC7 = 1; //As Prescribed in Datasheet
    TRISC6 = 1; //As Prescribed in Datasheet
    CREN = 1; //Enables Continuous Reception
    TXEN = 1; //Enables Transmission
    return 1; //Returns 1 to indicate Successful Completion
}

void UART_Write(char data) {
    while (!TRMT);
    TXREG = data;
}

char UART_Data_Ready() {
    return RCIF;
}

char UART_Read() {
    while (!RCIF);
    return RCREG;
}

void UART_Read_Text(char *Output, unsigned int length) {
    unsigned int i;
    for (int i = 0; i < length; i++)
        Output[i] = UART_Read();
}

void UART_Write_Text(char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++)
        UART_Write(text[i]);
}

void main(void) {
    MAPKEY D1, D2, D3;
    float ki, kd, kp;
    int desejado, error, P, I, D, PID_v;
    unsigned char duty_cycle =30; // Velocidade requerida
    unsigned int timer1 = 0;
    char str [] = "9999999999999999";
    
    
    LCD_init();	
    LCD_mapping(&D1,&D2,&D3);
    UART_Init(9600);
            
    // Inicializando as entradas e saídas
    TRISD   = 0x00;
    TRISA  |= 0x01;
    OSCCON  = 0x70;
    PR2     = 0x3F;
    CMCON0  = 0x07;
    INTCON  = 0;
    CCPR2L  = 0;
    CCP2CON = 0x0C;
    T2CON   = 0x04;
    
    // RC5 como entrada
    TRISC |= (1 << 5);

    // Configurando timer 1
    T1CON |= (1 << TMR1ON) | (1 << TMR1CS) | (1 << T1SYNC);
    
    PORTD |= (1 << RD7);
    
    TMR1H = 0;
    TMR1L = 0;

    CCPR2L = 0; // Velocidade inicial
    
    
    kp = 0.001;
    ki = 1;
    kd = 1;
    
    P = 0;
    I = 0;
    D = 0;
    PID_v = 0;
    
    desejado = 30;
    CCPR2L = 0;
    
    while(1) {        
        timer1 = (TMR1H << 8) + TMR1L;
        //timer1 *= 30; 
        displayNumber(timer1, &D1, &D2, &D3);
        
        error = desejado - timer1;
        if (error) {
            P = error;
            I = I + error;
            D = 0;

            PID_v = kp * P + ki * I + kd*D;

            CCPR2L = PID_v;
        }
        utoa(str, CCPR2L, 10);
        UART_Write_Text(str);
        UART_Write('\n');
        
        utoa(str, timer1, 10);
        UART_Write_Text(str);
        UART_Write('\n');
      
        
        TMR1H = 0;
        TMR1L = 0;
        // A cada 1 segundo
        __delay_ms(600);
    }
    
    return;
}