#ifndef __BASKET__HEADER__INCLUDED__
#define __BASKET__HEADER__INCLUDED__
#include<iostream>
#include"Egg.h"

class Basket
{
public:
	Basket();
	Basket(const Basket&);
	~Basket();
	Basket& operator=(const Basket&);
	Basket(const char*);

	void setName(const char*);
	void add≈gg(const Egg&);
	void removeEgg(const char*);
	char* getName()const;

	void print() const;
	void report()const;
	bool serialize(const char*);
	bool deserialize(const char*);

private:
	void resize(int);
	void init();

	char* name;
	Egg* eggs; 
	int amountOfEggs;
	int basketSize;
};

#endif // !__BASKET__HEADER__INCLUDED__
