#include "Egg.h"
#include<iostream>

using std::cin;
using std::cout;
using std::endl;

Egg::Egg(): name(NULL), size(0)
{
	setName("");
}

Egg::Egg(const char* e, int newSize) : name(NULL)
{
	setEgg(e, newSize);
}

Egg::Egg(const Egg& e) :name(NULL)
{
	size = e.size;
	setName(e.name);
}

Egg::~Egg()
{
	delete[] name;
}

Egg& Egg::operator=(const Egg& e)
{
	if (this != &e)
	{
		size = e.size;
		setName(e.name);
	}

	return *this;
}


int Egg::getSize()const
{
	return size;
}
char* Egg::getName()const
{
	return name;
}

void Egg::setEgg(const char* n, int newSize)
{
	delete[] name; 
	name = NULL;
	setName(n);
	size = newSize;

}

void Egg::setName(const char * n)
{
	int len = strlen(n);
	char* tmp = new (std::nothrow) char[len + 1];
	if (!tmp) return;

	//delete after checking if the allocation for the new name is successfull
	strcpy_s(tmp, len + 1, n);
	delete[] name;
	name = tmp;
}
