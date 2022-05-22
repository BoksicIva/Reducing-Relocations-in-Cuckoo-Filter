#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/hashing.h"
#include "../Header_files/try_hashing.h"

using namespace std;

void try_hashing(int k) {
	// read genome
	string whole_genome;
	string genome;
	ifstream genome_file("Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genome.fna");

	if (genome_file) {
		while (getline(genome_file, genome)) {
			whole_genome += genome;
		}
	}
	else {
		cout << "Failed to open file!" << endl;
		return;
	}

	genome_file.close();

	// take k-mers of size k and calculate their h1, fingeprint and h2
	for (int i = 0; i < whole_genome.length(); i++) {
		string k_mer = whole_genome.substr(i, k);

		hashes_struct hashes = get_hashes(k_mer.c_str());

		cout << "h1 = " << hashes.h1 << endl;
		cout << "fingerprint = " << hashes.fingerprint << endl;
		cout << "h2 = " << hashes.h2 << endl;
		cout << endl;
	}
}