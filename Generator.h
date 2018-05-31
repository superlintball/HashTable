#ifndef GENERATORH
#define GENERATORH

class Generator
{
	public:
		Generator();
		char* firstName();
		char* lastName();
		int id();
		double gpa();
		
	private:
		char* fNames[25];
		char* lNames[25];
		int currentId = 100001;
};

#endif