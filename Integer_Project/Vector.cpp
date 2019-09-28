// Vector.cpp
// Authors: Kevin Flores, Philippe Gairaud, Javier Amador.
// Description: Implementation of Vector.h

#include "Vector.h"

Vector::Vector(int size)
{
	this->size = size;
	vector = new int [size];
	for (int i = 0; i < size; i++) {
		vector[i] = 0;
	}
}

int Vector::GetPosition(int position)
{
	return vector[position];
}

int Vector::GetSize()
{
	return size;
}

void Vector::AddCarry(int position, int carry)
{
	vector[position] += carry;
}

void Vector::Add(int position, int number)
{

	vector[position] = number;

}



Vector::~Vector()
{

}
