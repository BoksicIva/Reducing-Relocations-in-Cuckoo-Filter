#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/GENOM_example.h"

using namespace std;

void GENOM_example() {
	string genom;
	ifstream genom_file("../Resource_files/genom.fna");

	if (getline(genom_file, genom)) {
		cout << genom;
	}
	else {
		cout << "Failed to read file!" << endl;
	}

	genom_file.close();
}