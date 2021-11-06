#include "HashTable.h"

int main() {
retry:
	cout << "Please enter a hash table size: " << endl;
	cin >> tablesize; //prompt user to input the size of hash table and write into the tablesize
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Hash table initialize failed" << endl;
		goto retry; //Error handling for user input other value not integer
	}
	char input;
	string courseinfo, courseid, changecapacity;
	int searchelement;
	table = hashtable(tablesize); //prepare the variable and ready for writing the values from user
	do {
		perform:
		cout << "What action would you like to perform?" << endl;
		cin >> input; //do while loop for user to perform the action
		input = toupper(input); //Error handling to make sure all input can be reconized by switch cases
		switch (input) {
		case 'A':
			cout << "Enter a course information using the format courseId:credits:capacity:days,time" << endl;
			cin >> courseinfo; //wrtie the user's input as a string
			if (!insertCourse(courseinfo)) {
				cout << "The table is full" << endl;
			} //from the insetCourse function, if false, return the table is full
			break;
		case 'B':
			cout << "Enter a courseId" << endl;
			cin >> courseid;
			searchelement = table.searchElement(courseid); //write the user's input a string and assign the string into the searchelement function
			if (searchelement != -1) { //if the return value is not -1, means found the course in the table. print the information of this course
				printf("%s found with credit(s) %d, capacity %d in the days: %s and the time: %s \n", 
					table.t[searchelement].Courseid.c_str(),
					table.t[searchelement].Credits, 
					table.t[searchelement].Capacity, 
					table.t[searchelement].Days.c_str(), 
					table.t[searchelement].Time.c_str());//print the table by using hash value of courseid
			}
			else {
				courseid = courseid.substr(0, courseid.find(':'));
				cout << courseid << " not found" << endl; //if there is no courseid in the table, we take the substring before the : and print not found
			}
;			break;
		case 'C':
			cout << "Enter a courseId and a capacity value to change to using the format courseId:capacity" << endl;
			cin >> changecapacity;
			if (changeElement(changecapacity) == true) {
				changecapacity = changecapacity.substr(0, changecapacity.find(':'));
				cout << changecapacity << " updated" << endl; //If changecapacity function return true, means the course found and updated the capacity
			}
			else {
				changecapacity = changecapacity.substr(0, changecapacity.find(':'));
				cout << changecapacity << " not found" << endl; //if not found, print the courseid and not found
			}
			break;
		case 'D':
			printtable();
			break; 
		default: 
			cout << "Please enter commands  'A', 'B', 'C', 'D', or 'Q'" << endl;
			break; //deafault case for error handling
		}

	} while (input != 'Q');
	delete[] table.t; //when use enter Q, quit the loop and free memory
}

hashtable::hashtable(int length) {
	this->length = length;
	this->t = new Course[length]; //get the length from user and create the new class for hashtable
}
int prime(int number) {
	int j;
	if (number & 1)
		number -= 2; //if the last digit is true means we have odd number, and subtract 2 for the pervious odd number
	else
		number--;//else we subtract 1 for get the pervious odd number
	for (int i = number; i >= 2; i -= 2) {
		for (j = 3;j <= sqrt(i); j += 2) { //looking for the half of the odd number factor
			if (i % j == 0)//if the number can be mod by a odd number, means this odd number is not prime number
				break;//go found the next smaller odd number
		}
		if (j > sqrt(i))//if j is larger than the half of the odd number factor return i
			return i;
	}
	return 2;//else return 2
}

int h1(int key) {
	int h1 = key % tablesize;
	return h1; //use the key mod by table size
}

int h2(int key) {

	int h2 = key % prime(key);
	return h2; //use the key mod by a nearest prime number 
}

int coverter(string id) {
	int sum = 0;
	for (int i = 0;i < id.length();i++) {
		sum += (char)(id[i]) * (i + 1);
	}
	return sum; //convert each character from the string as ascii number and multiply by the number of place. ie. first character multiple 1 second miltiple 2 so on
}

