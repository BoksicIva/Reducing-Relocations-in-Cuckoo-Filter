#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <numeric>
#include "../Header_files/hashing.h"
#include "../Header_files/ReadGenome.h"
#include "../Header_files/implementation.h"
#include "../Header_files/CuckooFilter.h"

using namespace std;
using namespace std::chrono;

vector<vector<uint32_t>> build_cuckoo_table(int k, string filename, int rows, int columns, int mnk, bool reduced) {
	// a file for saving results
	fstream output;

	// read genome
	string whole_genome = ReadGenome(filename);

	// create cuckoo table 
	vector<vector<uint32_t>> CuckooTable = createCuckooTable(rows);

	// number of k-mers
	int num_k_mers = 0;

	// insertion time vector
	vector<long long> insertion_time_vector;

	// total number of relocations of cuckoo filtering
	int num_reloc = 0;

	for (int i = 0; i < whole_genome.length()-k; i++) {
		// take k-mers of size k
		string k_mer = whole_genome.substr(i, k);
		num_k_mers++;

		// insert into cuckoo table
		auto start = high_resolution_clock::now();
		bool inserted = insert(rows, columns, CuckooTable, k_mer.c_str(), mnk, reduced, num_reloc);
		auto stop = high_resolution_clock::now();
		auto insertion_time = duration_cast<microseconds>(stop - start).count();

		insertion_time_vector.push_back(insertion_time);

	}

	// load factor
	float load_factor = 0.0;
	for (vector<uint32_t> v : CuckooTable) {
		for (uint32_t i : v) {
			load_factor++;
		}
	}

	// save output to a file
	output.open("output.csv", ios::out | ios::app);
	output << k << ","
		<< rows << ","
		<< columns << ","
		<< mnk << ","
		<< reduced << ","
		<< static_cast<int>(load_factor) << "," // number of inserted k-mers
		<< num_k_mers << "," // number of k-mers of size k
		<< (load_factor / num_k_mers) * 100 << ","; // % of k_mers that were inserted

	cout << "Number of k-mers of size " << k  << ": " << num_k_mers << endl;
	cout << "Number of inserted k-mers:   " << int(load_factor) << endl;
	cout << (load_factor / num_k_mers) * 100 << "% of k_mers were inserted." << endl;

	// average insertion time
	float average_insertion_time = 0.0;

	if (!insertion_time_vector.empty()) {
		auto const count = static_cast<float>(insertion_time_vector.size());
		average_insertion_time = accumulate(insertion_time_vector.begin(), insertion_time_vector.end(), 0.0) / count;
	}

	output << average_insertion_time << ",";
	cout << endl;
	cout << "Average insertion time: " << average_insertion_time << " ms" << endl;

	load_factor = load_factor / (rows * columns);
	output << load_factor * 100 << ","; // load factor 
	cout << "Load factor: " << load_factor * 100 << "%" << endl;


	// Number of relocations
	output << num_reloc << "\n";
	cout << "Number of relocations: " << num_reloc << endl;


	output.close();

	return CuckooTable;
}

void search_for_random_k_mers(int k, int num_of_random_k_mers, string filename, vector<vector<uint32_t>> CuckooTable) {
	// a file for saving results
	fstream output;

	// read genome
	string whole_genome = ReadGenome(filename);
	srand(time(0));

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

	// save output to a file
	output.open("output_search.csv", ios::out | ios::app);

	output << k << ","
		<< num_found << "," // number of found k-mers
		<< num_of_random_k_mers << ","
		<< (num_found / num_of_random_k_mers) * 100 // % of random k_mers that were found
		<< "\n";

	cout << endl;
	cout << "Number of searched k-mers of size " << k << ": " << num_of_random_k_mers << endl;
	cout << "Number of found k-mers:               " << num_found << endl;
	cout << (num_found / num_of_random_k_mers) * 100 << "% of random k_mers were found." << endl;
}

void implementation(string filename, int k, int rows, int columns, int mnk, int num_of_random_k_mers, bool reduced) {
	// build the cuckoo table
	vector<vector<uint32_t>> CuckooTable = build_cuckoo_table(k, filename, rows, columns, mnk, reduced);

	// search
	search_for_random_k_mers(k, num_of_random_k_mers, filename, CuckooTable);
}
