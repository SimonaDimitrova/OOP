#include "Egg.h"
#include "Basket.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	cout << "Change basket name (name), Add eggs (add), Remove eggs (remove), see a report (report)\n"
		 <<"\tserialize (serialize), deserialize (deserialize) or exit(exit)?\n " << endl;

	Basket b("Na Stavri koshnicata");
	char buff[2000];

	while (true)
	{
		char buffer[7];
		cin.clear();
		cin.sync();
		cin >> buffer;
		cin.ignore();

		if (!strcmp(buffer, "exit"))break;
		else if (!strcmp(buffer, "name")) 
		{
			cout << "Enter the name of the Basket: " << endl; 
			cin.getline(buff, 2000);
			b.setName(buff);
		}
		else if (!strcmp(buffer, "add")) 
		{
			int size;
			cout << "Enter the name of the egg: " << endl;
			cin.getline(buff, 2000);
			cout << "Enter the size of the egg: " << endl;
			cin >> size;
			b.addЕgg(Egg(buff, size));
		}
		else if (!strcmp(buffer, "remove"))
		{
			cout << "Which card to remove?" << endl;
			cin.getline(buff, 2000);
			b.removeEgg(buff);
		}
		else if (!strcmp(buffer, "report"))
		{
			b.print();
			b.report();
		}
		else if (!strcmp(buffer, "serialize"))
		{
			//Object serialization consists of saving the values that are part of an object,
			//mostly the value gotten from declaring a variable of a class. 
			b.serialize("serialization.bin");
		}
		else if (!strcmp(buffer, "deserialize"))
		{
			//Object deserialization consists of reading the already saved values in the binary file
			b.deserialize("serialization.bin");
		}
		else
		{
			std::cerr << "Wrong input!" << endl;
		}
	}
	return 0;
}