// Main.cpp
//
// Description: Main program.

#include<iostream>
#include <cstdlib>
#include"Integer.h"

int main(int argc, char* argv[]) {
	int _int = 2;
	long int _long = 234566123;
	long int _long2 = 129749302;

	Integer* x = new Integer(_long);
	Integer* y = new Integer(_long2);
	Integer* x_plus_y = &(x->sum_2(*x, *y));

	// Javier: Pruebas del toString();

	std::cout << "Valor 1: " << std::endl;
	std::cout << x->toString();
	std::cout << std::endl;

	std::cout << "Valor 2: " << std::endl;
	std::cout << y->toString();
	std::cout << std::endl;


	// Javier: Prueba del toString() y sum_2();
	std::cout << "Suma de valor 1 y valor 2: " << std::endl;
	std::cout << x_plus_y->toString();
	std::cout << std::endl;



	system("pause");
	return 0;
}