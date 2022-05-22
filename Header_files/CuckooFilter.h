#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<vector<uint32_t>> createCuckooTable(int m);

bool insert(int m, int b, vector<vector<uint32_t>>& CuckooTable, const char* genom, int MNK,bool reduced);

bool search(vector<vector<uint32_t>>& CuckooTable, const char* genom);

bool duplicateFilters(vector<uint32_t>& bucket1, vector<uint32_t>& bucket2, uint32_t Ex);

int fingerCount(vector<uint32_t>& bucket);

void insert_in_slot(vector<uint32_t>& bucket, uint32_t h);

uint32_t kick_from_slot(vector<uint32_t>& bucket, uint32_t Ex);

bool full_bucket(vector<uint32_t>& bucket, int b);