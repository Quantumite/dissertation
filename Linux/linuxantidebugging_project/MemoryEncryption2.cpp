#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>

#include <openssl/evp.h>
#include <openssl/rand.h>

#include "BaseTest.hpp"

static const unsigned int KEY_SIZE = 32;
static const unsigned int BLOCK_SIZE = 16;

template <typename T>
struct zallocator
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer address (reference v) const {return &v;}
    const_pointer address (const_reference v) const {return &v;}

    pointer allocate (size_type n, const void* hint = 0) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();
        return static_cast<pointer> (::operator new (n * sizeof (value_type)));
    }

    void deallocate(pointer p, size_type n) {
        OPENSSL_cleanse(p, n*sizeof(T));
        ::operator delete(p); 
    }
    
    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof (T);
    }
    
    template<typename U>
    struct rebind
    {
        typedef zallocator<U> other;
    };

    void construct (pointer ptr, const T& val) {
        new (static_cast<T*>(ptr) ) T (val);
    }

    void destroy(pointer ptr) {
        static_cast<T*>(ptr)->~T();
    }

#if __cpluplus >= 201103L
    template<typename U, typename... Args>
    void construct (U* ptr, Args&&  ... args) {
        ::new (static_cast<void*> (ptr) ) U (std::forward<Args> (args)...);
    }

    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
#endif
};

typedef std::basic_string<char, std::char_traits<char>, zallocator<char> > secure_string;
using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

void gen_params(unsigned char key[KEY_SIZE], unsigned char iv[BLOCK_SIZE]);
void aes_encrypt(const unsigned char key[KEY_SIZE], const unsigned char iv[BLOCK_SIZE], const std::vector<uint8_t>& ptext, std::vector<uint8_t>& ctext);
void aes_decrypt(const unsigned char key[KEY_SIZE], const unsigned char iv[BLOCK_SIZE], const std::vector<uint8_t>& ctext, std::vector<uint8_t>& rtext);

// g++ -Wall -std=c++11 evp-encrypt.cxx -o evp-encrypt.exe -lcrypto
void ValidateMemoryEncryptionTest(void)
{
    std::string functionName = std::string("MemoryEncryptionTest");
    // Load the necessary cipher
    EVP_add_cipher(EVP_aes_256_cbc());

    // plaintext, ciphertext, recovered text
    std::vector<uint8_t> iDataVector = std::vector<uint8_t>(BUFSIZE);
    std::vector<uint8_t> encryptedDataVector = std::vector<uint8_t>(BUFSIZE+BLOCK_SIZE);
    size_t tmp = 0;

    //initialize iDAtaVector
    for(size_t i=0; i < BUFSIZE; i++)
    {
	     iDataVector.push_back(i);
    }

    unsigned char key[KEY_SIZE], iv[BLOCK_SIZE];
    gen_params(key, iv);
  
    aes_encrypt(key, iv, iDataVector, encryptedDataVector);
    
    //Do test
    ResearchTimer r(functionName+" (Total)");
    for(size_t i=0; i < BUFSIZE; i++)
    {
	    ResearchTimer r2(functionName);
	    aes_decrypt(key, iv, encryptedDataVector, iDataVector);
	    for(size_t j=0; j < 1024; j++)
	    {
		    tmp = iDataVector.at(i);
		    tmp = (tmp*j) % 1024;
		    iDataVector.at(i) = tmp;
	    }
	    aes_encrypt(key, iv, iDataVector, encryptedDataVector);
	    r2.stop();
    }
    r.stop();

    OPENSSL_cleanse(key, KEY_SIZE);
    OPENSSL_cleanse(iv, BLOCK_SIZE);
}

void gen_params(unsigned char key[KEY_SIZE], unsigned char iv[BLOCK_SIZE])
{
    int rc = RAND_bytes(key, KEY_SIZE);
    if (rc != 1)
      throw std::runtime_error("RAND_bytes key failed");

    rc = RAND_bytes(iv, BLOCK_SIZE);
    if (rc != 1)
      throw std::runtime_error("RAND_bytes for iv failed");
}

void aes_encrypt(const unsigned char key[KEY_SIZE], const unsigned char iv[BLOCK_SIZE], const std::vector<uint8_t>& ptext, std::vector<uint8_t>& ctext)
{
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptInit_ex failed");

    // Recovered text expands upto BLOCK_SIZE
    ctext.resize(ptext.size()+BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

    rc = EVP_EncryptUpdate(ctx.get(), (unsigned char*)&ctext[0], &out_len1, (const unsigned char*)&ptext[0], (int)ptext.size());
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptUpdate failed");
  
    int out_len2 = (int)ctext.size() - out_len1;
    rc = EVP_EncryptFinal_ex(ctx.get(), (unsigned char*)&ctext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptFinal_ex failed");

    // Set cipher text size now that we know it
    ctext.resize(out_len1 + out_len2);
}

void aes_decrypt(const unsigned char key[KEY_SIZE], const unsigned char iv[BLOCK_SIZE], const std::vector<uint8_t>& ctext, std::vector<uint8_t>& rtext)
{
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptInit_ex failed");

    // Recovered text contracts upto BLOCK_SIZE
    rtext.resize(ctext.size());
    int out_len1 = (int)rtext.size();

    rc = EVP_DecryptUpdate(ctx.get(), (unsigned char*)&rtext[0], &out_len1, (const unsigned char*)&ctext[0], (int)ctext.size());
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptUpdate failed");
  
    int out_len2 = (int)rtext.size() - out_len1;
    rc = EVP_DecryptFinal_ex(ctx.get(), (unsigned char*)&rtext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptFinal_ex failed");

    // Set recovered text size now that we know it
    rtext.resize(out_len1 + out_len2);
}

