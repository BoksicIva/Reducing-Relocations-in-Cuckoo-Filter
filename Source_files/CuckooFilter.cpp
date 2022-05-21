#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Header_files/CuckooFilter.h"
#include "../Header_files/hashing.h"

using namespace std;

/// <summary>
/// Funtion creates Cuckoo table as 2D vector of “m” rows and “b” columns of uint32_t type.
/// Table is used for storing segments "fingerprints" that are results of hashinf funtion.
/// 
/// By: Iva Bokšić
/// </summary>
/// <param name="m">The number of buckets in the Cuckoo filter </param>
/// <param name="b"> the number of entries in each bucket </param>
/// <returns>Function returns pointer to CuckooTable of type vector of vector of uint32_t type</returns>
vector<vector<uint32_t>> createCuckooTable(int m) {
	vector<vector<uint32_t>> CuckooTable(m);		
	return CuckooTable;
}

/// <summary>
/// Funtion inseerts fingerprint of test segment into entries of bucket in Cuckoo Table. 
/// There are 3 cases of insertion: 
/// 
///		1)Both buckets have empty entries
///     -> the fingerprint will be stored in a randomly chosen bucket.
/// 
///		2)Only one bucket has empty entries
///		-> the fingerprint will be stored in the bucket with empty entries.
/// 
///		3) Both buckets are full
///		-> the Cuckoo filter makes room for the newly inserted 
///       element by randomly selecting and kicking out a fingerprint 
///       stored in either bucket.
/// 
/// By: Iva Bokšić
/// </summary>
/// /// <param name="CuckooTable">Representation of Cuckoo Table </param>
/// <param name="genom">Text segment that needs to be stored into Cuckoo Table</param>
/// <returns>Boolean value if text segment s successfuly stored</returns>
bool insert(int m, int b,vector<vector<uint32_t>> &CuckooTable, const char* genom,int MNK) {
	hashes_struct hashes = get_hashes(genom);
	uint32_t Ex = hashes.fingerprint;
	uint32_t h1_x = hashes.h1;
	uint32_t h2_x = hashes.h2;


	int position1 = h1_x % CuckooTable.size();
	int position2 = h2_x % CuckooTable.size();
	vector<uint32_t>& bucket1 = CuckooTable[position1];
	vector<uint32_t>& bucket2 = CuckooTable[position2];

	if (!duplicateFilters(bucket1, bucket2, Ex)) {
		int count1 = fingerCount(CuckooTable[position1]);
		int count2 = fingerCount(CuckooTable[position2]);

		
		if (!full_bucket(bucket1,b) && !full_bucket(bucket1,b)) {

			if (count1 <= count2) {
				insert_in_slot(bucket1, h1_x);
			}
			else {
				insert_in_slot(bucket2, h2_x);
			}

		}
		else if (!full_bucket(bucket1, b) || !full_bucket(bucket1, b)) {
			if (!full_bucket(bucket1, b)) {
				insert_in_slot(bucket1, h1_x);
			}
			else {
				insert_in_slot(bucket2, h2_x);
			}
		}
		else {
			// relocation process
			int random = rand() % 2;
			uint32_t r = h2_x;
			uint32_t Er;
			vector<uint32_t> kick_from_bucket = bucket2, to_bucket;
			if (random == 1) {
				r = h1_x;
				kick_from_bucket = bucket1;
			}

			
			for (int n = 0; n < MNK; n++) {
				Er = kick_from_slot(kick_from_bucket, Ex);
				int position = (r ^ Er) % b;
				to_bucket = CuckooTable[position];
				if (!full_bucket(to_bucket, b)) {
					insert_in_slot(to_bucket, h1_x);
					return true;
				}
				Ex = Er;
				kick_from_bucket = to_bucket;
			}
			return false;
		}
	}
	vector<uint32_t> bucket444 = CuckooTable[1];
	return true;
	    /// .The victim calculates its alternative
		///		  bucket, and tries to relocate itself to the 
		///		  alternative bucket.If the alternative bucket has empty entries, 
		///		  CF inserts the victim into one of the empty entriesand the 
		///       insertion process ends.Otherwise, such a relocation process 
		///		  continues until the kicked out fingerprint finds an available 
		///       alternative bucket or the number of relocation reaches the 
		///       predefined maximum number, denoted as MNK.
}


//bool get(unsigned char* segment) {

//}


bool duplicateFilters(vector<uint32_t>& bucket1, vector<uint32_t>& bucket2,uint32_t Ex) {

	for (uint32_t fp : bucket1) {
		if (fp == Ex)
			return true;
	}

	for (uint32_t fp : bucket2) {
		if (fp == Ex)
			return true;
	}

	return false;
}

int fingerCount(vector<uint32_t>& bucket) {
	return (int)bucket.size();
}

void insert_in_slot(vector<uint32_t>& bucket, uint32_t h) {
	bucket.insert(bucket.begin() + bucket.size(), h);
}

uint32_t kick_from_slot(vector<uint32_t>& bucket, uint32_t Ex) {
	int r = rand() % bucket.size();
	uint32_t Er = bucket[r];
	bucket[r] = Ex;
	return Er;
}


bool full_bucket(vector<uint32_t>& bucket,int b) {
	return bucket.size() == b;
}