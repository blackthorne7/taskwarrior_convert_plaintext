#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void task_add_cmd(vector<string>, int, char, string);

int main() {
	ifstream fin("todo.txt");

	vector<string> taskList;

	string line;
	string urgency_str;
	char urgency_char;
	string due_date;

	while (getline(fin, line)) {
		taskList.push_back(line);
	}
	
	cout << "\nTERMINAL: tasks stored to vector\n\n";
	
	for (int i = 0; i < taskList.size(); i++) {
		cout << taskList[i] << endl;

		cout << "QUERY: enter urgency (H, M, L, Q for quit): ";
		
		getline(cin, urgency_str);
		
		urgency_char = urgency_str[0];
		urgency_char = toupper(urgency_char);

		switch (urgency_char) {
			case 'H':
			case 'M':
			case 'L':
				cout << "TRUE";
				cout << "QUERY: enter due date: ";
				getline(cin, due_date);
				
				if (due_date == "Q" || due_date == "q") {
					exit(1);
				}

				task_add_cmd(taskList, i, urgency_char, due_date);
				
				break;

			case 'Q': 
				cout << "FALSE";	
				exit(1);

		}
	}

	cout << "TERMINAL: task adding complete";

	fin.close();
}

void task_add_cmd(vector<string> taskList, int i, char urgency_char, string due_date) {

	string str = "echo task add priority:" + urgency_char;
	str += " " + taskList[i] + " " + "due:" + due_date;
	const char* command = str.c_str();
	system(command);
	cout << "\nTERMINAL: task added to taskwarrior\n\n";
}
