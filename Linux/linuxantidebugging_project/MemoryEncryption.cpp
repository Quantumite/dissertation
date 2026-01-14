#include "BaseTest.hpp"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

typedef struct _cipher_params_t {
	uint8_t *key;
	uint8_t *iv;
	uint32_t encrypt;
	const EVP_CIPHER *cipher_type;
} cipher_params_t;

static uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

static uint8_t key[] = "abcd1234wxyz9999++--//bananastop";

int32_t encrypt_decrypt(cipher_params_t *params, uint8_t *input, uint8_t *output)
{
	int cipher_block_size = EVP_CIPHER_block_size(params->cipher_type);
	EVP_CIPHER_CTX *ctx;
	int numBytesRead, out_len;

	ctx = EVP_CIPHER_CTX_new();
	if(!ctx)
	{
		std::cout << "Unable to get new encryption context (ctx)." << std::endl;
		return -1;
	}

	if(!EVP_CipherInit_ex(ctx, params->cipher_type, NULL, NULL, NULL, params->encrypt))
	{
		std::cout << "Failed to initialize cipher context" << std::endl;
	}

	OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == AES_BLOCK_SIZE);

	if(!EVP_CipherInit_ex(ctx, NULL, NULL, params->key, params->iv, params->encrypt))
	{
		std::cout << "Failed to initialize key and iv in ctx." << std::endl;
		EVP_CIPHER_CTX_cleanup(ctx);
	}
	
	if(!EVP_CipherUpdate(ctx, output, &out_len, input, BUFSIZE))
	{
		std::cout << "Unable to update cipher context with data" << std::endl;
		EVP_CIPHER_CTX_cleanup(ctx);
		return -1;
	}

	//cipher final block
	if(!EVP_CipherFinal_ex(ctx, output, &out_len))
	{
		std::cout << "Failed to update cipher final block" << std::endl;
		EVP_CIPHER_CTX_cleanup(ctx);
		return -1;
	}
	return 0;
}

void ValidateMemoryEncryptionTest(void)
{
	std::vector<uint8_t> iDataVector = std::vector<uint8_t>(BUFSIZE);
	std::vector<uint8_t> encryptedDataVector = std::vector<uint8_t>(BUFSIZE+AES_BLOCK_SIZE);
	std::string functionName = std::string("MemoryEncryptionTest");
	int32_t status = 0;
	uint8_t tmp = 0;

	//Initialize Data
	for(size_t i=0; i < BUFSIZE; i++)
	{
		iDataVector.push_back((i+0x30) % 0x7F);
	}
	
	
	cipher_params_t *params = (cipher_params_t *)malloc(sizeof(cipher_params_t));
	if(!params)
	{
		std::cout << "Unable to allocate memory" << std::endl;
		return;
	}

	params->key = key;
	params->iv = iv;

	//encrypt data initially
	params->encrypt = 1;
	params->cipher_type = EVP_aes_256_cbc();
	status = encrypt_decrypt(params, iDataVector.data(), encryptedDataVector.data());

	ResearchTimer r(functionName+" (Total)");
	for(size_t i=0; i < BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);

		//Decrypt
		params->encrypt = 0;
		status = encrypt_decrypt(params, encryptedDataVector.data(), iDataVector.data());

		//use data
		for(size_t j=0; j < 1024; j++)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp*j) % 1024;
			iDataVector.at(i) = tmp;
		}

		//Encrypt
		params->encrypt = 1;
		status = encrypt_decrypt(params, iDataVector.data(), encryptedDataVector.data());
		
		r2.stop();
	}
	r.stop();
	free(params);
}
