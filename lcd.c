#include <htc.h>
#include <pic.h>
#include "lcd.h"
#include "lib.h"

//================================================================//
                        /*  Functions  */
                        
void LCD_mapping(MAPKEY* D1,MAPKEY* D2, MAPKEY* D3){
	//digito 1
	D1->sa = &LCDDATA2; D1->bits[0] =6 ; 
	D1->sb = &LCDDATA2; D1->bits[1] =7 ; 
	D1->sc = &LCDDATA8; D1->bits[2] =7 ; 
	D1->sd = &LCDDATA11; D1->bits[3] =6 ; 
	D1->se = &LCDDATA8; D1->bits[4] =6 ; 
	D1->sf = &LCDDATA5; D1->bits[5] =6 ; 
	D1->sg = &LCDDATA5; D1->bits[6] =7 ; 
		
	//digito 2
	D2->sa = &LCDDATA0; D2->bits[0] =6 ;
	D2->sb = &LCDDATA2; D2->bits[1] =5 ;
	D2->sc = &LCDDATA8; D2->bits[2] =5 ;
	D2->sd = &LCDDATA9; D2->bits[3] =6 ;
	D2->se = &LCDDATA6; D2->bits[4] =6 ;
	D2->sf = &LCDDATA3; D2->bits[5] =6 ;
	D2->sg = &LCDDATA5; D2->bits[6] =5 ;
	
	//digito 3
	D3->sa = &LCDDATA0; D3->bits[0] =3 ;
	D3->sb = &LCDDATA1; D3->bits[1] =3 ;
	D3->sc = &LCDDATA7; D3->bits[2] =3 ;
	D3->sd = &LCDDATA9; D3->bits[3] =3 ;
	D3->se = &LCDDATA6; D3->bits[4] =3 ;
	D3->sf = &LCDDATA3; D3->bits[5] =3 ;
	D3->sg = &LCDDATA4; D3->bits[6] =3 ;  
}

void LCD_init(){
   
	LCDSE0 = 0x4F;
	LCDSE1 = 0x08;
	LCDSE2 = 0xE1;

	/* apaga LCDDATA*/
	reg_clr(LCDDATA0);
	reg_clr(LCDDATA1);
	reg_clr(LCDDATA2);
	reg_clr(LCDDATA3);
	reg_clr(LCDDATA4);
	reg_clr(LCDDATA5);
	reg_clr(LCDDATA6);
	reg_clr(LCDDATA7);
	reg_clr(LCDDATA8);
	reg_clr(LCDDATA9);
	reg_clr(LCDDATA10);
	reg_clr(LCDDATA11);
	
	/* WAVEFORM TYPE A, LCD MODULE IS ACTIVE PRESCALER IS 1:1,  
	BIAS IS 0 (CAN BE STATIC OR 1/3) */
	LCDPS = 0x20;
	
	/* LDC MODULE IS ON, DRIVER MODULE IS ENABLED DURING SLEEP
	NO WRITE FAIL ERROR, VLDC PINS ARE ENABLED, MULTIPLEX 1/4 BIAS 1/3 */
	LCDCON = 0x93;
			
}

//mapea cada digito para a respectiva casa decimal
void displayNumber(int num,MAPKEY* D1,MAPKEY* D2, MAPKEY* D3){
        //mostra digito1
		displayDigit(num/100, D3 );
		num %=100;
		//mostra digito2
		displayDigit(num/10, D2);
		num %=10;
        bitset(LCDDATA10,3);  // Ponto decimal 5.13
		//mostra digito3
		displayDigit(num, D1);
        
}

//desenha caracter no display
void displayDigit(int digito, MAPKEY* D1 ){            
	switch(digito){
		case 0:
			bitset(*D1->sa, D1->bits[0]);
			bitset(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]); 
			bitset(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitclr(*D1->sg, D1->bits[6]); 
		break;
		case 1:
			bitclr(*D1->sa, D1->bits[0]); 
			bitset(*D1->sb, D1->bits[1]);  
			bitset(*D1->sc, D1->bits[2]);
			bitclr(*D1->sd, D1->bits[3]);
			bitclr(*D1->se, D1->bits[4]);
			bitclr(*D1->sf, D1->bits[5]);
			bitclr(*D1->sg, D1->bits[6]);
		break;
		case 2:
			bitset(*D1->sa, D1->bits[0]);
		    bitset(*D1->sb, D1->bits[1]);
			bitclr(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitset(*D1->se, D1->bits[4]);
			bitclr(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);	
		break;
		case 3:
			bitset(*D1->sa, D1->bits[0]);
		    bitset(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitclr(*D1->se, D1->bits[4]);
			bitclr(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);	
		break;
		case 4:
			bitclr(*D1->sa, D1->bits[0]);
		    bitset(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitclr(*D1->sd, D1->bits[3]);
			bitclr(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);	
		break;
		case 5:
			bitset(*D1->sa, D1->bits[0]);
    		bitclr(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitclr(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);
		break;
		case 6:
			bitset(*D1->sa, D1->bits[0]);
		    bitclr(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitset(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);	
		break;
		case 7:
			bitset(*D1->sa, D1->bits[0]);
		    bitset(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitclr(*D1->sd, D1->bits[3]);
			bitclr(*D1->se, D1->bits[4]);
			bitclr(*D1->sf, D1->bits[5]);
			bitclr(*D1->sg, D1->bits[6]);	
		break;
		case 8:
			bitset(*D1->sa, D1->bits[0]);
		    bitset(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitset(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);	
		break;
		case 9:
			bitset(*D1->sa, D1->bits[0]);
		    bitset(*D1->sb, D1->bits[1]);
			bitset(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitclr(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitset(*D1->sg, D1->bits[6]);	
		break;
		case 'C':
			bitset(*D1->sa, D1->bits[0]);
		    bitclr(*D1->sb, D1->bits[1]);
			bitclr(*D1->sc, D1->bits[2]);
			bitset(*D1->sd, D1->bits[3]);
			bitset(*D1->se, D1->bits[4]);
			bitset(*D1->sf, D1->bits[5]);
			bitclr(*D1->sg, D1->bits[6]);	
		break;
   }
}