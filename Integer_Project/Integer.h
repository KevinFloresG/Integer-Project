// Integer.h
//
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
#define ZERO 0 //supuestamente no es recomendado en C++, pero así las define el profe...
#define ONE 1 
#define DIGITS_CANT 10000 //Por esto de divide o de modula un número para quitarle 4 dígitos
#define V_TAM 5

#include<iostream>

//static const short int ZERO = 0;
//static const short int ONE = 1;

struct Nodo{
	short int v[V_TAM];
	struct Nodo* next;
};

class Integer {
private:
	bool sign; // true->positive || false->negative

	void nodos_copy(Nodo*, const Nodo*);

public:
	struct Nodo* first;
	Integer();			// Default Constructor
	Integer(int);		// Constructor Overload (int)
	Integer(long);		// Constructor Overload (long)
	Integer& sum_2(Integer&, Integer&);
};

#endif // !INTEGER_H



