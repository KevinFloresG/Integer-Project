// MyExceptions.h
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador
// Description: Class to manage exceptions.

#include <exception>
#include<string>
using std::string;


#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

class MyExceptions : std::exception {
public:
	MyExceptions(string);
	const char* what()throw(); // Returns a string that contains the message of what error ocurred
	~MyExceptions()throw();
private:
	string message;
};


#endif // !MYEXCEPTIONS_H