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
	std::string num_test = "123456567856845235234123123129837293857234985618286537163571263512";
	Integer *x = new Integer(_long);
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
	std::cout << Integer::parse(num_test)->toString() << std::endl;


	// Salida: 23000098630783012300000000000234566123
	// 23 0000 9863 0783 0123 0000 0000 0002 3456 6123


	Integer *y = new Integer(_long2);
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

	Integer *x_plus_y = new Integer();
	*x_plus_y = *x + *y;
	// x_plus_y = next = 33 1235 8507 0783 0900 0000 0000 0003 6431 5425 


	// Salida: 33123585070783090000000000000364315425
	// 33 1235 8507 0783 0900 0000 0000 0003 6431 5425

	Integer *x_less_y = new Integer();
	*x_less_y = *x - *y;
	// x_less_y = next = 12 8766 1219 0782 9346 0000 0000 0001 0481 6821

	// Salida: 12876612190782934600000000000104816821
	// 12 8766 1219 0782 9346 0000 0000 0001 0481 6821

	// Javier: Pruebas del toString()

	std::cout << "Valor 1: " << std::endl;
	std::cout << *x; // Prueba sobrecarga de <<
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Valor 2: " << std::endl;
	std::cout << y->toString();
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Valor 3: " << std::endl;
	std::cout << z->toString();
	std::cout << std::endl;
	std::cout << std::endl;


	//// Javier: Prueba del toString() y suma
	//std::cout << "Suma de valor 1 y valor 2: " << std::endl;
	//std::cout << x_plus_y->toString();
	//std::cout << std::endl;
	//std::cout << std::endl;

	//// Javier: Prueba del toString() y resta
	//std::cout << "Resta de valor 1 y valor 2: " << std::endl;
	//std::cout << x_less_y->toString();
	//std::cout << std::endl;
	//std::cout << std::endl;

	std::cout << "Son iguales 1 y 2?" << std::endl << std::endl;
	if(*x==*y)
		std::cout<<"SI SON IGUALES"<< std::endl << std::endl;
	else
		std::cout << "NO SON IGUALES" << std::endl << std::endl;

	std::cout << "Son iguales 2 y 3?" << std::endl << std::endl;
	if (*y == *z)
		std::cout << "SI SON IGUALES" << std::endl << std::endl;
	else
		std::cout << "NO SON IGUALES" << std::endl << std::endl;

	std::cout << "Son iguales 1 y 3?" << std::endl << std::endl;
	if (*x == *z)
		std::cout << "SI SON IGUALES" << std::endl << std::endl;
	else
		std::cout << "NO SON IGUALES" << std::endl << std::endl;

	delete x;
	delete y;
	delete x_plus_y;
	delete x_less_y;

	system("pause");
	return 0;
}