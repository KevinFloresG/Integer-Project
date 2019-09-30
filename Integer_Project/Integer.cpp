// Integer.cpp
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador
// Description: Implementation of Integer.h.

#include"Integer.h"
#include <sstream>
#include <vector>


Integer::Integer() : sign(true), first(new Nodo()) { first->next = nullptr; }

Integer::Integer(int n) : sign(true) {

	//Int constructor
	//Create a integer using int value
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
			aux->v[x] = (short int)(n % DIGITS_CANT); 
			n /= DIGITS_CANT;
		}
	}
}

Integer::Integer(long n): sign(true) {

	//Long constructor
	//Create a integer using long value
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
			aux->v[x] = (short int)(n % DIGITS_CANT); 
			n /= DIGITS_CANT;
		}
	}
}

Integer::~Integer(){
	Empty(); 
	delete first;
}

void Integer::setSign(bool b_value){
	sign = b_value;
}

bool Integer::getSign()const{
	return sign;
}

void Integer::NodosCopy(Nodo* actual, const Nodo* n) {
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

Integer& Integer::Addition(Integer& n_1, const Integer& n_2) {

	 //Returns the sum of two Integers

	 if (!n_1.first || !n_2.first) { 
		 throw MyExceptions("The first node of one of the integers doesn't exist"); 
	 }

	 if (!n_1.getSign() || !n_2.getSign()) // If it is an addition of one or two negatives then it can be treated as a substraction
		 return Substract(n_1, n_2);



	int sum; bool carry = false;
	Integer* result = new Integer();
	Nodo *aux_1 = n_1.first, *aux_2 = n_2.first, *aux_3 = new Nodo();
	result->first = aux_3;

	for (int x = 0; aux_1 || aux_2; x++) {

		sum = aux_1->v[x] + aux_2->v[x];

		if (sum >= DIGITS_CANT) { // Verifying if the sum have more than 4 digits
			carry = true; 
			aux_3->v[x] += sum % DIGITS_CANT;
		}
		else {
			carry = false;
			aux_3->v[x] += sum;
		}
		
		if (x == V_TAM - ONE) { // The end of the node array
			aux_2 = aux_2->next; aux_1 = aux_1->next; 
			x = -1;
			if (carry || aux_1 || aux_2) { // Adding new Node if is needed
				aux_3->next = new Nodo();
				aux_3 = aux_3->next;
				aux_3->v[ZERO] = carry;
				// Copy nodes if one of the two integers is finished already 
				if (aux_1 && !aux_2) { NodosCopy(aux_3, aux_1); return *result; } 
				if (aux_2 && !aux_1) { NodosCopy(aux_3, aux_2); return *result; }
			}
		}
		else {
			aux_3->v[x + ONE] = carry; // adding carry to the next position
		}
	}
	return *result;
}

void Integer::Verify(Integer& n) {

	//Check if the value of the last node is zero
	Nodo* aux = n.first;
	Nodo* aux_prev = aux;
	while (aux->next) { aux_prev = aux;  aux = aux->next; }
	if (aux != n.first) {
		for (int x = 0; x <= V_TAM; x++){
			if (x == V_TAM) { delete aux; aux_prev->next = nullptr; break; } // Delete the node if it has only zeros
			else { if (aux->v[x] != 0) break; }
		}
	}
}

Integer& Integer::MultiplyForInt(const Integer& integer, short int value, int ceros) {

	//Complementary method for multiplication
	//Multiply a integer by short int value 
	//Exception


	if (!integer.first) {
		throw MyExceptions("The first node of the integer doesn't exist");
	}

	short int carry = 0; Integer *end = new Integer();
	Nodo* result = end->first; short int x = 0, y = 0;
	Nodo* aux = integer.first; int multiply;
	if (ceros > ZERO) {	// adding zeros on the result
		while (ceros >= V_TAM) {
			result->next = new Nodo();
			result = result->next;
			result->next = nullptr;
			ceros -= V_TAM;
		}
		y = ceros; // putting de iterator for the result in the correct position after de ceros 
	}
	while(aux && x < V_TAM) { // multiplying de short int value with the given integer
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
	if (carry) { // Verifying if there is a missing carry
		if (y >= V_TAM) { // Adding the missing carry
			result->next = new Nodo(); result = result->next;
			result->v[ZERO] = carry; result->next = nullptr;
		}
		else { result->v[y] = carry; }
	}
	Integer::Verify(*end); // Verifying the last node.

	if ((!integer.getSign() && value >= 0) || (integer.getSign() && value < 0)) // The sign is added if needed
		end->setSign(false);

	return *end;
}

Integer& Integer::Multiplication(Integer& n_1, const Integer& n_2) {

	//Returns the multiplication of two integers
	//Exception
	if (!n_1.first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	std::vector<Integer*> integers = std::vector<Integer*>(); Integer* result = new Integer();
	short int ceros = 0; Nodo* aux = n_2.first;
	short int x = 0;
	while (aux) { // Go through the entire second integer
		while ( x < V_TAM){
			// Multiplying each position of the vectors that conform the second integer with de first integer
			// and adding the result to the auxiliar list of integer's
			integers.push_back(&Integer::MultiplyForInt(n_1, aux->v[x], ceros));
			x++; ceros++;
		}
		x = 0; aux = aux->next;
	}
	for (Integer *in : integers) { 
		*result += *in; // Sum of all resulting integers
	}
	integers.clear(); // Deleting integer's

	if ((!n_1.getSign() && n_2.getSign()) || (n_1.getSign() && !n_2.getSign())) // The sign is added if needed
		result->setSign(false);

	return *result;
}

Integer& Integer::Substract(Integer& n_1, const Integer& n_2) {

	//Return the substraction of two integers
	//Exception
	if (!n_1.first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	
	short int Substract; bool borrow = false;
	Integer* result = new Integer();
	Nodo *aux_1 = n_1.first, *aux_2 = n_2.first, *aux_3 = new Nodo();
	result->first = aux_3;

	for (int x = 0; aux_1 ; x++) {

		// Substracting position to position and looking if is needed a borrow
		// always the bigger integer is n_1.

		if (aux_1->v[x] - borrow < ZERO) {
			aux_3->v[x] = (DIGITS_CANT - ONE) - aux_2->v[x];
		}
		else {
			Substract = aux_1->v[x] - aux_2->v[x] - borrow; 

			if (Substract < ZERO) {
				borrow = true;
				aux_3->v[x] = DIGITS_CANT + Substract;
			}
			else {
				borrow = false;
				aux_3->v[x] = Substract;
			}
		}
		if (x == V_TAM - ONE) {
			aux_2 = aux_2->next; aux_1 = aux_1->next;
			x = -1;
			if (aux_1) {
				aux_3->next = new Nodo();
				aux_3 = aux_3->next;
				if (aux_1 && !aux_2) { NodosCopy(aux_3, aux_1); return *result; }
			}
		}
	}

	return *result;
}


std::string Integer::toString() const{
	//Returns string of the digits of Integer
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

	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	return Addition(*this, n_2);
}

Integer& Integer::operator*(const Integer& n_2){

	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	return Multiplication(*this, n_2);
}

void Integer::operator+=(const Integer& n_2){

	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	*this = *this + n_2;
}

Integer& Integer::operator-(const Integer& n_2) {
	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	if (*this < n_2) {
		Integer result;
		Integer aux = n_2;
		result = Substract(aux, *this);
		result.setSign(false);
		return result;
	}

	return Substract(*this, n_2);
}

void Integer::operator-=(const Integer& n_2){
	//Exception
	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}
	
	*this = *this - n_2;
}



Integer& Integer::operator=(const Integer& n_2) {

	if (!this->first) { this->first = new Nodo(); }
	this->Empty();
	NodosCopy(this->first, n_2.first);
	this->setSign(n_2.getSign());
	return *this;
}

bool Integer::operator==(const Integer& n_2) {

	if (!this->first || !n_2.first) {
		throw MyExceptions("The first node of one of the integers doesn't exist");
	}

	if (this->getSign() != n_2.getSign())
		return false;

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

	if (!this->getSign() && n_2.getSign())
		return true;

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

	if (this->getSign() && !n_2.getSign())
		return true;

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
	//This method creates a integer using a string
	Integer* new_integer = new Integer();
	Nodo* aux = new Nodo();
	aux = new_integer->first;
	int number_len = number.size();
	int vector_position = 0;
	std::string num_group = "";
	for (int i = 0; i < number_len; i++) {

		//Take the elements of a string and group them in groups of 4
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

	//Returns the factorial of a number

	//We convert the integer to positive
	if (!number->sign) {

		number->setSign(true);

	}

	Integer* result = new Integer(1);
	Integer* index = new Integer(1);
	Integer* increment = new Integer(1); //To increase the index

	for (*index; *index <= *number; *index = *index + *increment) {
		
		*result = *result * *index;
		
	}
	delete index;
	delete increment;
	return result;
}
Integer* Integer::Fibonacci(Integer* n){

	//Fibonacci sequence

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
		aux_1->Empty(); // We Empty aux_1 
		*aux_1 = *aux_2; // The value of aux_2 is assigned to aux_1
		aux_2->Empty(); // We Empty aux_2 
		*aux_2 = *aux_3; // The value of aux_3 is assigned to aux_2

	}
	aux_2->Empty(); // We Empty aux_2 one last time because it has the same value of aux_3

	return aux_3; // The n_th term is returned
}

void Integer::Empty() {
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
	first->next = nullptr;
}
// Overload of << Operator using the method toString()
std::ostream& operator <<(std::ostream& exit, const Integer& node) {
	exit << node.toString();
	return exit;
}

int Integer::GetNodesCant() {

	Nodo* aux = new Nodo();
	aux = first;
	int cant = 1;
	while (aux->next!= nullptr) {
		
		
		cant++;
		aux = aux->next;
	}
	return cant;
}
int Integer::WastedMemory() {
	//Returns the wasted memory of the integer
	// Number of bytes per node - Number of bytes used in the first node  + size of the next pointer of the last node
	return NODE_SIZE - (((((this->toString().size() % NODE_SIZE) / NUM_TAM))+1) *2) + sizeof(this->GetLastNode()->next);
}

Nodo* Integer::GetLastNode()
{	
	//Returns the last element of teh Integer
	Nodo* aux = this->first;

	while (aux->next != first) {
		aux = aux->next;
	}
	return aux;
}
