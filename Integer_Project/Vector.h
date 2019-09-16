#ifndef VECTOR_H
#define VECTOR_H


class Vector {

private:
	int size;
	int* vector;
public:
	Vector(int);
	int GetPosition(int);
	int GetSize();
	void AddCarry(int,int);
	void Add(int, int);
	~Vector();



};


#endif // !VECTOR_H