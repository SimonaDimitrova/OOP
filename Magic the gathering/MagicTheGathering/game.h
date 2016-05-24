#ifndef __GAME__HEADER__INCLUDED__
#define __GAME__HEADER__INCLUDED__
#include <fstream>


struct Player
{
	char name[128];
	unsigned short ID;
};


struct Card
{
	//8 instead of 5 (strlen("Green")) for padding and alignment reasons
	char color[8]; 
	char name[64];
	unsigned short int ID;
};

struct Deck 
{
	Player player;
	Card card[60];
	int color; 
};

bool isCommand(const char*);

bool searchPlayerIDinFile(const int, const char*);
bool searchCardIDinFile(const int, const char*);
bool searchPlayerName(const char*, const char *);
bool searchCardinFile(const char*, Card&);
bool searchCardByID(int a, Card&);

int colorD(const Deck&, const int);
int returnColor(const char*);

void createPlayer();
void createCard();
void createDeck();
bool reportWithoutDecks();
bool report();

#endif 