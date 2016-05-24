#include "Egg.h"
#include "Basket.h"
#include <iostream>
#include <fstream>

const int INITIAL_SIZE = 8;


//Operator [] - by given index, if valid, returns the egg in that index
Egg & Basket::operator[](int index) const 
{
	if (index<0 || index>amountOfEggs)
		cout << "Invalid index." << endl;
	return eggs[index];
}

//Operator [] - by given array, returns the first egg in that index, if there is one
Egg & Basket::operator[](char * arr) const
{
	for (int i = 0; i < amountOfEggs; i++)
	{
		if (!strcmp(arr, eggs[i].getName()))
		{
			cout << "In index : " << i << endl;
			return eggs[i];
		}
	}
}

//Operator += - concatenating two baskets 
Basket & Basket::operator+=(const Basket & b)
{
	this->setName(b.getName());
	for (int i = 0; i < b.getSize(); i++)
		this->add≈gg(b[i]);
	
	return *this;
}

//Operator += - concatenating an array with all of the eggs in the current basket
Basket & Basket::operator+=(char * arr)
{	
	for (int i = 0; i < amountOfEggs; i++)
	{
		//by using the operator += in class Egg
		eggs[i] += arr;
	}

	return *this;
}

//Operator *=  - by given number multiplyes all egg sizes in the basket by that number
Basket & Basket::operator*=(double s)
{
	for (int i = 0; i < amountOfEggs; i++)
	{
		//by using the operator *= in class Egg
		eggs[i]*= s;
	}
	return *this;
}

//Operator /= - by given number divides all egg sizes in the basket by that number
Basket & Basket::operator/=(double s)
{
	if (s != 0)
	{
		for (int i = 0; i < amountOfEggs; i++)
		{
			//by using the operator *= in class Egg dividing by 1/s
			eggs[i] *= 1/s;
		}
	}
	else
		cout << "Dividing by zero? Some people just wanna watch the world burn." << endl;

	return *this;
}

// Operator %= - counts how many of the same eggs are in two baskets
Basket & Basket::operator%=(const Basket & basket)
{ 
	for (int i = 0; i < amountOfEggs; i++) 
	{
		//if an egg from this is in basket
		if (!basket.hasEgg(eggs[i])) 
		{
			//if not, removing the one in this
			removeEgg(eggs[i].getName()); 
			//i--, because when removing an egg, it puts the last one in his place, so we have to check that position again
			i--;
		}
	} 
	return *this;
}

/*Operators (==, !=) - comparing two baskets. Two baskets are equal when every element in the position i in the first basket
is equal to the element in the same position in the second basket. Two eggs are equal if the arrays of their names are the same.*/
bool Basket::operator==(const Basket & basket) const
{
	if (amountOfEggs != basket.amountOfEggs)
	{
		return false;
	}
	
	for (int i = 0; i < amountOfEggs; i++)
	{
		if (strcmp(eggs[i].getName(), basket.eggs[i].getName()))
			return false;
	}

	return true;
}

bool Basket::operator!=(const Basket & basket) const
{
	return !(*this == basket);
}

//Operator + - concatenating two baskets 
Basket operator + (const Basket & a, const Basket & b)
{
	Basket result(a);
	result += b; 
	return result;
}

//Operator + - concatenating an array with all of the eggs in the current basket
Basket operator+(const Basket & basket, const char * arr) 
{	
	Basket result(basket);
	result += arr;
	return result;
}

//Operator * - by given number multiplyes all egg sizes in the basket by that number
Basket operator*(const Basket & basket, double n)
{
	Basket result (basket);
	result *= n;
	return result;
}

//Operator / - by given number divides all egg sizes in the basket by that number
Basket operator/(const Basket & basket, double n)
{
	Basket result(basket);
	result /= n; 
	return result;
}

// Operator %= - counts how many of the same eggs are in two baskets
Basket operator%(const Basket & a, const Basket & b)
{
	Basket result(a);	
	result %= b;
	return result;
}
/*Operators (<, <=, >=) - compares two baskets. First basket is smaller than the second, when we encounter an element in
the first, which is smaller than the one in the second and by that time no bigger element is encountered.
Two eggs are equal if the arrays of their names are the same. One egg is smaller than the other, if the array of
the first egg is smaller than the one in the second.*/

bool operator<(const Basket &a, const Basket &b)
{
	int min;
	if (a.getSize() < b.getSize())
		min = a.getSize();
	else
		min = b.getSize();

	for (int i = 0; i < min; i++)
	{
		if ((strcmp(a[i].getName(), b[i].getName()) > 0)) 
			return false;
	} 

	if(a.getSize() <= b.getSize()) 
	{ 
		return true;
	}
	else
	{
		return false;
	}
}

bool operator<=(const Basket & a, const Basket & b)
{
	//a<=b <=> !(b<a)
	return !(b<a);
}

bool operator>=(const Basket & a, const Basket & b)
{
	//a>=b  <=> !(a<b)
	return !(a<b);
}

Basket::Basket() :eggs(NULL), basketSize(INITIAL_SIZE), amountOfEggs(0), name(NULL)
{
	init();
	setName("");
}

Basket::Basket(const Basket& b) : eggs(NULL), name(NULL)
{
	basketSize = b.basketSize;
	amountOfEggs = b.amountOfEggs;
	setName(b.name);
	init();

	for (int i = 0; i < amountOfEggs; i++)
		eggs[i] = b.eggs[i];
}

Basket :: ~Basket()
{
	delete[] eggs;
	delete[] name;
}

