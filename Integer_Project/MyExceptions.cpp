// MyExceptions.h
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador
// Description: Implementation of MyExceptions.h.

#include "MyExceptions.h"

MyExceptions::MyExceptions(string m):message(m){
}

const char* MyExceptions::what() throw(){
	return message.c_str();
}

MyExceptions::~MyExceptions() throw()
{
}
