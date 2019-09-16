// Integer.h
//
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
#define ZERO 0 //supuestamente no es recomendado en C++, pero así las define el profe...
#define ONE 1 
#define DIGITS_CANT 10000 //Por esto de divide o de modula un número para quitarle 4 dígitos
#define V_TAM 5
#define NUM_TAM 4

#include <string>
// mae yo creo que al tigre no le va a cuadrar esto XD 
/*Javier: Ah mae se me olvidó quitarle eso del using std::string, lo había puesto cuando pensaba que no me estaba sirviendo
los metodos del string, sigue tirandome como que estuviera mal pero si compila y ejecuta eso, debe ser porque
estamos haciendo las varas en dos versiones de visual o algo así*/
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

	void vaciar();
	void nodos_copy(Nodo*, const Nodo*);
	Integer& sum(Integer&, const Integer&); // Sum of two Integer's
	Integer& substract(Integer&, const Integer&);  // Substraction of tow Integer's
	Integer& multiplication(Integer&, const Integer&);

public:

	struct Nodo* first;
	Integer();			// Default Constructor
	Integer(int);		// Constructor Overload (int)
	Integer(long);		// Constructor Overload (long)
	static Integer* Parse(std::string);
	static Integer* Factorial(Integer*);
	Integer& operator+(const Integer&);
	Integer& operator*(const Integer&);
	void operator +=(const Integer&);
	Integer& operator-(const Integer&);
	void operator-=(const Integer&);
	Integer& operator=(const Integer&);
	bool operator ==(const Integer&);
	bool operator !=(const Integer&);
	bool operator <(const Integer&);
	bool operator >(const Integer&);
	bool operator <=(const Integer&);
	bool operator >=(const Integer&);
	friend Integer& operator++(const Integer&);
	friend std::ostream& operator << (std::ostream&, const Integer&); // << Operator Overload
	std::string toString()const; // Method to convert Integer into a string to print it
};

#endif // !INTEGER_H
