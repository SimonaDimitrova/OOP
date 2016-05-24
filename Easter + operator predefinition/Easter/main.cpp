#include "Egg.h"
#include "Basket.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;
/************************************OPERATORS CHECKED IN REPORT!!! *****************************************/
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
			cout << "\n********** REPORT! **********\n" ;

			Basket a("Na Stavri drugata koshnica");
			a.addЕgg(Egg("Egg1", 3));
			a.addЕgg(Egg("Egg2", 2));
			
			cout << "\n\t First basket: " << endl;
			b.print();

			cout << "\n\t Second basket: " << endl;
			a.print();

			cout << "\n\t First egg in first basket (operator []): \n" << b[0].getName() << endl;

			cout << "\n\t Second basket *= 3 :" << endl;
			a *= 3;
			a.print();

			cout << "\n\t First basket /=2.2 :" << endl;
			b /= 2.2; 
			b.print();

			cout << "\n\t Enter the name of an egg from the first basket (operator []): " << endl;
			char buff[2000];
			cin >> buff;
			b[buff];

			char buff2[20000];
			cout << "\n\t Enter a string for the second basket (operator +=): " << endl;
			cin >> buff2;
			a += buff2;
			a.print();
			
			cout << "\n\t First basket == second basket? " << endl;
			if (b == a) 
				cout << "Yes. " << endl;
			else
				cout << "No. " << endl;

			cout << "\n\t Second basket += first basket : " << endl;
			a += b;
			a.print();

			cout << "\n\t Second basket %= first basket :" << endl;
			a %= b;
			a.print();
			
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