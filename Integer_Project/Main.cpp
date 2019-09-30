// Main.cpp
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador.
// Description: Main program.

#include<iostream>
#include <cstdlib>
#include"Integer.h"

int main(int argc, char* argv[]) {
	int _int = 2;
	long int _long = 234566123;
	Integer *x = new Integer(_int);
	Integer *y = new Integer(_long);
	Integer *factorial_test = new Integer(1000);
	Integer* fibonacci_test = new Integer(1000);


	try {
		std::cout << "	LE SIRVE MOOOOOOOOOP_?????????????? \n\n\n";
		std::cout << "Testing Factorial of 1000: " << std::endl << std::endl;
		factorial_test = Integer::Factorial(factorial_test);
		std::cout << factorial_test->toString() << std::endl <<std::endl;
		std::cout << "Wasted memory of the structure: ";
		std::cout << factorial_test->WastedMemory() <<" bytes" << std::endl;
		std::cout << std::endl;
		std::cout << "Testing Fibonacci with 1000: " << std::endl << std::endl;
		fibonacci_test = Integer::Fibonacci(fibonacci_test);
		std::cout << fibonacci_test->toString() << std::endl << std::endl;
		std::cout << "Wasted memory of the structure: ";
		std::cout << fibonacci_test->WastedMemory() << " bytes" << std::endl;
		std::cout << std::endl;
		std::cout << "Testing wasted memory in some integers" << std::endl << std::endl;
		std::cout << "Testing: " << std::endl;
		std::cout << x->toString() << std::endl << std::endl;
		std::cout << "Wasted memory of the structure: ";
		std::cout << x->WastedMemory() << " bytes" << std::endl << std::endl;
		std::cout << "Testing: " << std::endl;
		std::cout << y->toString() << std::endl << std::endl;
		std::cout << "Wasted memory of the structure: ";
		std::cout << y->WastedMemory() << " bytes" << std::endl << std::endl;

	}

	catch (MyExceptions& exc) {
		std::cout << "Error: " << exc.what() << std::endl;
		system("pause");
	}

	catch (...) {
		std::cout << "Error: " << "Unknown Error" << std::endl;
		system("pause");
	}
	

	delete factorial_test;
	delete fibonacci_test;
	delete y;
	delete x;
	system("pause");
	return 0;
}