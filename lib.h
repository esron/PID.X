#ifndef LIB_H
#define LIB_H

//n�o lembro pra que serve 
#ifndef _XTAL_FREQ
	#define _XTAL_FREQ 8000000     //4MHz 
#endif

//se��o de defini��es
#define bitset(var, numbit) ((var) |= (1UL) << (numbit))
#define bitclr(var, numbit) ((var) &= ~((1UL) << (numbit)))
#define reg_clr(var) ((var) &= 0x00)

#endif
