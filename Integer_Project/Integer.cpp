// Integer.cpp
//
// Description: Implementation of Integer.h.

#include"Integer.h"

Integer::Integer() : sign(true), first(nullptr) {}

Integer::Integer(int n) : sign(true) {
	if (n < ZERO) { 
		sign = false; n *= -1; 
	}
	first = new Nodo();
	first->next = nullptr;
	Nodo* aux = first; // se auto destruye al salir del metodo no? (la memoria del puntero se libera)

	/*No esto seguro si se destruye o no, cualquier cosa poniendo un delete aux al final no deberíamos tener problemas
	o sí ? (Siempre y cuado el ptr no este viendo el nodo al final, sino nullptr)
	*/

	for (int x = 0; n; x++) {
		if (x == 5) {
			aux->next = new Nodo();
			aux = aux->next;
			aux->next = nullptr;
			x = 0;
		}
		else {
			aux->v[x] = (short int)(n % DIGITS_CANT); //el cast se hace aquí para usar 2 bytes.
			n /= DIGITS_CANT;
		}
	}
}

Integer::Integer(long n): sign(true) {
	if (n < ZERO) {
		sign = false; n *= -1;
	}
	first = new Nodo();
	first->next = nullptr;
	Nodo* aux = first;
	for (int x = 0; n; x++) {
		if (x == 5) {
			aux->next = new Nodo();
			aux = aux->next;
			aux->next = nullptr;
			x = 0;
		}
		else {
			aux->v[x] = (short int)(n % DIGITS_CANT); //el cast se hace aquí para usar 2 bytes.
			n /= DIGITS_CANT;
		}
	}
}
