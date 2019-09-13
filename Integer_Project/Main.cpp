// Main.cpp
//
// Description: Main program.

#include<iostream>
#include"Integer.h"

int main(int argc, char* argv[]) {
	int _int = 1234567891;
	long int _long = 234566123;
	Integer* x = new Integer(_int);
	Integer* y = new Integer(_long);
	system("pause");
	return 0;
}