#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Header_files/SHA1_example.h"
#include "../Header_files/ReadGenome.h"
#include "../Header_files/hashing.h"
#include "../Header_files/try_hashing.h"
#include "../Header_files/CuckooFilter.h"

using namespace std;

int main() {
	//sha1_example();
	
	//string genome = ReadGenome("Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genome.fna");

	//int k = 10;
	//try_hashing(k);
	// read genome

	string whole_genome;
	string genome;
	ifstream genome_file("Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genome.fna");
	vector<vector<uint32_t>> CuckooTable = createCuckooTable(10);
	string a="";
	int counter = 10;
	if (genome_file) {
		while (getline(genome_file, genome)) {
			whole_genome += genome;
			bool inserted = insert(10, 4, CuckooTable, genome.c_str(), 5);
			cout << inserted<<endl;
			counter--;
			a = genome;
			if (counter == 0)
				break;
		}
		cout <<"Search:"<< search(CuckooTable, a.c_str());
	}
	else {
		cout << "Failed to open file!" << endl;
		return -1;
	}

	genome_file.close();


	return 0;
}