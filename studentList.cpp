/*
 * Author Raveen Karnik
 * Date: 10-3-17
 * This program allows user to add and remove students from a list of students
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

struct Node
{
	Student* student;
	Node* next = NULL;
	Node(Student* st)
	{
		student = st;
	}
};

//add student function
void addStudent(Node* hashTable[], int &indices, Generator* gen, int &size)
{
	cout << "How many students would you like to add?\n";
	int num = 0;
	cin >> num;
	
	for(int i = 0; i < num; i++)
	{
		Student* hi = new Student(gen->firstName(), gen->lastName(), gen->id(), gen->gpa());
	}
	
	/*//add new student to end of vector
	stList.push_back(new Student());

	//prompt user for all information on student
	cout << "Enter student's first name." << endl;
	cin >> stList.back()->firstName;
	cout << "Enter student's last name." << endl;
	cin >> stList.back()->lastName;
	cout << "Enter student's ID Number." << endl;
	cin >> stList.back()->id;
	cout << "Enter student's GPA." << endl;
	cin >> stList.back()->gpa;*/
}
/*
//go through all students and print their information
void printStudents(vector<Student*> stList)
{
	//defint iterator to go through vector
	std::vector<Student*>::iterator it;
	for(it = stList.begin(); it != stList.end(); it++)
	{
		// idea from the C++ Forum, answer from user JLBorges
		// http://www.cplusplus.com/forum/general/71342/
		// accesses object position by taking the difference between the iterator and the beginning
		int position = it - stList.begin();

		cout << stList[position]->firstName << " " << stList[position]-> lastName;
		cout << ", " << stList[position]->id << ", " << setprecision(2) << fixed << stList[position]->gpa << endl;
	}
}

//delete student function; boolean so user can know if the student was deleted
bool deleteStudent(vector<Student*> &stList)
{
	//prompt user for id of student to be deleted, then iterate through
	cout << "Enter ID number of student to be deleted." << endl;
	int deleteId;
	cin >> deleteId;
	std::vector<Student*>::iterator it;
	for(it = stList.begin(); it != stList.end(); it++)
	{
		//check each student in the vector for a matching id, and delete if found
		int position = it - stList.begin();
		if(stList[position]->id == deleteId)
		{
			//delete student and return true to indicate the student was deleted
			delete stList[position];
			stList.erase(stList.begin()+position);
			return true;
		}
	}
	//return false if no matching student was found
	return false;
}*/

//main code block
int main()
{	
	srand(time(NULL));
	
	//define variables to be used
	vector<Student*> studentList();
	Node* hashTable[128];
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
			cout << "Student Added." << endl << endl;
		}
		
		//if the user wants to prints students, print them all and notify when complete
		else if(strcmp(input, "PRINT") == 0 || strcmp(input, "print") == 0)
		{
			//printStudents(studentList);
			//cout << "All Students Printed." << endl << endl;
		} 
		
		//if the user wants to delete a student, attempt to delete that student
		else if(strcmp(input, "DELETE") == 0 || strcmp(input, "delete") == 0)
		{
			/*//depending on what deleteStudent returns, notify the user of what happened
			if(deleteStudent(studentList))
			{
				cout << "Selected Student Deleted." << endl << endl;
			} else
			{
				cout << "Given Student was not Found." << endl << endl;
			}*/
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
