#include <iostream>
#include <fstream>
#include <string>
#include "../Header_files/ReadGenome.h"

using namespace std;

string ReadGenome(string filename) {
	// read genome
	string whole_genome;
	string genome;
	ifstream genome_file(filename);

	if (genome_file) {
		while (getline(genome_file, genome)) {
			whole_genome += genome;
		}

		genome_file.close();
		return whole_genome;
	}
	else {
		cout << "Failed to open file!" << endl;

		genome_file.close();
		exit(0);
	}
}