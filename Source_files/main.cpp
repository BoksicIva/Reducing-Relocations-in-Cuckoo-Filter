#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Header_files/SHA1_example.h"
#include "../Header_files/GENOM_example.h"
#include "../Header_files/hashing.h"
#include "../Header_files/try_hashing.h"
#include "../Header_files/CuckooFilter.h"

using namespace std;

int main() {
	//sha1_example();
	
	//GENOM_example();

	//int k = 10;
	//try_hashing(k);
	// read genom

	string whole_genom;
	string genom;
	ifstream genom_file("Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genom.fna");
	vector<vector<uint32_t>> CuckooTable = createCuckooTable(10);
	int counter = 10;
	if (genom_file) {
		while (getline(genom_file, genom)) {
			whole_genom += genom;
			bool inserted = insert(10, 4, CuckooTable, genom.c_str(), 5);
			cout << inserted;
			counter--;
			if (counter == 0)
				break;
		}
	}
	else {
		cout << "Failed to open file!" << endl;
		return -1;
	}

	genom_file.close();


	return 0;
}