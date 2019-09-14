// Integer.h
//
// Description: Class that can perform arithmetic operations with very large numbers.

#ifndef INTEGER_H
#define INTEGER_H
#define ZERO 0 //supuestamente no es recomendado en C++, pero as� las define el profe...
#define ONE 1 
#define DIGITS_CANT 10000 //Por esto de divide o de modula un n�mero para quitarle 4 d�gitos
#define V_TAM 5

#include <string>
using std::string; // mae yo creo que al tigre no le va a cuadrar esto XD 
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
	Integer& sum(Integer&, const Integer&); // Sum of two Integer's
	Integer& substract(Integer&, const Integer&);  // Substraction of tow Integer's

public:

	struct Nodo* first;
	Integer();			// Default Constructor
	Integer(int);		// Constructor Overload (int)
	Integer(long);		// Constructor Overload (long)

	Integer& operator+(const Integer&);
	Integer& operator-(const Integer&);
	Integer& operator=(const Integer&);

	//friend std::ostream& operator << (std::ostream&, const Integer&); // << Operator Overload
	std::string toString(); // Method to convert Integer into a string to print it
};

#endif // !INTEGER_H
