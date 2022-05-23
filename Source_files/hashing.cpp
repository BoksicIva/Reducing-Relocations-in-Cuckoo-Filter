#include <string>
#include <stdio.h>
#include <string.h>
#include "../Header_files/hashing.h"
#include <openssl/sha.h>
#include <iostream>

using namespace std;     

struct hashes_struct get_hashes(const char* genome) {
	// prepare parameters for calculating hash
	const unsigned char* to_hash = reinterpret_cast<const unsigned char*>(genome);
	size_t length = strlen((char*)to_hash);
	unsigned char* results = new unsigned char[SHA_DIGEST_LENGTH];

	// calculate hash
	SHA1(to_hash, length, results);

	// hash consists of 20 bytes = 160 bits
	// using only 64 bits
	unsigned char* results64 = new unsigned char[8];
	memcpy(results64, results, 8);

	// dividing 64 bits into h1 and fingerprint
	Casting castingH1;
	memcpy(castingH1.char_format, results64, 4);

	Casting castingF;
	memcpy(castingF.char_format, &results64[4], 4);

	// casting h1 and fingerprint to bytes
	hashes_struct hashes;
	hashes.h1 = castingH1.binary_format;
	hashes.fingerprint = castingF.binary_format;

	// calculating h2
	hashes.h2 = hashes.h1 ^ hashes.fingerprint;

	return hashes;
}