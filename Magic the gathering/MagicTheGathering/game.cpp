#include "game.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;

const char* PLAYERS_FILE = { "players.dat" }; 
const char* CARDS_FILE = { "cards.dat" };
const char* DECKS_FILE = { "decks.dat" };
const char* REPORT_FILE = { "report.txt" };

const int PLAYER_NAME_LEN = 128;
const int CARD_NAME_LEN = 64;
const int DECK_SIZE = 60 ;  
const int NUMBER_OF_COLORS = 5; 
const int MAX_NUMBER_OF_IDS = 32'768;//This is equal to pow(2,15); 

#define RAND (rand() % MAX_NUMBER_OF_IDS )

//5 is the longest color, but I'll keep it 8 (like in the structure)
char colors[][8] = { 
	{ "Red" },
	{ "Black" },
	{ "Blue" },
	{ "White" },
	{ "Green" }
};

bool isCommand( const char* c)
{
	if (strcmp(c, "cc") == 0)
	{
		cout << "Creating a card." << endl;
		createCard();
	}
	else if (strcmp(c, "cd") == 0)
	{
		cout << "Creating a deck." << endl;
		createDeck();
	}
	else if (strcmp(c, "cp") == 0)
	{
		cout << "Creating a player." << endl;
		createPlayer();
	}
	else if (strcmp(c, "report") == 0)
	{
		cout << "Creating a report." << endl;
		report();
	}
	else 
	{
		cout << "Wrong input!" << endl;
		return false;
	}

	return true;
}

//we can unite searchPlayerIDinFile and searchCardIDinFile by using template
bool searchPlayerIDinFile(const int id, const char* fileName)
{
	//open binary file for reading
	std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		inFile.close();
		return false;
	}

	Player tmp;

	//looking for the same ID until the end of the file
	while (!inFile.eof())
	{
		inFile.read((char*)&tmp, sizeof(tmp));
		if (tmp.ID == id)
		{
			cout << "Same ID!" << endl;
			return true;
		}
	}

	inFile.close();
	return false;
}

bool searchCardIDinFile(const int id, const char * fileName) 
{
	//open binary file for reading
	std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		inFile.close();
		return false;
	}

	Card tmp;

	//looking for the same ID until the end of the file
	while (!inFile.eof())
	{
		inFile.read((char*)&tmp, sizeof(tmp));
		if (tmp.ID == id)
		{
			cout << "Same ID!" << endl;
			return true;
		}
	}

	inFile.close();
	return false;
}

bool searchPlayerName(const char* name, const char* fileName) 
{	
	//open binary file for reading
	std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		inFile.close();
		return false;
	}

	Player temp;

	//looking for the same ID until the end of the file
	while (!inFile.eof())
	{
		inFile.read((char*)&temp, sizeof(temp));
		if (!strcmp(temp.name, name))
		{
			cout << "The name exists!" << endl;
			return true;
		}
		
	}

	inFile.close();
	return false;
}

bool searchCardinFile(const char* name, Card& temp) 
{
	//open binary file for reading
	std::ifstream inFile(CARDS_FILE, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		inFile.close();
		return false;
	}

	//looking for the same name until the end of the file
	while (!inFile.eof())
	{
		inFile.read((char*)&temp, sizeof(temp));
		//must chek if the reading is done correctly
		if (!inFile) return false; 

		if (!strcmp(temp.name, name))
		{
			cout << "The name exists!" << endl;
			return true;
		}
	}

	inFile.close();
	return false;
}

bool searchCardByID(int id, Card& c)
{
	//open binary file for reading
	std::ifstream inFile(CARDS_FILE, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		inFile.close();
		return false;
	}

	//looking for the same id until the end of the file
	while (!inFile.eof())
	{
		inFile.read((char*)&c, sizeof(c));

		if (id == c.ID)
		{
			return true;
		}
		
		if (!inFile) return false;
	}

	inFile.close();
	return false;
}

/*
 * With counting sort returns the index in the colors array of the most common color in the deck
 * Returns -1 if there's an invalid color in the deck
 * How to use it:
 * int most_common_color = colorD(myDeck)
 * std::cout<<colors[most_common_color]<<std::endll; 
 */
int colorD(const Deck& d, const int DECK_SIZE)
{
	int countColors[NUMBER_OF_COLORS+1] = { 0 };

	//counting the colors
	for (int i = 0; i < DECK_SIZE; i++)
	{

		int col = returnColor(d.card[i].color); 
		//if the color is invalid 
		if (col < 0)
			return -1;

		//else
		countColors[col]++;
	}

	//finding the position of the most common color (max)
	int max = 0;
	for (int i = 0; i < NUMBER_OF_COLORS; i++)
	{
		if (countColors[i] > countColors[max])
		{ 
			max = i;
		}
	}
	
	return max; 

}

int returnColor(const char* colorName)
{
	for (int i = 0; i < NUMBER_OF_COLORS; i++)
	{
		if (!strcmp(colorName, colors[i])) return i;
	}

	//invalid index if the color is not present in the colors array
	return -1; 
}

void createPlayer()
{
	//open binary file for writing, all output operations are performed at the end of the file
	std::ofstream outFile(PLAYERS_FILE , std::ios::out| std::ios::app | std::ios::binary);
	if (!outFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		outFile.close();
		return ;
	}
	

	Player player;

	cout << "Enter the name of the player (up to 127 characters):" << endl;
	cin.clear(); //todo, do we need all?
	cin.sync();
	cin.ignore();
	cin.getline(player.name, PLAYER_NAME_LEN, '\n');
	srand(time(NULL));

	int id; 
	do {
		id = RAND;
	} while (searchPlayerIDinFile(id, PLAYERS_FILE));

	player.ID = id;

	outFile.write((char*)&player, sizeof(player));
	outFile.close();

}

