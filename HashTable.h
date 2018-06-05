#ifndef HASHTABLEH
#define HASHTABLEH

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

//struct to define student
struct Student
{
	char* fName;
	char* lName;
	int id;
	double gpa;
	Student(const char* firstName, const char* lastName, int stID, double stGPA)
	{
		fName = strcpy(new char[strlen(firstName)+1],firstName);
		lName = strcpy(new char[strlen(lastName)+1],lastName);
		id = stID;
		gpa = stGPA;
	}
	
	~Student()
	{
		delete[] fName;
		delete[] lName;
	}
	
	void info()
	{
		cout << fName << "\n" << lName << "\n#" << id << "\n" << setprecision(2) << fixed << gpa << endl << endl;
	}
};

//struct to define a student-carrying node
struct Node
{
	Student* student;
	Node* next = NULL;
	Node(Student* st) : student(st), next(0) {}
	~Node(){}
};

//class hash table to store all of the functions a hash table should be able to do
class HashTable
{
	public:
		HashTable();
		~HashTable();
		
		Student* find(int stID);
		void add(char* firstName, char* lastName, int stID, double stGPA);
		void add(Student* st);
		bool remove(int stID);
		void print();
		
	private:
		Node** table;
		int size;
		int hash(int stID);
};

#endif