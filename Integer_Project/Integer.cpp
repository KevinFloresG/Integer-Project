// Integer.cpp
//
// Description: Implementation of Integer.h.

#include"Integer.h"
#include <sstream>
#include <vector>


Integer::Integer() : sign(true), first(new Nodo()) {}

Integer::Integer(int n) : sign(true) {
	if (n < ZERO) { 
		sign = false; n *= -1; 
	}
	first = new Nodo();
	first->next = nullptr;
	Nodo* aux = first; // se auto destruye al salir del metodo no? (la memoria del puntero se libera)

	/*Javier: No esto seguro si se destruye o no, cualquier cosa poniendo un delete aux al final no deber�amos tener problemas
	o s� ? (Siempre y cuado el ptr no este viendo el nodo al final, sino nullptr)

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
			aux->v[x] = (short int)(n % DIGITS_CANT); //el cast se hace aqu� para usar 2 bytes.
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
			aux->v[x] = (short int)(n % DIGITS_CANT); //el cast se hace aqu� para usar 2 bytes.
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

Integer& Integer::sum(Integer& n_1, const Integer& n_2) {

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
			// Aqu� se avanza el siguiente nodo, se verifica si hay que llevar carry
			// o si alguno de los integers ya termin� y la otra no, en ese caso solo 
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
	//aux_3->next = nullptr;
	return *result;
}

Integer& Integer::substract(Integer& n_1, const Integer& n_2) {

	// hay que poner una excepcion supongo. En caso de que reciba Integers con first en null.
	// if (!n_1.first || !n_2.first) { throw 1; } 

	// Variables auxilires
	short int substract; bool borrow = false;
	Integer* result = new Integer();
	Nodo *aux_1 = n_1.first, *aux_2 = n_2.first, *aux_3 = new Nodo();
	result->first = aux_3;

	for (int x = 0; aux_1 ; x++) {

		if (aux_1->v[x] - borrow < ZERO) {
			aux_3->v[x] = (DIGITS_CANT - ONE) - aux_2->v[x];
		}
		else {
			substract = aux_1->v[x] - aux_2->v[x] - borrow;

			if (substract < ZERO) {
				borrow = true;
				aux_3->v[x] = DIGITS_CANT + substract;
			}
			else {
				borrow = false;
				aux_3->v[x] = substract;
			}
		}
		if (x == V_TAM - ONE) {
			// Aqu� se avanza el siguiente nodo, se verifica si hay que llevar carry
			// o si alguno de los integers ya termin� y la otra no, en ese caso solo 
			// se copia el resto de nodos del Integer que no ha terminado.
			aux_2 = aux_2->next; aux_1 = aux_1->next;
			x = -1;
			if (aux_1) {
				aux_3->next = new Nodo();
				aux_3 = aux_3->next;
				if (aux_1 && !aux_2) { nodos_copy(aux_3, aux_1); return *result; }
			}
		}
	}
	//aux_3->next = nullptr;
	return *result;
}
Integer& Integer::multiplication(Integer& n_1, const Integer& n_2)
{
	std::string n_1_value = n_1.toString();
	std::string n_2_value = n_2.toString();
	int n_1_size = n_1_value.size();
	int n_2_size = n_2_value.size();
	int n_1_index = 0;
	int n_2_index = 0;
	//Vector to store the result
	std::vector<int> vector_result(n_1_size + n_2_size,0);

	for (int i = n_1_size - 1; i >= 0; i--) {
		
		int carry = 0;
		int n_1 = (n_1_value[i])-48;
		n_2_index = 0;
		for (int j = n_2_size - 1; j >= 0; j--)
		{
			int n_2 = n_2_value[j]-48;
			int sum = n_1 * n_2 + vector_result[n_1_index + n_2_index] + carry;
			carry = sum / 10;
			vector_result[n_1_index + n_2_index] = sum % 10;
			n_2_index++;
		}
		if (carry > 0)
			vector_result[n_1_index + n_2_index] += carry;
		n_1_index++;
	}
	int result_index = vector_result.size() - 1;
	while (result_index >= 0 && vector_result[result_index] == 0)
		result_index--;

	std::string string_result = "";
	while (result_index >= 0)
		string_result += std::to_string(vector_result[result_index--]);

	return *parse(string_result);

}
/*Javier: Hay varias cosas que se pueden cambiar para que sea mejor (ya sea que se vea m�s ordenado o que sea m�s eficiente), 
pero di sirve para probar y di cumple lo que se espera de esto*/

//Returns string of the digits of Integer
std::string Integer::toString() const{

	std::stringstream stringIntegerD; // Stringstream in which the digits of a Node are stored
	std::string stringInteger=""; // String in which all the digits of Integer are stored, but with the extra zeros
	std::stringstream actualStringInteger; // Stringstream in which there are no extra zeros 
	                                       //(i.e. 00002 would be saved as 2 in this stringstream)

	Nodo* aux = first;
	short int digits=0;


	
	while (aux) {

		for (int i = V_TAM-1; i >= 0; i--) {

			digits = aux->v[i];

			// To check if there is a need to add zeros, because each cell saves 4 digits 
			if (digits < 10) {
				stringIntegerD << "000" << digits;
				continue;
			}

			if (digits < 100) {
				stringIntegerD << "00" << digits;
				continue;
			}

			if (digits < 1000) {
				stringIntegerD << "0" << digits;
				continue;
			}

			stringIntegerD << digits;
		
		}

		stringInteger =  stringIntegerD.str() + stringInteger; // To save the digits in order
		stringIntegerD.str(""); // The string is emptied to save only the next batch of digits
		aux = aux->next; // we move to the next node
	}



	// If the Integer is negative then a minus sign is added in the stringstream
	if (!sign)
		actualStringInteger << "-";

	// The following for is to create a stringstream where there are no extra zeros

	bool startPrintingActualNumber = false; // To know when to start getting numbers

	for (int i = 0; i < stringInteger.length(); i++) {

		if (stringInteger[i] != '0') // Is true when the number starts
			startPrintingActualNumber = true;

		if (startPrintingActualNumber)
			actualStringInteger  << stringInteger[i];
	}

	// If startPrintingActualNumber is false after the cicle, it's because what was stored was the number ZERO
	if (!startPrintingActualNumber)
		actualStringInteger << '0';


	return actualStringInteger.str();

}

Integer& Integer::operator+(const Integer& n_2) {
	// se necesita la sobrecarga de los comparadores
	return sum(*this, n_2);
}

Integer& Integer::operator*(const Integer& n_2)
{
	return multiplication(*this, n_2);
}

void Integer::operator+=(const Integer& n_2){
	// Falta probar
	*this = *this + n_2;
}

Integer& Integer::operator-(const Integer& n_2) {
	// se necesita la sobrecarga de los comparadores
	return substract(*this, n_2);
}

void Integer::operator-=(const Integer& n_2){
	// Falta probar
	*this = *this - n_2;
}

Integer& Integer::operator=(const Integer& n_2) {
	if (!this->first) { this->first = new Nodo(); }
	nodos_copy(this->first, n_2.first);
	return *this;
}

bool Integer::operator==(const Integer& n_2) {

	Nodo* aux1 = this->first;
	Nodo* aux2 = n_2.first;

	while (aux1 && aux2) {

		for (int i = 0; i < V_TAM; i++)
			if (aux1->v[i] != aux2->v[i]) // It an element from the array is different then ther are not equal
				return false;

		aux1 = aux1->next;
		aux2 = aux2->next;

		if ((aux1 && !aux2) || (!aux1 && aux2)) //If they are of different length they are not equal
			return false;

	}

	return true; // If we get here then both Integers are equal

}
bool Integer::operator!=(const Integer& n_2){

	if (*this == n_2)
		return false;
	else
		return true;
}
bool Integer::operator<(const Integer& n_2){

	if (*this == n_2) // We check if they are equal 
		return false;

	Nodo* aux1 = this->first;
	Nodo* aux2 = n_2.first;
	char smaller; // To know which one is lesser in case both of them are of the same amount of nodes

	while (aux1 && aux2) {

		// We change smaller according to the values of the nodes
		for (int i = 0; i < V_TAM; i++) {
			if (aux1->v[i] < aux2->v[i]) 
				smaller = 'L';
			else
				if (aux1->v[i] > aux2->v[i])
					smaller = 'R';
		}

		aux1 = aux1->next;
		aux2 = aux2->next;

		if ((aux1 && !aux2)) //If aux1 has more nodes than aux2 it is because aux1 is bigger
			return false;
		else
			if ((!aux1 && aux2)) // If aux1 has less nodes then its smaller
				return true;
	}

	if (smaller == 'L')
		return true;
	else
		return false;

	return false;
}
bool Integer::operator>(const Integer& n_2){
	if (*this == n_2 || *this < n_2)
		return false;
	else
		return true;
}
bool Integer::operator<=(const Integer& n_2){

	if (*this < n_2 || *this == n_2)
		return true;
	else
		return false;
}
bool Integer::operator>=(const Integer& n_2){
	if (*this > n_2 || *this == n_2)
		return true;
	else
		return false;
}
Integer* Integer::parse(std::string number)
{
	Integer* new_integer = new Integer();
	Nodo* aux = new Nodo();
	aux = new_integer->first;
	int number_len = number.size();
	int vector_position = 0;
	std::string num_group = "";
	std::string test;

	short int test2;
	for (int i = 0; i < number_len; i++) {

		num_group = number.back() + num_group;
		number.pop_back();

		if (vector_position > 4) {
			aux->next = new Nodo();
			aux = aux->next;
			vector_position = 0;

		}
		if (number.size() <= num_group.size()) {
			aux->v[vector_position] = stoi(num_group);
		}
		if (num_group.size() >= 4) {
			aux->v[vector_position] = stoi(num_group);
			vector_position += 1;
			num_group = "";

		}
	}

	return new_integer;
}
// Overload of << Operator using the method toString()
std::ostream& operator <<(std::ostream& exit, const Integer& node) {
	exit << node.toString();
	return exit;
}