// Integer.h
// Authors: Kevin Flores, Philippe Gairaud , Javier Amador.
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
#define ZERO 0 //supuestamente no es recomendado en C++, pero así las define el profe...
#define ONE 1 
#define DIGITS_CANT 10000 //Por esto de divide o de modula un número para quitarle 4 dígitos
#define V_TAM 9
#define NUM_TAM 4

#include <string>
#include<iostream>
#include "Vector.h"

//static const short int ZERO = 0;
//static const short int ONE = 1;

struct Nodo{
	short int v[V_TAM];
	struct Nodo* next;
};

class Integer {
private:

	bool sign; // true->positive || false->negative
	struct Nodo* first;
	void empty();
	void nodos_copy(Nodo*, const Nodo*);
	 //Insert number in a beginning of a Integer.
	static void verify(Integer&);
	Integer& addition(Integer&, const Integer&); // Addition of two Integers
	Integer& substract(Integer&, const Integer&);  // Substraction of two Integers
	Integer& multiplication(Integer&, const Integer&); // Multiplication of two Integers

public:
	static Integer& multiply_for_int(const Integer&, short int, int);

	Integer();			// Default Constructor
	Integer(int);		// Constructor Overload (int)
	Integer(long);		// Constructor Overload (long)
	static Integer* Parse(std::string); // Method that turns a string into an instance of Integer
	static Integer* Factorial(Integer*); // Method that allows to get the factorial or large numbers
	static Integer* Fibonacci(Integer*); // Method that returns the n-th element of the Fibonacci succesion
	Integer& operator+(const Integer&); // Operator + Overload
	Integer& operator*(const Integer&); // Operator * Overload
	void operator +=(const Integer&); // Operator += Overload
	Integer& operator-(const Integer&); // Operator - Overload
	void operator-=(const Integer&); // Operator -= Overload
	Integer& operator=(const Integer&); // Operator = Overload
	bool operator ==(const Integer&); // Operator == Overload
	bool operator !=(const Integer&); // Operator != Overload
	bool operator <(const Integer&); // Operator < Overload
	bool operator >(const Integer&); // Operator > Overload
	bool operator <=(const Integer&); // Operator <= Overload
	bool operator >=(const Integer&); // Operator >= Overload
	friend Integer& operator++(const Integer&); //Pending, unnecesary
	friend std::ostream& operator << (std::ostream&, const Integer&); // << Operator Overload
	std::string toString()const; // Method to convert Integer into a string to print it
};

#endif // !INTEGER_H
