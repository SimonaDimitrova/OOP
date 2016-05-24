#ifndef __EGG__HEADER__INCLUDED
#define __EGG__HEADER__INCLUDED
#include<iostream>

using std::cout;
using std::endl;

class Egg
{
public:
	Egg& operator+=(const char*);
	Egg& operator*=(double);

public:
	Egg();
	Egg(const char*, double);
	Egg(const Egg&);
	~Egg();
	Egg& operator=(const Egg&);

	int getSize()const;
	char* getName()const;
	void setEgg(const char*, double);
	void setName(const char*);
	void setSize(double);
	
private:
	char* name;
	double size; 
};


#endif // !__EGG__HEADER__INCLUDED