void createCard()
{
	//open binary file for writing, all output operations are performed at the end of the file
	std::ofstream outFile(CARDS_FILE, std::ios::out | std::ios::app | std::ios::binary);
	if (!outFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		outFile.close();
		return;
	} 

	
	Card card;
	cout << "Enter the color of the card (Red, Black, Blue, White, Green):" << endl;
	//must use cin, because it reads until space so when the card is "White durabura",
	//it will take the first word (until the space) as the color => White, and the rest (durabura) as the name of the card
	cin>>card.color;  
	
	cout << "Enter the name of the card (up to 64 characters):" << endl;
	cin.clear();
	cin.sync();
	cin.ignore();
	cin.getline(card.name, CARD_NAME_LEN, '\n');

	
	//generating random ID between 100 000 and 900 000
	//with srand we seed the randomizer with a value that is always changing by feeding it the value of the current time 
	srand(time(NULL));

	//so when we call rand(), a new random number will be produced every time, while checking if it is the same
	int id;
	do {
		id = RAND;
	} while (searchCardIDinFile(id, CARDS_FILE));
	
	card.ID = id;

	outFile.write((char*)&card, sizeof(Card));
	outFile.close();
}

void createDeck()
{
	//open binary file for writing, all output operations are performed at the end of the file
	std::ofstream outFile(DECKS_FILE, std::ios::out | std::ios::app | std::ios::binary);
	if (!outFile)
	{
		std::cerr << "Error. File not open." << std::endl;
		outFile.close();
		return;
	}
	
	Deck myDeck;

	char buff[PLAYER_NAME_LEN];
	cout << "Enter the name of the player (up to 127 characters):" << endl;
	cin.clear(); 
	cin.sync();
	cin.ignore();
	cin.getline(buff, PLAYER_NAME_LEN, '\n');
	searchPlayerName(buff, PLAYERS_FILE);

	strcpy_s(myDeck.player.name, PLAYER_NAME_LEN , buff);

	Card card{ "","",0 };
	char buff2[CARD_NAME_LEN];
	int count = 0;

	while(count<DECK_SIZE)
	{
		cout << "Enter the name of the card (up to 64 characters):" << endl;
		cin.clear(); 
		cin.sync();
		cin.getline(buff, CARD_NAME_LEN, '\n');

		if (searchCardinFile(buff, card))
		{
			//writing card in deck
			myDeck.card[count] = card;
			count++; 
		}
		
	}
	myDeck.color = colorD(myDeck, DECK_SIZE);

	if ( myDeck.color < 0) {
		std::cout << "Wrong color";
	}
	else {
		std::cout << "Color of the deck is: " << colors[myDeck.color] << std::endl;
	} 
	
	outFile.write((char*)&myDeck, sizeof(Deck));
	outFile.close();

}

bool reportWithoutDecks()
{
	std::ifstream inFile(CARDS_FILE, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		std::cerr << "Error. File not open!" << endl;
		inFile.close();
		return false;
	}

	std::ofstream rep(REPORT_FILE, std::ios::out);
	if (!rep)
	{
		std::cerr << "Error. File not open." << std::endl;
		rep.close();
		return false;
	}

	for (int i = 0; i < NUMBER_OF_COLORS; i++)
	{
		rep << colors[i] << endl;
	}


	Card c;
	inFile.read((char*)&c, sizeof(c));
	rep << "Most common card: " << c.name << " Color: " << c.color ;

	inFile.close();
	rep.close();
}

bool report()
{
	//open binary file for reading
	std::ifstream inFile(DECKS_FILE, std::ios::in | std::ios::binary);
	if (!inFile)
	{
		reportWithoutDecks();
		inFile.close();
		return false;
	}
	std::ofstream rep(REPORT_FILE, std::ios::out); 
	if (!rep)
	{
		std::cerr << "Error. File not open." << std::endl;
		rep.close();
		return false;
	}

	Deck temp;
	int countCards[MAX_NUMBER_OF_IDS] = { 0, };

	for (int i = 0; i < NUMBER_OF_COLORS; i++)
	{
		rep << colors[i] << std::endl;

		while (inFile){
			
			inFile.read((char*)&temp, sizeof(temp));
			if (!inFile) break;
			if (temp.color == i) {
				rep	 << "\tOwner: " << temp.player.name 
				 << " Card: " << temp.card[0].name 
				 << " Color: " << temp.card[0].color << endl;
				
				for (int i = 0; i < DECK_SIZE; i++)
				{
					int id = temp.card[i].ID;
					if (id < 0)
						return false;

					countCards[id]++;
				}
			}
		}

		inFile.clear();
		inFile.seekg(0, std::ios::beg);
	}

	int max = 0;
	for (int i = 0; i <  MAX_NUMBER_OF_IDS; i++)
	{
		if (countCards[i] > countCards[max]) 
		{
			max = i;
		}
	}
	//countCards[max] is how many times the card with id = max is present

	Card c;
	if (searchCardByID(max, c))
	{
		rep << "Most common card:" << c.name << " Color:" << c.color ;
	}

	inFile.close();
	rep.close();

}

