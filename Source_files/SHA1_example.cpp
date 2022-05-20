#include <iostream>
#include <openssl/sha.h>
#include "../Header_files/SHA1_example.h"

using namespace std;

void sha1_example() {
    // prepare parameters for calculating hash
    const unsigned char* to_hash = reinterpret_cast<const unsigned char*>("ACTGGGTCCAA");
    size_t length = strlen((char*)to_hash);
    unsigned char* results = new unsigned char[SHA_DIGEST_LENGTH];

    // calculate hash
    SHA1(to_hash, length, results);

    // print hash
    for (int i = 0; i < 20; i++) {
        printf("%02x ", results[i]);
    }
    printf("\n");

    // try
    const unsigned char* the_same_hash = reinterpret_cast<const unsigned char*>("ACTGGGTCCAA");
    unsigned char* results_same = new unsigned char[SHA_DIGEST_LENGTH];
    SHA1(the_same_hash, length, results_same);

    const unsigned char* different_hash = reinterpret_cast<const unsigned char*>("TTCGAA");
    unsigned char* results_different = new unsigned char[SHA_DIGEST_LENGTH];
    SHA1(different_hash, length, results_different);

    for (int i = 0; i < 20; i++) {
        printf("%02x ", results_same[i]);
    }
    printf("\n");

    for (int i = 0; i < 20; i++) {
        printf("%02x ", results_different[i]);
    }
    printf("\n");
}