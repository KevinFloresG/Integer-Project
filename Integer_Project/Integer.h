// Integer.h
//
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
#define ZERO 0 //supuestamente no es recomendado en C++, pero así las define el profe...
#define ONE 1 
#define DIGITS_CANT 10000 //Por esto de divide o de modula un número para quitarle 4 dígitos

#include<iostream>

//static const short int ZERO = 0;
//static const short int ONE = 1;

struct Nodo{
	short int v[5];
	struct Nodo* next;
};

class Integer {
private:
	bool sign; // true->positive || false->negative
	struct Nodo* first;
public:
	Integer();			// Default Constructor
	Integer(int);		// Constructor Overload (int)
};

#endif // !INTEGER_H



