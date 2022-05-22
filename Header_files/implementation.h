#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<vector<uint32_t>> build_cuckoo_table(int k, string filename, int rows, int columns, int mnk, bool reduced);
void search_for_random_k_mers(int k, int num_of_random_k_mers, string filename, vector<vector<uint32_t>> CuckooTable);
void implementation(string filename, int k, int rows, int columns, int mnk, int num_of_random_k_mers, bool reduced);