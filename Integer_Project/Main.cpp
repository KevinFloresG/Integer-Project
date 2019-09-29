// Main.cpp
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador.
// Description: Main program.

#include<iostream>
#include <cstdlib>
#include"Integer.h"

int main(int argc, char* argv[]) {
	int _int = 2;
	long int _long = 234566123;
	long int _long2 = 129749302;
	std::string num_test = "1000";
	std::string num_test_2 = "1714546546546545454544548544544545";
	Integer *x = new Integer(_long);
	/*
	x->first->next = new Nodo;
	x->first->next->next = nullptr;
	x->first->next->v[0] = 123;
	x->first->next->v[1] = 783;
	x->first->next->v[2] = 9863;
	x->first->next->v[3] = 0;
	x->first->next->v[4] = 23;
	// x = 23 0000 9863 0783 0123 0000 0000 0002 3456 6123
	std::cout << num_test << std::endl;
	std::cout << "Testing parse" << std::endl;
	std::cout << Integer::Parse(num_test)->toString() << std::endl;
	std::cout << "Testing multiplication" << std::endl;
	Integer* mul_test = new Integer();
	
	Integer* n1_test = Integer::Parse(num_test);
	Integer* n2_test = Integer::Parse(num_test_2);
	*mul_test = *n1_test * *n2_test;

	std::cout << mul_test->toString() << std::endl;

	std::cout << "Factorial" << std::endl;
	std::cout << Integer::Factorial(Integer::Parse(num_test))->toString() << std::endl;

	// Salida: 23000098630783012300000000000234566123
	// 23 0000 9863 0783 0123 0000 0000 0002 3456 6123

	*/
	Integer *y = new Integer(_long2);/*
	y->first->next = new Nodo;
	y->first->next->next = nullptr;
	y->first->next->v[0] = 777;
	y->first->next->v[1] = 0;
	y->first->next->v[2] = 8644;
	y->first->next->v[3] = 1234;
	y->first->next->v[4] = 10;
	// y = 10 1234 8644 0000 0777 0000 0000 0001 2974 9302

	// Salida: 10123486440000077700000000000129749302
	// 10 1234 8644 0000 0777 0000 0000 0001 2974 9302

	Integer* z = new Integer(_long);
	z->first->next = new Nodo;
	z->first->next->next = nullptr;
	z->first->next->v[0] = 123;
	z->first->next->v[1] = 783;
	z->first->next->v[2] = 9863;
	z->first->next->v[3] = 0;
	z->first->next->v[4] = 23;
	*/
	Integer *x_plus_y = new Integer(1000);
	Integer* Fibonacci = new Integer(1000);
	/*Fibonacci->setSign(false);*/
//	*x_plus_y = *x + *y;

	//*x_plus_y = *x_plus_y * *x_plus_y;
	try {
		std::cout << "Testing Factorial of 1000: " << std::endl;
		std::cout << Integer::Factorial(x_plus_y)->toString() << std::endl;
		std::cout << Integer::Factorial(x_plus_y)->WastedMemory() << std::endl;
		std::cout << std::endl;
		std::cout << "Testing Fibonacci with 1000: " << std::endl;
		std::cout << Integer::Fibonacci(Fibonacci)->toString() << std::endl;
	}

	catch (MyExceptions& exc) {
		std::cout << "Error: " << exc.what() << std::endl;
		system("pause");
	}

	catch (...) {
		std::cout << "Error: " << "Unknown Error" << std::endl;
		system("pause");
	}
	

	delete x_plus_y;
	delete Fibonacci;

	system("pause");
	return 0;
}