/*
 * Author Raveen Karnik
 * Date: 6-3-18
 * This program allows a user to add and remove students from a list of students stored in a hash table.
 * The students are randomly generated from a list of names.
 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "Generator.h"
#include "HashTable.h"

using namespace std;

//main code block
int main()
{
	HashTable table;
	Generator* gen = new Generator();
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
			cout << endl;
			//prompt the user for the number of students being added
			cout << "How many students would you like to add?\n";
			int num = 0;
			cin >> num;
			for(int i = 0; i < num; i++)
			{
				table.add(gen->firstName(), gen->lastName(), gen->id(), gen->gpa());
			}
			cout << "Student(s) Added." << endl << endl;
		}
		
		//if the user wants to prints students, print them all and notify when complete
		else if(strcmp(input, "PRINT") == 0 || strcmp(input, "print") == 0)
		{
			table.print();
			cout << "All Students Printed." << endl << endl;
		} 
		
		//if the user wants to delete a student, attempt to delete that student
		else if(strcmp(input, "DELETE") == 0 || strcmp(input, "delete") == 0)
		{
			//prompt user for id of student to be deleted, then iterate through
			cout << "Enter ID number of student to be deleted." << endl;
			int deleteId;
			cin >> deleteId;
			cout << endl;
			
			//depending on what deleteStudent returns, notify the user of what happened
			if(table.remove(deleteId))
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
