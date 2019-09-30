// Integer.h
// Authors: Kevin Flores, Philippe Gairaud , Javier Amador.
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
#define ZERO 0 
#define ONE 1 
#define DIGITS_CANT 10000 
#define V_TAM 9
#define NUM_TAM 4
#define NODE_SIZE 18

#include <string>
#include<iostream>
#include "MyExceptions.h"


struct Nodo{
	short int v[V_TAM];
	struct Nodo* next = nullptr;
};

class Integer {
private:

	bool sign; // true->positive || false->negative
	struct Nodo* first;
	void Empty();
	void NodosCopy(Nodo*, const Nodo*); // Copy the following nodes of a given node
	static void Verify(Integer&); // Verify that there are not only zeros in the last node
	static Integer& MultiplyForInt(const Integer&, short int, int); // Multiply an Integer with a normal int and add zeros
	Integer& Addition(Integer&, const Integer&); // Addition of two Integers
	Integer& Substract(Integer&, const Integer&);  // Substraction of two Integers
	Integer& Multiplication(Integer&, const Integer&); // Multiplication of two Integers

public:

	Integer();			// Default Constructor
	Integer(int);		// Constructor Overload (int)
	Integer(long);		// Constructor Overload (long)
	~Integer();     
	void setSign(bool);
	bool getSign()const;
	int GetNodesCant(); //Return the number of nodes of the integer
	int WastedMemory(); //Return wasted memory
	Nodo* GetLastNode(); //Return the last node of the integer
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
	friend std::ostream& operator << (std::ostream&, const Integer&); // << Operator Overload
	std::string toString()const; // Method to convert Integer into a string to print it
};

#endif // !INTEGER_H
