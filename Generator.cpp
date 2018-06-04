#include "Generator.h"

#include <fstream>

using namespace std;

//auto-populates first and last names into an array
Generator::Generator()
{
	srand(time(NULL));
	ifstream stream("firstNames.txt");
	if(stream.is_open())
	{
		int fIndex = 0;
		while(!stream.eof())
		{
			fNames[fIndex] = new char[16];
			stream.getline(fNames[fIndex++], 16);
		}
		stream.close();
	}
	
	stream.open("lastNames.txt");
	if(stream.is_open())
	{
		int lIndex = 0;
		while(!stream.eof())
		{
			lNames[lIndex] = new char[16];
			stream.getline(lNames[lIndex++], 16);
		}
		stream.close();
	}
}

//randomly returns one of the 25 first names
char* Generator::firstName()
{
	return fNames[rand() % 25];
}

//randomly returns one of the 25 last names
char* Generator::lastName()
{
	return lNames[rand() % 25];
}

//returns the next id
int Generator::id()
{
	return currentId++;
}

//returns a random number between 0.1 and 4.0
double Generator::gpa()
{
	return (static_cast<double>(rand() % 400 + 1)/100);
}