#include "HashTable.h"

using namespace std;

//initializes the size to 128
HashTable::HashTable()
{
	size = 128;
	table = new Node*[128];
}

HashTable::~HashTable() {}

//looks for the specific student by ID
Student* HashTable::find(int stID)
{
	//look at the place that the student would be stored
	Node* current = table[hash(stID)];
	
	//go through all the students in the linked list there to determine if they're there
	while(current)
	{
		if(current == 0) return 0;
		else if(current->student->id == stID) return current->student;
		else current = current->next;
	}
}

//add a student to the hash table given their information
void HashTable::add(char* firstName, char* lastName, int stID, double stGPA)
{
	Node** current = &table[hash(stID)];
	int collisions = 0;
	
	//see how many collisions there are
	while(*current != 0)
	{
		current = &(*current)->next;
		collisions++;
	}
	
	//double the size if there are more than three collisions when chaining
	if(collisions >= 3)
	{
		size *= 2;
		Node** old = table;
		table = new Node*[size];
		
		for(int i = 0; i < size/2; i++)
		{
			Node* node = old[i];
			while(node)
			{
				add(node->student);
				node = node->next;
			}
		}
	}
	//if there aren't more than three collisions just add them
	else
	{
		*current = new Node(new Student(firstName, lastName, stID, stGPA));
	}
}

//add student to hash table given student object by accessing data and then calling by info
void HashTable::add(Student* st)
{
	add(st->fName, st->lName, st->id, st->gpa);
	delete st;
}

//remove a student by id, returning whether or not that student was found
bool HashTable::remove(int stID)
{
	//go through the linked list at the logical position
	Node** current = &table[hash(stID)];
	int collisions = 0;
	while(*current != 0)
	{
		//if the student is found
		if((*current)->student->id == stID)
		{
			Node* temp = *current;
			*current = (*current)->next;
			
			//move the student out of the list then delete
			if(collisions == 0)
				table[hash(stID)] = temp->next;
			else if(collisions == 1)
				table[hash(stID)]->next = temp->next;
			else if(collisions == 2)
				table[hash(stID)]->next->next = temp->next;
			
			delete temp;
			return true;
		}
		//if the student is not found, move to the next spot in the list
		else
		{
			*current = (*current)->next;
			collisions++;
		}
	}
	return false;
}

//print out every student in the table
void HashTable::print()
{
	for(int i = 0; i < size; i++)
	{
		Node* current = table[i];
		while(current != 0)
		{
			current->student->info();
			current = current->next;
		}
	}
	
	cout << size << endl;
}

//hash function uses student's id as an input to return a random location to store it in the hash table
int HashTable::hash(int stID)
{
	/* Thank you to user Thomas Mueller on stackoverflow
	 * at https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
	 * for the hash function being used*/
	unsigned int toHash = static_cast<unsigned int>(stID);
	toHash = ((toHash >> 16) ^ toHash) * 0x45d9f3b;
    toHash = ((toHash >> 16) ^ toHash) * 0x45d9f3b;
    toHash = (toHash >> 16) ^ toHash;
	toHash = toHash % size;
	return static_cast<int>(toHash);
}