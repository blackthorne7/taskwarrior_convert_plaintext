// this version of the program reads in lines from the file and deletes each line from the file after it executes that as a "task add"

// todo: finish commenting
// merge file and vector, ask user if they want to delete file or not
// line storeLine
// rename urgency - priority
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// function declarations
void taskAddCmd(string, char, string); // runs task add
string fileLocation(); // returns todo file location
int vectorOrFile(); // returns whether user wants vector or file
void vectorMethod(); // vector method
void fileMethod(); // file method
void sedDelete(); // runs sed delete on file line

void fileMethod() {
	ifstream fin(fileLocation()); // opens text file containing tasks to be processed and added

	string line;
	string storeLine;
	string urgency_str;
	char urgency_char;
	string due_date;

	cout << "\nTERMINAL: file processing started\n\n";
	
	while (getline(fin, line)) { // reads the next line in the file
		storeLine = line;

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

	cout << "\nTERMINAL: task adding complete\n";

	fin.close();

	cout << "\nTERMINAL: file processing complete\n\n";

}


int main() {

	int whichProcess = vectorOrFile();
	if (whichProcess == 1)
		void vectorMethod();
	else if (whichProcess == 2)
		void fileMethod();
}

string fileLocation() {
	string location;
	cout << "Please enter the todo file location: ";
	getline(cin, location);
	
	return location;
}

int vectorOrFile() {
	int input;

	cout << "This program has two methods of file processing.\nProcess 1: read-only - the program will read your todo file, and prompt you. No changes will be made to the file - however, if you quit the program without completing processing, the program will not record where you left off.\n Process 2: write - the program will create a backup of your file, then delete each line from your todo file as it processes it.\n Enter 1 or 2: ";
	cin >> input;
	return input;
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
	string sed = "echo sed -i 1d todo.txt";
	const char* sed_del = sed.c_str();
	//system(sed_del);
	cout << endl << sed << endl;
	cout << "TERMINAL: line deleted\n\n";
}

