#include <iostream>
#include "game.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{	
	while (true)
	{
	
		char buffer[7];
		cout << "Do you want to : \n Create a deck (cd), Create a player (cp), create a card (cc) or see a report (report)? " << endl;
		cin >> buffer;

		cin.clear();
		cin.sync();
		if (!strcmp(buffer, "quit"))
		{
			break;
		}
		isCommand(buffer);
		
	} 

	
	return 0;
}