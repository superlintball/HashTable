/*
 * Author Raveen Karnik
 * Date: 6-3-18
 * This program allows a user to add and remove students from a list of students stored in a hash table.
 * The students are randomly generated from a list of names.
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Generator.h"
using namespace std;

//struct to define student
struct Student
{
	char* fName;
	char* lName;
	int id;
	double gpa;
	Student(char* firstName, char* lastName, int stID, double stGPA)
	{
		fName = firstName;
		lName = lastName;
		id = stID;
		gpa = stGPA;
	}
};

//struct to define a student-carrying node
struct Node
{
	Student* student;
	Node* next = NULL;
	Node(Student* st)
	{
		student = st;
	}
	~Node()
	{
		delete student;
	}
};

//uses student's id as an input to return a random location to store it in the hash table
int hashReturn(int input, int size)
{
	/* Thank you to user Thomas Mueller on stackoverflow
	 * at https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
	 * for the hash function being used*/
	unsigned int toHash = static_cast<unsigned int>(input);
	toHash = ((toHash >> 16) ^ toHash) * 0x45d9f3b;
    toHash = ((toHash >> 16) ^ toHash) * 0x45d9f3b;
    toHash = (toHash >> 16) ^ toHash;
	toHash = toHash % size;
	return static_cast<int>(toHash);
}

//check if either more than half the table is full or if there are at least 3 collisions in the given index
bool reHashNeeded(Node* hashTable[], int indices, int size, int index)
{
	if(indices >= size/2) return true;
	
	else if(!hashTable[index]) return false;
	
	else if(!hashTable[index]->next) return false;
	
	else if(!hashTable[index]->next->next) return false;
	
	return true;
}

//add student function
Node** addStudent(Node* hashTable[], int &indices, Generator* gen, int &size)
{
	cout << endl;
	//prompt the user for the number of students being added
	cout << "How many students would you like to add?\n";
	int num = 0;
	cin >> num;
	
	//methodically go through and add them
	for(int i = 0; i < num; i++)
	{
		//generate a new student and figure out where to store it
		Student* s = new Student(gen->firstName(), gen->lastName(), gen->id(), gen->gpa());
		int index = hashReturn(s->id, size);
		Node* n = new Node(s);
		
		//check if the table needs to be remade
		if(!reHashNeeded(hashTable, indices, size, index))
		{
			//if the table doesn't need to be remade
			
			//if there are no collisions at the index
			if(!hashTable[index])
			{
				hashTable[index] = n;
				indices++;
			}
			//if there is one collision
			else if(!hashTable[index]->next)
			{
				hashTable[index]->next = n;
			}
			//if there are two collisions
			else if(!hashTable[index]->next->next)
			{
				hashTable[index]->next->next = n;
			}
		}
		//if the table does need to be remade
		else
		{
			//reset the number of indices in use to 0
			indices = 0;
			
			//double the size of the table
			size *= 2;
			cout << "Just changed the size to: " << size << endl;
			Node* newHash[size];
			for(int j = 0; j < size; j++)
				newHash[j] = NULL;
			
			//go through the old table and hash all the nodes into the new table
			for(int j = 0; j < size/2; j++)
			{
				if(hashTable[j])
				{
					Node* current = hashTable[j];
					while(current)
					{
						int newIndex = hashReturn(current->student->id, size);
						if(!newHash[newIndex])
						{
							newHash[newIndex] = current;
							indices++;
						} else if(!newHash[newIndex]->next)
						{
							newHash[newIndex]->next = current;
						} else if(!newHash[newIndex]->next->next)
						{
							newHash[newIndex]->next->next = current;
						}
						Node* temp = current;
						current = current->next;
						temp->next = NULL;
					}
				}
			}
			
			//remap the old hash table to the new one and delete the old one
			Node** old = hashTable;
			hashTable = newHash;
			delete *old;
		}
	}
	
	return hashTable;
}

//go through all students and print their information
void printStudents(Node* hashTable[], int size)
{
	cout << endl;
	for(int i = 0; i < size; i++)
	{
		if(hashTable[i])
		{
			Node* current = hashTable[i];
			while(current)
			{
				Student* s = current->student;
				cout << s->fName << endl;
				cout << s->lName << endl;
				cout << "ID: " << s->id << endl;
				cout << "GPA: " << setprecision(2) << fixed << s->gpa << endl << endl;
				current = current->next;
			}
		}
	}
}

//delete student function; boolean so user can know if the student was deleted
bool deleteStudent(Node* hashTable[], int size)
{
	//prompt user for id of student to be deleted, then iterate through
	cout << "Enter ID number of student to be deleted." << endl;
	int deleteId;
	cin >> deleteId;
	cout << endl;
	
	int index = hashReturn(deleteId, size);
	Node* current = hashTable[index];
	
	//look through the linked list at the index for the student with that id
	//keep track of how many students you went through to get there
	int collisions = 0;
	while(current)
	{
		if(current->student->id == deleteId)
			break;
		current = current->next;
		collisions++;
	}
	
	//if the student was found
	if(current)
	{
		//move the student out of the list
		if(collisions == 0)
		{
			hashTable[index] = current->next;
		}
		else if(collisions == 1)
		{
			hashTable[index]->next = current->next;
		}
		else if(collisions == 2)
		{
			hashTable[index]->next->next = current->next;
		}
		
		delete current;
		return true;
	}
	//return false if no matching student was found
	return false;
}

//main code block
int main()
{	
	//define variables to be used
	vector<Student*> studentList();
	
	Node* hashTable[128];
	for(int i = 0; i < 128; i++)
		hashTable[i] = NULL;
	
	int indices = 0;
	Generator* gen = new Generator();
	int size = 128;
	char input[8];

	//general loop to stay true until the user signals to quit
	bool keepGoing = true;
	while(keepGoing)
	{
		//prompt user to add, print, or delete student(s), calling the corresponding function
		cout << "\"ADD\", \"PRINT\", or \"DELETE\" student(s)?" << endl;
		cout << "Type \"QUIT\" to exit." << endl;
		cin >> input;

		//if the user wants to add a student, add that student and print that they have been added
		if(strcmp(input, "ADD") == 0 || strcmp(input, "add") == 0)
		{
			addStudent(hashTable, indices, gen, size);
			cout << "Student(s) Added." << endl << endl;
		}
		
		//if the user wants to prints students, print them all and notify when complete
		else if(strcmp(input, "PRINT") == 0 || strcmp(input, "print") == 0)
		{
			printStudents(hashTable, size);
			cout << "All Students Printed." << endl << endl;
		} 
		
		//if the user wants to delete a student, attempt to delete that student
		else if(strcmp(input, "DELETE") == 0 || strcmp(input, "delete") == 0)
		{
			//depending on what deleteStudent returns, notify the user of what happened
			if(deleteStudent(hashTable, size))
			{
				cout << "Selected Student Deleted." << endl << endl;
			} else
			{
				cout << "Given Student Was Not Found." << endl << endl;
			}
		}
		
		//if the user wants to quit, set the boolean to false, closing the while loop
		else if(strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0)
		{
			keepGoing = false;
		}
		
		//indicate confusion with any other input
		else
		{
			cout << "Sorry, I couldn't understand that." << endl << endl;
		}
	}
	return 0;
}
