#include "Egg.h"
#include<iostream>

using std::cin;
using std::cout;
using std::endl;

Egg & Egg::operator+=(const char * arr)
{
	int appendLen = strlen(arr);
	int len = 0;

	//getting the lenght of the egg's name
	int eggLen = strlen(this->getName());

	char* name = new char[eggLen + appendLen + 1];
	//the name is copied 
	strcpy_s(name, eggLen + 1, this->getName());
	//concatenating the name and the given string
	strcat_s(name, eggLen + appendLen + 1, arr);
	//setting it as the new name of the egg 
	this->setName(name);
	delete[] name;

	return *this;
}

Egg & Egg::operator*=(double n)
{
	size *= n;
	return *this;
}

Egg::Egg(): name(NULL), size(0)
{
	setName("");
}

Egg::Egg(const char* e, double newSize) : name(NULL)
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

void Egg::setEgg(const char* n, double newSize)
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

void Egg::setSize(double s)
{
	size = s;
}