int hashtable::hash(string id) {
	int k = coverter(id); //get the integer of sum of string

	for (int i = 0; i < this->length; i++) {
		int h = (h1(k) + i * h2(k)) % tablesize;
		if (this->t[h].Courseid == "") {
			this->t[h].collision = i;
			return h; //use hash function seaching the table if there is empty place, also return i as collision
		}
		else if (this->t[h].Courseid == id) {
			this->t[h].collision = i;
			return h; //if the input is same as the table return the hash value and collision number
		}
	}
	return -1; //return -1 if the table is full
}

bool hashtable::insertElement(Course* info) {
	
	int h = this->hash(info->Courseid); //assign the hash value from user's input courseid
	if (h != -1 && this->t[h].Courseid == "") {
		this->t[h].Courseid = info->Courseid;
		this->t[h].Credits = info->Credits;
		this->t[h].Capacity = info->Capacity;
		this->t[h].Days = info->Days;
		this->t[h].Time = info->Time;

		return true; // if hash value not -1 (table not full), assign the table of hash value for each course elements
	}
	
	return false; // else return false
}
bool insertCourse(string info) {
	Course* newcourse = new Course; //create a new course and ready for input the information
	
	newcourse -> Courseid = info.substr(0, info.find(':'));// write the beginning of the string until found the :
	info = info.substr(info.find(':') + 1);//delete the front part of the string that include the :

	newcourse->Credits = std::stoi(info.substr(0, info.find(':')));
	info = info.substr(info.find(':') + 1);

	newcourse->Capacity = std::stoi(info.substr(0, info.find(':')));
	info = info.substr(info.find(':') + 1);

	newcourse->Days = info.substr(0, info.find(','));
	info = info.substr(info.find(',') + 1);

	newcourse->Time = info.substr(0); //repeat the process until all information has been wrote into the newcourse
	return table.insertElement(newcourse);//use insertelement to insert the course into the table
}

int hashtable::searchElement(string id) {
	int i = table.hash(id); //get the hash value of the courseid
	if (i > -1 && table.t[i].Courseid == id) {
		return i; //if the has value not equal to -1 and found the hash vlaue in the hashtable has same id from the user's input return the hash value that contain the course
	}
	else return -1; //not found the element
}

bool changeElement(string courseinfo) {
	Course* newcourse = new Course;  //create a newcourse

	newcourse->Courseid = courseinfo.substr(0, courseinfo.find(':'));
	courseinfo = courseinfo.substr(courseinfo.find(':') + 1);//found the courseid from the user's input

	int v = table.searchElement(newcourse->Courseid);//use search function to found the has value of the course id
	if (v != -1) { 
		newcourse->Capacity = std::stoi(courseinfo.substr(0));
		table.t[v].Capacity = newcourse->Capacity;
		return true;//if the hash value not equal to -1, get the rest of substring (which is the capacity that user want to change), and change the hash tbale's capacity of input's course course
	}
	return false;//return false if hash value is -1
}

void printtable() {
	cout << "index collision CrouseId Credits Capacity Days Time" << endl; //print the title 
	for (int i = 0; i < table.length;i++) {
		if (table.t[i].Courseid != "") {
			cout << i << "	";
			cout << table.t[i].collision << "	";
			cout << table.t[i].Courseid << "	";
			cout << table.t[i].Credits << "	";
			cout << table.t[i].Capacity << "	";
			cout << table.t[i].Days << "	";
			cout << table.t[i].Time << endl;
			// print all the element in the table if the index of hashtable is not null
		}
		else {
			cout << i << "	";
			cout << 0 << "	";
			cout << "none" << "	";
			cout << 0 << "	";
			cout << 0 << "	";
			cout << "none" << "	";
			cout << "none" << endl;
		}//if the index of hashtable is null, print 0 and none instead
	}
}
