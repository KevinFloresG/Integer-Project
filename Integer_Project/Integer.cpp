// Integer.cpp
//
// Description: Implementation of Integer.h.

#include"Integer.h"
#include <sstream>


Integer::Integer() : sign(true), first(nullptr) {}

Integer::Integer(int n) : sign(true) {
	if (n < ZERO) { 
		sign = false; n *= -1; 
	}
	first = new Nodo();
	first->next = nullptr;
	Nodo* aux = first; // se auto destruye al salir del metodo no? (la memoria del puntero se libera)

	/*Javier: No esto seguro si se destruye o no, cualquier cosa poniendo un delete aux al final no deberíamos tener problemas
	o sí ? (Siempre y cuado el ptr no este viendo el nodo al final, sino nullptr)

	Kevin: es que si le ponemos delete va a borrar el nodo. 

	Javier: Y si al final le asignamos null_ptr y luego si delete ? O no tiene sentido ?


	*/

	for (int x = 0; n; x++) {
		if (x == V_TAM) {
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
		if (x == V_TAM) {
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

void Integer::nodos_copy(Nodo* actual, const Nodo* n) {

	for (int x = 0; n; x++) { 
		if (x == V_TAM) { 
			n = n->next; x = -1;
			if (n) {
				actual->next = new Nodo();
				actual = actual->next;
				actual->next = nullptr;
			}
		}
		else { actual->v[x] += n->v[x]; }
	}
}

Integer& Integer::sum_2(Integer& n_1, Integer& n_2) {

	// hay que poner una excepcion supongo. En caso de que reciba Integers con first en null.
	// if (!n_1.first || !n_2.first) { throw 1; } 

	// Variables auxilires
	int sum; bool carry = false;
	Integer* result = new Integer();
	Nodo *aux_1 = n_1.first, *aux_2 = n_2.first, *aux_3 = new Nodo();
	result->first = aux_3;

	for (int x = 0; aux_1 || aux_2; x++) {

		sum = aux_1->v[x] + aux_2->v[x];

		if (sum >= DIGITS_CANT) { 
			carry = true; 
			aux_3->v[x] += sum % DIGITS_CANT;
		}
		else {
			carry = false;
			aux_3->v[x] += sum;
		}
		
		if (x == V_TAM - ONE) {
			// Aquí se avanza el siguiente nodo, se verifica si hay que llevar carry
			// o si alguno de los integers ya terminó y la otra no, en ese caso solo 
			// se copia el resto de nodos del Integer que no ha terminado.
			aux_2 = aux_2->next; aux_1 = aux_1->next; 
			x = -1;
			if (carry || aux_1 || aux_2) {
				aux_3->next = new Nodo();
				aux_3 = aux_3->next;
				aux_3->v[ZERO] = carry;
				if (aux_1 && !aux_2) { nodos_copy(aux_3, aux_1); return *result; }
				if (aux_2 && !aux_1) { nodos_copy(aux_3, aux_2); return *result; }
			}
		}
		else {
			aux_3->v[x + ONE] = carry;
		}
	}

	return *result;
}


/*Javier: Hay varias cosas que se pueden cambiar para que sea mejor (ya sea que se vea más ordenado o que sea más eficiente), 
pero a sirve para probar y di cumple lo que se espera de esto*/


//Returns string of the digits of Integer
std::string Integer::toString() {

	std::stringstream stringInteger; // Stringstream in which all the digits from Integer are stored
	std::stringstream actualStringInteger; // Stringstream in which there are no extra zeros (i.e. 00002 would be saved as 2 in this stringstream)
	std::string noExtraZeros; // Used to create actualStringInteger

	Nodo* aux = first;
	short int digits=0;


	
	while (aux) {

		for (int i = V_TAM-1; i >= 0; i--) {

			digits = aux->v[i];

			if (digits < 10) {
				stringInteger << "000" << digits;
				continue;
			}

			if (digits < 100) {
				stringInteger << "00" << digits;
				continue;
			}

			if (first->v[i] < 1000) {
				stringInteger << "0" << digits;
				continue;
			}

			stringInteger << digits;

		
		}

		aux = aux->next;
	}

	// The following for is to create a stringstream where there are no extra zeros

	noExtraZeros = stringInteger.str(); 
	bool startPrintingActualNumber = false; // To know when to start getting numbers

	for (int i = 0; i < noExtraZeros.length(); i++) {

		if (noExtraZeros[i] != '0') // Is true when the number starts
			startPrintingActualNumber = true;

		if (startPrintingActualNumber)
			actualStringInteger  << noExtraZeros[i];
	}

	actualStringInteger << '\n';

	return actualStringInteger.str();

}