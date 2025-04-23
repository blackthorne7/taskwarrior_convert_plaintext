// this version of the program reads in lines from the file and deletes each line from the file after it executes that as a "task add"

// todo: finish commenting
// merge file and vector, ask user if they want to delete file or not
// line storeLine
// rename urgency - priority
//


#include <iostream>
#include <fstream>

using namespace std;

void task_add_cmd(string, char, string); // function declaration

int main() {

	string location; // file location
	cout << "Please enter the todo file location: ";
	getline(cin, location);
	ifstream fin(location); // opens text file containing tasks to be processed and added

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

				task_add_cmd(storeLine, urgency_char, due_date);

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

void task_add_cmd(string storeLine, char urgency_char, string due_date) {

	string str = "echo task add priority:" ;
	str += urgency_char;
	str += " \"" + storeLine + "\" " + "due:" + due_date;

	const char* command = str.c_str();
	cout << "echo " << str << endl;
	system(command);
	
	string sed = "echo sed -i 1d todo.txt";
	const char* sed_del = sed.c_str();
	system(sed_del);
	cout << endl << sed << endl;
	
	cout << "\nTERMINAL: task added\n";
	cout << "TERMINAL: line deleted\n\n";
}

