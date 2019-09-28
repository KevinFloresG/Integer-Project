// Integer.cpp
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador
// Description: Implementation of Integer.h.

#include"Integer.h"
#include <sstream>
#include <vector>


Integer::Integer() : sign(true), first(new Nodo()) { first->next = nullptr; }

Integer::Integer(int n) : sign(true) {
	if (n < ZERO) { 
		sign = false; n *= -1; 
	}
	first = new Nodo();
	first->next = nullptr;
	Nodo* aux = first; // se auto destruye al salir del metodo no? (la memoria del puntero se libera)

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

Integer::~Integer(){
	/*empty();*/
}

void Integer::setSign(bool b_value){
	sign = b_value;
}

bool Integer::getSign(){
	return sign;
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

Integer& Integer::addition(Integer& n_1, const Integer& n_2) {

	// hay que poner una excepcion supongo. En caso de que reciba Integers con first en null.
	// Excepcion agregada
	 if (!n_1.first || !n_2.first) { 
		 throw MyExceptions("The first node of one of the integers doesn't exist"); 
	 } 

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
	//aux_3->next = nullptr;
	return *result;
}

void Integer::verify(Integer& n) {
	// verifica si el ultimo nodo vale cero
	Nodo* aux = n.first;
	Nodo* aux_prev = aux;
	while (aux->next) { aux_prev = aux;  aux = aux->next; }
	if (aux != n.first) {
		for (int x = 0; x <= V_TAM; x++){
			if (x == V_TAM) { delete aux; aux_prev->next = nullptr; break; }
			else { if (aux->v[x] != 0) break; }
		}
	}
}

Integer& Integer::multiply_for_int(const Integer& integer, short int value, int ceros) {

	//Exception
	if (!integer.first) {
		throw MyExceptions("The first node of the integer doesn't exist");
	}

	short int carry = 0; Integer *end = new Integer();
	Nodo* result = end->first; short int x = 0, y = 0;
	Nodo* aux = integer.first; int multiply;
	if (ceros > ZERO) { 
		while (ceros >= V_TAM) {
			result->next = new Nodo();
			result = result->next;
			result->next = nullptr;
			ceros -= V_TAM;
		}
		y = ceros;
	}
	while(aux && x < V_TAM) {
		multiply = (aux->v[x] * value) + carry;
		if (multiply >= DIGITS_CANT) {
			carry = multiply / DIGITS_CANT;
			multiply %= DIGITS_CANT;
		}
		else { carry = 0; }
		result->v[y] = (short int)multiply;
		multiply = 0;
		x++; y++;
		if (y >= V_TAM) {
			y = 0;
			result->next = new Nodo();
			result = result->next;
			result->next = nullptr;
		}
		if (x >= V_TAM && aux->next) { 
			x = 0; aux = aux->next; 
		}
	}
	if (carry) { 
		if (y >= V_TAM) {
			result->next = new Nodo(); result = result->next;
			result->v[ZERO] = carry; result->next = nullptr;
		}
		else { result->v[y] = carry; }
	}
	Integer::verify(*end);
	return *end;
}

Integer& Integer::multiplication(Integer& n_1, const Integer& n_2) {

	//Exception
	if (!n_1.first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	std::vector<Integer> integers; Integer* result = new Integer();
	short int ceros = 0; Nodo* aux = n_2.first;
	short int x = 0;
	while (aux) {
		while ( x < V_TAM){
			integers.push_back(Integer::multiply_for_int(n_1, aux->v[x], ceros));
			x++; ceros++;
		}
		x = 0; aux = aux->next;
	}
	for (Integer in : integers) { 
		*result += in; 
	}
	integers.clear();
	return *result;
}

Integer& Integer::substract(Integer& n_1, const Integer& n_2) {

	// hay que poner una excepcion supongo. En caso de que reciba Integers con first en null.
	if (!n_1.first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

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
			// Aquí se avanza el siguiente nodo, se verifica si hay que llevar carry
			// o si alguno de los integers ya terminó y la otra no, en ese caso solo 
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
/*
Integer& Integer::multiplication(Integer& n_1, const Integer& n_2)
{
	std::string n_1_value = n_1.toString();
	std::string n_2_value = n_2.toString();
	int n_1_size = n_1_value.size();
	int n_2_size = n_2_value.size();
	int n_1_index = 0;
	int n_2_index = 0;
	//Vector to store the result
	Vector* vector_result = new Vector(n_1_size + n_2_size);

	for (int i = n_1_size - 1; i >= 0; i--) {
		
		int carry = 0;
		int n_1 = (n_1_value[i])-48;
		n_2_index = 0;
		for (int j = n_2_size - 1; j >= 0; j--)
		{
			int n_2 = n_2_value[j]-48;
			int sum = n_1 * n_2 + vector_result->GetPosition(n_1_index + n_2_index) + carry;
			carry = sum / 10;
			vector_result->Add(n_1_index + n_2_index,  sum % 10);
			n_2_index++;
		}
		if (carry > 0)
			vector_result->AddCarry(n_1_index + n_2_index , carry);
		n_1_index++;
	}
	int result_index = vector_result->GetSize()-1 ;
	while (result_index >= 0 && vector_result->GetPosition(result_index) == 0)
		result_index--;

	std::string string_result = "";
	while (result_index >= 0)
		string_result += std::to_string(vector_result->GetPosition(result_index--));

	return *Parse(string_result);

}*/
/*Javier: Hay varias cosas que se pueden cambiar para que sea mejor (ya sea que se vea más ordenado o que sea más eficiente), 
pero di sirve para probar y di cumple lo que se espera de esto*/

//Returns string of the digits of Integer
std::string Integer::toString() const{

	if (!this->first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

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

	aux = nullptr;
	delete aux;

	return actualStringInteger.str();

}

Integer& Integer::operator+(const Integer& n_2) {
	// se necesita la sobrecarga de los comparadores
	// Para que en la suma ? No bastaria fijarse en sign  mandar a llamar a resta ?

	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	return addition(*this, n_2);
}

Integer& Integer::operator*(const Integer& n_2){

	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	return multiplication(*this, n_2);
}

void Integer::operator+=(const Integer& n_2){

	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	// Falta probar
	*this = *this + n_2;
}

Integer& Integer::operator-(const Integer& n_2) {
	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	// se necesita la sobrecarga de los comparadores
	//if (*this < n_2) {
	//	return substract(n_2, *this); // Error por const con n_2
	//}

	return substract(*this, n_2);
}

void Integer::operator-=(const Integer& n_2){

	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}
	
	// Falta probar
	*this = *this - n_2;
}



Integer& Integer::operator=(const Integer& n_2) {

	if (!this->first) { this->first = new Nodo(); }
	this->empty();
	nodos_copy(this->first, n_2.first);
	return *this;
}

bool Integer::operator==(const Integer& n_2) {

	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	Nodo* aux1 = this->first;
	Nodo* aux2 = n_2.first;

	while (aux1 && aux2) {

		for (int i = 0; i < V_TAM; i++)
			if (aux1->v[i] != aux2->v[i]) // If an element from the array is different then ther are not equal
				return false;

		aux1 = aux1->next;
		aux2 = aux2->next;

		if ((aux1 && !aux2) || (!aux1 && aux2)) //If they are of different length they are not equal
			return false;

	}

	return true; // If we get here then both Integers are equal

}
bool Integer::operator!=(const Integer& n_2){

	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}


	if (*this == n_2)
		return false;
	else
		return true;
}
bool Integer::operator<(const Integer& n_2){

	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}


	if (*this == n_2) // We check if they are equal 
		return false;

	Nodo* aux1 = this->first; // aux_1 is used to travel across the first Integer
	Nodo* aux2 = n_2.first; // aux_2 is used to travel across the second Integer
	char smaller; // To know which one is lesser in case both of them are of the same amount of nodes

	while (aux1 && aux2) {

		// We change smaller according to the values of the nodes
		for (int i = 0; i < V_TAM; i++) {
			if (aux1->v[i] < aux2->v[i]) //  Left/First Integer is smaller
				smaller = 'L';
			else
				if (aux1->v[i] > aux2->v[i]) //  Right/Second Integer is smaller
					smaller = 'R';
		}

		aux1 = aux1->next; // We move to the next node of the first Integer
		aux2 = aux2->next; // We move to the next node of the second Integer

		if ((aux1 && !aux2)) //If aux1 has more nodes than aux2 it is because aux1 is bigger
			return false;
		else
			if ((!aux1 && aux2)) // If aux1 has less nodes then its smaller
				return true;
	}

	if (smaller == 'L') // Returns true if first Integer was smaller, and false otherwise
		return true;
	else
		return false;

	return false;
}
bool Integer::operator>(const Integer& n_2){
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	if (*this == n_2 || *this < n_2) // If *this is equal or smaller than n_2 then it can't be bigger
		return false;
	else
		return true;
}
bool Integer::operator<=(const Integer& n_2){ 
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}


	if (*this < n_2 || *this == n_2) // If *this is equal or smaller than n_2 then it returns true
		return true;
	else
		return false;
}
bool Integer::operator>=(const Integer& n_2){
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	if (*this > n_2 || *this == n_2)
		return true;
	else
		return false;
}
Integer* Integer::Parse(std::string number)
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

		if (vector_position >= V_TAM) {
			aux->next = new Nodo();
			aux = aux->next;
			vector_position = 0;

		}
		if (number.size() <= num_group.size()) {
			aux->v[vector_position] = stoi(num_group);
		}
		if (num_group.size() >= NUM_TAM) {
			aux->v[vector_position] = stoi(num_group);
			vector_position += 1;
			num_group = "";

		}
	}

	return new_integer;
}
Integer* Integer::Factorial(Integer* number){	

	// Sirve con negativos ?
	if (!number->sign) {

		throw MyExceptions("This factorial is only for positives");

	}

	Integer* result = new Integer(0);
	Integer* index = new Integer(1);
	Integer* increment = new Integer(1);
	*result = *index;
	*result = *increment;
	*result = *index;
	for (*index; *index <= *number; *index = *index + *increment) {
		
		*result = *result * *index;
		
	}
	return result;
}
Integer* Integer::Fibonacci(Integer* n){
	// Time Complexity O(n) , O(n2) ?

	if (!n->sign) {

	throw MyExceptions("The term is negative");
		
	}

	if (n == 0) // If the desired term is 0 then it is returned immediately
		return new Integer(0);


	Integer* i = new Integer(2); //Counter used to stop the succesion when we arrive at the desired term, since the first two terms
								//of the succcesion are 1, this counter is initialized as 2

	Integer* add = new Integer(1); // Integer used to increase i by one

	Integer* aux_1 = new Integer(1); // aux_1 will act as the n-2_th term of the succesion
	Integer* aux_2 = new Integer(1); // aux_2 will act as the n-1_th term of the succesion
	Integer* aux_3 = new Integer(0); // Result of the operation

	for (i; *i < *n; *i = *i + *add) {

		*aux_3 = *aux_1 + *aux_2; // We get the current term by adding aux_1 to aux_2 or viceversa
		aux_1->empty(); // We empty aux_1 
		*aux_1 = *aux_2; // The value of aux_2 is assigned to aux_1
		aux_2->empty(); // We empty aux_2 
		*aux_2 = *aux_3; // The value of aux_3 is assigned to aux_2

	}
	aux_2->empty(); // We empty aux_2 one last time because it has the same value of aux_3

	return aux_3; // The n_th term is returned
}
/*Integer& operator++(const Integer& number)
{
	Integer* increment = new Integer(1);
	return *number + *increment;
	
}*/

void Integer::empty() {
	if (!first) {
		return;
	}
	Nodo* aux = first->next;
	while (aux) {
		delete first;
		first = aux;
		aux = aux->next;
	}
	delete first;
	first = new Nodo();
}
// Overload of << Operator using the method toString()
std::ostream& operator <<(std::ostream& exit, const Integer& node) {
	exit << node.toString();
	return exit;
}