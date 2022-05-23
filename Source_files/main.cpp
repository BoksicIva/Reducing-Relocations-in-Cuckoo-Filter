#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/implementation.h"
#include <typeinfo>
#include <openssl/sha.h>
#include "../Header_files/hashing.h"

using namespace std;

int main() {
	int k = 100;
	int rows = 50000;
	int columns = 100;
	int mnk = 100;
	int num_of_random_k_mers =5000000;
	bool reduced = true;
	string filename = "Reducing-Relocations-in-Cuckoo-Filter/Resource_files/genome.fna";

	implementation(filename, k, rows, columns, mnk, num_of_random_k_mers, reduced);

	return 0;
}