#include <iostream>
#include "functions.h"
#include "student.h"

using namespace std;

int main() {
	string operation;
	cin >> operation;
	while (operation != "exit") {
		if (operation == "sequentialSearch") {
			SequentialSearch();
		} 
		else if (operation == "buildIndex") {
			BuildIndex();
		}
		else if (operation == "search") {
			Search();
		}
		else {
			cout << "Invalid operation! \n";
		}
		cin >> operation;
	}
	return 0;
}