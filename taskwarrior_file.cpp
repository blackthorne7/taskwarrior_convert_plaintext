// todo: finish commenting
// rename urgency - priority

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// function declarations
void taskAddCmd(string, char, string); // runs task add
string getFileLocation(); // returns todo file location
int vectorOrFile(); // returns whether user wants vector or file
void vectorMethod(); // vector method
void fileMethod(); // file method
void sedDelete(); // runs sed delete on file line
void makeFileBackup(string);
void getUrgency(string, string);
//const string FILE_LOCATION = getFileLocation();
const string FILE_LOCATION = "./tasks.txt";

int main() {

	int whichProcess = vectorOrFile();
	if (whichProcess == 1) {
		vectorMethod();
	}
	else if (whichProcess == 2)
		fileMethod();
}

void vectorMethod() {
	ifstream fin(FILE_LOCATION);

	vector<string> taskList;
	string line;
	string due_date;

	// fills vector with tasks from file
	while (getline(fin, line)) { 
		taskList.push_back(line);
	}

	cout << "\nTERMINAL: tasks stored to vector\n\n";

	for (int i = 0; i < taskList.size(); i++) {
		string storeLine = taskList[i];
		
		getUrgency(due_date, storeLine);
	}

	cout << "TERMINAL: task adding complete";

	fin.close();
}

void fileMethod() {
	string location = getFileLocation();
	makeFileBackup(location);
	ifstream fin(location); // opens text file containing tasks to be processed and added

	string line;
	string storeLine;
	string due_date;

	cout << "\nTERMINAL: file processing started\n\n";

	while (getline(fin, line)) { // reads the next line in the file
		storeLine = line;

		getUrgency(due_date, storeLine);
	}

	cout << "\nTERMINAL: task adding complete\n";
	fin.close();
	cout << "\nTERMINAL: file processing complete\n\n";
}

string getFileLocation() {
	string location;
	cout << "Please enter the todo file location: ";
	getline(cin, location);

	return location;
}

int vectorOrFile() {
	int input;

	cout << "\nProcess 1 (vector method) or Process 2 (file method): ";
	cin >> input;
	cin.ignore();
	return input;
}

void getUrgency(string due_date, string storeLine) {
	string urgency_str;
	char urgency_char;
	
	cout << storeLine << endl;
	
	cout << "QUERY: enter urgency (H, M, L, , Q for quit): "; // 
	getline(cin, urgency_str);

	urgency_char = urgency_str[0]; 
	urgency_char = toupper(urgency_char);

	switch (urgency_char) {
		case 'H':
		case 'M':
		case 'L':
			cout << "QUERY: enter due date: ";
			getline(cin, due_date);
			cout << endl;

			if (due_date == "Q" || due_date == "q") {
				exit(1);
			}
			taskAddCmd(storeLine, urgency_char, due_date);
			break;
		
		case 'Q': 
			cout << "\n\nABORTING\n";	
			exit(1);
	}
}


void makeFileBackup(string location) {
	cout << "\nTERMINAL: making file backup\n";
	string backupLocation = location + ".bak";
	string copyFile = "cp " + location + " " + backupLocation; 
	//system(copyFile);
}

void taskAddCmd(string storeLine, char urgency_char, string due_date) {

	string str = "task add priority:" ;
	str += urgency_char;
	str += " \"" + storeLine + "\" " + "due:" + due_date;

	const char* command = str.c_str();
	cout << "echo " << str << endl;
	//system(command);
	cout << "\nTERMINAL: task added\n";
}

void sedDelete() {
	string sed = "echo sed -i 1d " + FILE_LOCATION;
	const char* sed_del = sed.c_str();
	//system(sed_del);
	cout << endl << sed << endl;
	cout << "TERMINAL: line deleted\n\n";
}

