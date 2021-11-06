#include <iostream>
#include <string> 
#include <math.h>

using namespace std;

class Course { //Create a class that include the course information
public:
	int collision=0;
	string Courseid;
	int Credits;
	int Capacity;
	string Days;
	string Time;
};

class hashtable { //the hastable include the pointer of course and the length of hashtable
public:
	Course* t;

	int length;

	int hash(string a); //initialize the hash function

	hashtable(int tablelength = 10); //initialize the table length if no length

	bool insertElement(Course* newcourse); //insertelement function use for insert the course

	int searchElement(string id); //searching the course in the table
};
bool insertCourse(string info); //the function for assign the element into the new course
bool changeElement(string CourseInfo); //the function for change the capacity of the course
void printtable(); //print the table
hashtable table; //initialize the table	
int tablesize; //initialize the tablesize
