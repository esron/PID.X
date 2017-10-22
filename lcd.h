#ifndef LCD_H
#define LCD_H

/* The following figure shows the letter designation given to the
; segments in a 7-segment display
;
;    ----a----
;   |         |    
;   f         b
;   |         |
;    ----g----
;   |         |
;   e         c
;   |         |
;    ----d----
*/
typedef struct{
	int *sa;
	int *sb;
	int *sc;
	int *sd;
	int *se;
	int *sf;
	int *sg;
	int bits[7];
}MAPKEY;

//================================================================//
                      /*  Prototypes  */

void LCD_mapping(MAPKEY* D1,MAPKEY* D2,MAPKEY* D3 );
void LCD_init();
void LCD_clear();
void displayNumber(int,MAPKEY*,MAPKEY*,MAPKEY*);
void displayDigit(int, MAPKEY*);


#endif