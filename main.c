
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
#include "uart.h"

// Global PID variables
float ki, kd, kp, pid_val;
int last_error = 0;
int P, I, D;

void PID_init() {
    
    // Clearing values
    P = 0;
    I = 0;
    D = 0;
    
    // Empirical values for Kp, Ki & Kd;
    kp = 1.5;
    ki = 0.5;
    kd = 0.1;
}

int PID(int setpoint, int read) {
    int error;
    error = setpoint - read; // Error
    
    if (error) {
        P = error; // Proportional term
        I = I + error; // Integral term
        D = error - last_error; // Derivative term
        last_error = error;
        pid_val = kp * P + ki * I + kd * D;
        return CCPR2L += pid_val; // PID value
    }
    else
        return CCPR2L;
}

void main(void) {
    MAPKEY D1, D2, D3;
    
    // Setpoint value chosen to be max/2
    int setpoint = 25;
    unsigned int timer1;
    
    // Auxiliar string to use on UART
    char str [33];
    
    // Initialization procedures
    LCD_init();	
    LCD_mapping(&D1,&D2,&D3);
    UART_Init(9600);
    PID_init();
            
    
    TRISD   = 0x00; // Set PORTD as outpput
    OSCCON  = 0x70; // 8MHTZ CL
    PR2     = 0x3F; // PWM period
    INTCON  = 0; // Sisable interurps
    CCPR2L  = 0; // Clearing duty cycle
    CCP2CON = 0x0C; // CCP2 as PWM
    T2CON   = 0x04; // Timer 2 on
    
    // RC5 as input
    TRISC |= (1 << RC5);

    // Timer 1 configuration as synchronous counter
    // Prescaler = 1
    T1CON |= (1 << TMR1ON) | (1 << TMR1CS) | (1 << T1SYNC);
    
    PORTD |= (1 << RD7); // Turning on the motor
    
    TMR1H = 0; // Clearing timer1
    TMR1L = 0;
    
    while(1) {

        // Aquiring the encoder count
        timer1 = (TMR1H << 8) + TMR1L;
        
        // Dysplay the count on the LCD
        displayNumber(timer1, &D1, &D2, &D3);
        
        // Calculates the PID and update the duty cycle
        CCPR2L = PID(setpoint, timer1);
        
        // Sends the count read via UART
        utoa(str, timer1, 10);
        UART_Write_Text(str);
        UART_Write('\n');
      
        
        // Clearing timer1 to reset counts
        TMR1H = 0;
        TMR1L = 0;
        
        // A small delay to give the encoder time to count
        __delay_ms(600);
    }
    
    return;
}