#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Header_files/hashing.h"
#include "../Header_files/ReadGenome.h"
#include "../Header_files/implementation.h"
#include "../Header_files/CuckooFilter.h"

using namespace std;

vector<vector<uint32_t>> build_cuckoo_table(int k, string filename, int rows, int columns, int mnk) {
	// read genome
	string whole_genome = ReadGenome(filename);

	// create cuckoo table 
	vector<vector<uint32_t>> CuckooTable = createCuckooTable(rows);

	// number of insertions and number of k-mers
	int num_insertions = 0;
	int num_k_mers = 0;

	for (int i = 0; i < whole_genome.length(); i++) {
		// take k-mers of size k
		string k_mer = whole_genome.substr(i, k);
		num_k_mers++;

		// insert into cuckoo table
		bool inserted = insert(rows, columns, CuckooTable, k_mer.c_str(), mnk);

		if (inserted) {
			num_insertions++;
		}
	}

	cout << "Number of k-mers of size " << k  << ": " << num_k_mers << endl;
	cout << "Number of inserted k-mers:   " << num_insertions << endl;
	cout << (num_insertions / num_k_mers) * 100 << "% of k_mers were inserted." << endl;

	return CuckooTable;
}

void search_for_random_k_mers(int k, int num_of_random_k_mers, string filename, vector<vector<uint32_t>> CuckooTable) {
	// read genome
	string whole_genome = ReadGenome(filename);

	// number of found k-mers
	int num_found = 0;

	// search for random k_mers
	for (int i = 0; i < num_of_random_k_mers; i++) {
		// pick a random k_mer
		int random = rand() % (whole_genome.length() - k + 1);
		string k_mer = whole_genome.substr(random, k);
		bool found = search(CuckooTable, k_mer.c_str());

		if (found) {
			num_found++;
		}
	}

	cout << endl;
	cout << "Number of searched k-mers of size " << k << ": " << num_of_random_k_mers << endl;
	cout << "Number of found k-mers:               " << num_found << endl;
	cout << (num_found / num_of_random_k_mers) * 100 << "% of random k_mers were found." << endl;
}

void implementation(string filename, int k, int rows, int columns, int mnk, int num_of_random_k_mers) {
	// build the cuckoo table
	vector<vector<uint32_t>> CuckooTable = build_cuckoo_table(k, filename, rows, columns, mnk);

	// search
	search_for_random_k_mers(k, num_of_random_k_mers, filename, CuckooTable);
}
