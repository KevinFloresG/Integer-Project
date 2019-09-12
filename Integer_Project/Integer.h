// Integer.h
//
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
//#define ZERO 0; supuestamente no es recomendado en C++
//#define ONE 1; supuestamente no es recomendado en C++

#include<iostream>

const short int ZERO = 0;
const short int ONE = 1;

struct Nodo{
	unsigned short int* v[5];
	struct Nodo* next;
};

class Integer {
private:
	bool sign; // true->positive || false->negative
	struct Nodo* first;
public:

};

#endif // !INTEGER_H



