#include <openssl/sha.h>

union Casting {
	uint32_t binary_format;
	unsigned char char_format[SHA_DIGEST_LENGTH];
};

struct hashes_struct {
	uint32_t h1;
	uint32_t h2;
	uint32_t fingerprint;
};

struct 	hashes_struct get_hashes(const char* genom);