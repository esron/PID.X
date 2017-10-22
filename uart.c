#include <xc.h>

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

char UART_Read() {
    while (!RCIF);
    return RCREG;
}

void UART_Write_Text(char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++)
        UART_Write(text[i]);
}