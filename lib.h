#ifndef LIB_H
#define LIB_H

//não lembro pra que serve 
#ifndef _XTAL_FREQ
	#define _XTAL_FREQ 8000000     //4MHz 
#endif

//seção de definições
#define bitset(var, numbit) ((var) |= (1UL) << (numbit))
#define bitclr(var, numbit) ((var) &= ~((1UL) << (numbit)))
#define reg_clr(var) ((var) &= 0x00)

#endif
