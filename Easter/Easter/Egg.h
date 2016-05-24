#ifndef __EGG__HEADER__INCLUDED
#define __EGG__HEADER__INCLUDED
#include<iostream>

using std::cout;
using std::endl;

class Egg
{
public:
	Egg();
	Egg(const char*, int);
	Egg(const Egg&);
	~Egg();
	Egg& operator=(const Egg&);

	int getSize()const;
	char* getName()const;
	void setEgg(const char*, int);
	void setName(const char*);
	

private:
	char* name;
	int size;
};


#endif // !__EGG__HEADER__INCLUDED
