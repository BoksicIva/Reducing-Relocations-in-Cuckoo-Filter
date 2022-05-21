#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/hashing.h"
#include "../Header_files/try_hashing.h"

using namespace std;

void try_hashing(int k) {
	// read genom
	string whole_genom;
	string genom;
	ifstream genom_file("Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genom.fna");

	if (genom_file) {
		while (getline(genom_file, genom)) {
			whole_genom += genom;
		}
	}
	else {
		cout << "Failed to open file!" << endl;
		return;
	}

	genom_file.close();

	// take k-mers of size k and calculate their h1, fingeprint and h2
	for (int i = 0; i < whole_genom.length(); i++) {
		string k_mer = whole_genom.substr(i, k);

		hashes_struct hashes = get_hashes(k_mer.c_str());

		cout << "h1 = " << hashes.h1 << endl;
		cout << "fingerprint = " << hashes.fingerprint << endl;
		cout << "h2 = " << hashes.h2 << endl;
		cout << endl;
	}
}