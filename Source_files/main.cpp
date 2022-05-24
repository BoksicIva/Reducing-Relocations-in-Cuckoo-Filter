#include <iostream>
#include <string>
#include <cstdlib>
#include "../Header_files/implementation.h"

using namespace std;

/// By: Karolina Mirkovic
int main(int argc, char* argv[]) {
	/*int k = 100;
	int rows = 50000;
	int columns = 100;
	int mnk = 100;
	int num_of_random_k_mers = 5000000;
	bool reduced = true;
	string filename = "Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genome.fna";*/

	if (argc < 8) {
		cout << "Arguments missing!" << endl;
		return -1;
	}

	int k = atoi(argv[1]);
	int rows = atoi(argv[2]);
	int columns = atoi(argv[3]);
	int mnk = atoi(argv[4]);
	int num_of_random_k_mers = atoi(argv[5]);
	bool reduced = bool(argv[6]);
	string filename = argv[7];
	
	implementation(filename, k, rows, columns, mnk, num_of_random_k_mers, reduced);

	cout << "Done!" << endl;
		 
	return 0;
}