Basket&Basket::operator=(const Basket& b)
{
	if (this != &b)
	{
		basketSize = b.basketSize;
		amountOfEggs = b.amountOfEggs;
		setName(b.name);
		for (int i = 0; i < amountOfEggs; i++)
			eggs[i] = b.eggs[i];
	}
	return *this;
}


Basket::Basket(const char* n) : eggs(NULL), name(NULL), basketSize(INITIAL_SIZE), amountOfEggs(0)
{
	setName(n);
	init();
}

void Basket::setName(const char* n)
{
	int len = strlen(n);
	char* tmp = new (std::nothrow) char[len + 1];
	if (!tmp) return;

	//delete after checking if the allocation for the new name is successfull
	strcpy_s(tmp, len + 1, n);
	delete[] name;
	name = tmp;
}

void Basket::add≈gg(const Egg& a)
{
	if (amountOfEggs >= basketSize)
	{
		resize(basketSize * 2);
	}

	//adding the egg in the first empty position, which is on 'amountOfEggs'
	eggs[amountOfEggs] = a;
	amountOfEggs++;
}

void Basket::removeEgg(const char* str)
{
	if(amountOfEggs == 1)
		if (strcmp(eggs[0].getName(), str) == 0)
		{
			amountOfEggs--;
			return;
		}
	//putting the last egg on the position of the egg we want to remove
	//amountOfEggs-1 is the position of the last egg
	for (int i = 0; i < amountOfEggs; i++)
	{
		if (!(strcmp(eggs[i].getName(), str)))
		{
			//after switching it, size-- and break so that we don't check the rest of the objects
			eggs[i] = eggs[amountOfEggs - 1];
			amountOfEggs--;
			break; 
		}
	}

	if (amountOfEggs <= basketSize / 2)
	{
		resize(basketSize / 2);
	}
}

char * Basket::getName() const
{
	return name;
}

int Basket::getSize() const
{
	return amountOfEggs;
}

bool Basket::hasEgg(const Egg & e)const
{
	for (int i = 0; i < amountOfEggs; i++)
	{
		//if there's same egg as 'e' return true
		if (!strcmp(this->eggs[i].getName(), e.getName()))
			return true;
	}
	//no same egg found
	return false;
}


void Basket::print()const
{
	cout << "Name of owner: " << name << endl;

	for (int i = 0; i < amountOfEggs; i++)
	{
		cout << eggs[i].getName() << " " << eggs[i].getSize() << endl;
	}
}

void Basket::report() const
{
	std::ofstream myfile;
	char n[1000];
	int nameLen = strlen(name);
	strcpy_s(n, nameLen + 1, name);
	strcat_s(n, 1000 + 1, ".txt"); 
	myfile.open(n);
	for (int i = 0; i < amountOfEggs; i++)
	{
		myfile << eggs[i].getName() << " " << eggs[i].getSize() << endl;
	}
	myfile.close();
}

bool Basket::serialize(const char* file)
{
	std::ofstream myfile(file, std::ios::binary);
	if (!myfile)
	{
		cout << "Error" << endl;
		return false;
	}

	myfile.write((char*)&amountOfEggs, sizeof(amountOfEggs));

	int basketNameLen = strlen(name);
	myfile.write((char*)&basketNameLen, sizeof(basketNameLen));
	myfile.write((char*)name, basketNameLen);

	for (int i = 0; i < amountOfEggs; i++)
	{
		double eggSize = eggs[i].getSize();
		myfile.write((char*)&eggSize, sizeof(eggSize));

		char* eggName = eggs[i].getName();
		int nameLen = strlen(eggName);
		myfile.write((char*)&nameLen, sizeof(nameLen));
		myfile.write((char*)eggName, nameLen);

	}
	myfile.close();
	return true;
}


 // Deserializing the basket from the binary file in the already existing basket
 // If there is an error, the existing basket is not changed
bool Basket::deserialize(const char* file)
{
	Basket d;
	cout << "Iniating deserialization." << endl;

	std::ifstream myfile(file, std::ios::binary);
	if (!myfile)
	{
		cout << "Error" << endl;
		return false;
	}
	
	int amountOfE;
	myfile.read((char*)&amountOfE, sizeof(amountOfE));
	if (!myfile)
	{
		cout << "Error." << endl;
		return false;
	}

	char buffer[1000];
	int basketNameLen=0;
	myfile.read((char*)&basketNameLen, sizeof(basketNameLen));
	myfile.read((char*)buffer, basketNameLen);
	name[basketNameLen] = '\0';
	d.setName(buffer);

	for (int i = 0; i < amountOfE; i++)
	{
		double eggSize = 0;
		myfile.read((char*)&eggSize, sizeof(eggSize));

		int nameSize = 0;
		myfile.read((char*)&nameSize, sizeof(nameSize));
		myfile.read((char*)buffer, nameSize);
		buffer[nameSize] = '\0';
		d.add≈gg(Egg(buffer, eggSize));
	}
	//if all is okay, existing basket = basket we just read from the binary file
	*this = d;
	myfile.close();
	return true;
}

void Basket::resize(int r)
{
	Egg* newBasket = new Egg[r];
	basketSize = r;
	for (int i = 0; i < basketSize; i++)
	{
		newBasket[i] = eggs[i];
	}

	delete[] eggs;
	eggs = newBasket;
}

void Basket::init()
{
	Egg* tmp = new (std::nothrow) Egg[basketSize];
	if (!tmp) return;

	delete[] eggs;
	eggs = tmp;
}

