#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/implementation.h"

using namespace std;

int main() {
	int k = 10;
	int rows = 10000;
	int columns = 1000;
	int mnk = 100;
	int num_of_random_k_mers = 10000;
	bool reduced = false;
	string filename = "Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genome.fna";

	implementation(filename, k, rows, columns, mnk, num_of_random_k_mers, reduced);

	return 0;
}