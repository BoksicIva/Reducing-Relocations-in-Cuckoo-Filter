#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/GENOM_example.h"

using namespace std;

void GENOM_example() {
	string genom;
	ifstream genom_file("Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genom.fna");

	if (genom_file) {
		cout << genom_file.rdbuf();
	}
	else {
		cout << "Failed to open file!" << endl;
	}

	genom_file.close();
}