#ifndef __BASKET__HEADER__INCLUDED__
#define __BASKET__HEADER__INCLUDED__
#include<iostream>
#include"Egg.h"

class Basket
{
public:
	Egg& operator[](int) const;	
	Egg& operator[](char*) const;
	Basket& operator+=(const Basket&);
	Basket& operator+=(char*);
	Basket& operator*=(double);
	Basket& operator/=(double);
	Basket& operator%=(const Basket&);
	bool operator==(const Basket&)const;
	bool operator!=(const Basket&)const;
	
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
	int getSize()const;
	bool hasEgg(const Egg&)const;

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

Basket operator + (const Basket&, const Basket&); 
Basket operator+(const Basket&, const char*);
Basket operator*(const Basket&, double);
Basket operator/(const Basket&, double);
Basket operator%(const Basket&, const Basket&);
bool operator<(const Basket&, const Basket&);
bool operator<=(const Basket&, const Basket&);
bool operator>=(const Basket&, const Basket&);
#endif // !__BASKET__HEADER__INCLUDED_
