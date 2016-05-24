#include "Egg.h"
#include "Basket.h"
#include <iostream>
#include <fstream>

const int INITIAL_SIZE = 8;

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

void Basket::addÅgg(const Egg& a)
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
	char* n = name;
	int size = strlen(name) + strlen(".txt");
	strcat_s(n, size + 1, ".txt");
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

	int nameLen = strlen(name);
	myfile.write((char*)&nameLen, sizeof(int));
	myfile.write((char*)name, nameLen);

	for (int i = 0; i < amountOfEggs; i++)
	{
		int size = eggs[i].getSize();
		myfile.write((char*)&size, sizeof(size));

		char* eggName = eggs[i].getName();
		int eSize = strlen(eggName);
		myfile.write((char*)&eSize, sizeof(int));
		myfile.write((char*)eggName, eSize);

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

	char namee[1000];
	int s=0;
	myfile.read((char*)&s, sizeof(s));
	myfile.read((char*)namee, s);
	name[s] = '\0';
	d.setName(namee);

	char buffer[1000];
	for (int i = 0; i < amountOfE; i++)
	{
		int size1=0;
		myfile.read((char*)&size1, sizeof(int));

		int size2 = 0;
		myfile.read((char*)&size2, sizeof(int));
		myfile.read((char*)buffer, size2);
		buffer[size2] = '\0';
		d.addÅgg(Egg(buffer, size1));
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