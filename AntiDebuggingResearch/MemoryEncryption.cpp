//Thanks to https://learn.microsoft.com/en-us/windows/win32/seccng/encrypting-data-with-cng

#include <vector>
#include <string>
#include <iostream>
#include "BaseTest.hpp"
#include <bcrypt.h>
#include <Windows.h>
#include "memoryencryption.hpp"
#include "BaseFunction.hpp"

static const BYTE rgbIV[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

static const BYTE rgbAES128Key[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

Misc::MemoryEncryptionTest::MemoryEncryptionTest()
{
    lf = LogFile("memoryencryption.log", "Misc", "MemoryEncryption");
}

void Misc::MemoryEncryptionTest::RunTest(void)
{
    

    //Initialize Buffer
    std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
    std::vector<size_t> encryptedDataVector = std::vector<size_t>(BUFSIZE);
    size_t tmp = 0;
    AntiDebuggingTimer adt = AntiDebuggingTimer();
    BCRYPT_ALG_HANDLE hAlgorithmHandle = NULL;
    BCRYPT_KEY_HANDLE hKeyHandle = NULL;
    BYTE pSecret[] = "alphabetsoup";
    ULONG encryptionResults;
    ULONG cbKeyObject = 0;
    ULONG cbData = 0;
    ULONG cbBlockLen = 0;

    //Initialize provider using AES algorithm with no cryptographic primitive provider (NULL) and no flags (0)
    NTSTATUS status = BCryptOpenAlgorithmProvider(&hAlgorithmHandle, BCRYPT_AES_ALGORITHM, NULL, 0);
    if (!BCRYPT_SUCCESS(status))
    {
        std::cout << "Unable to initialize encryption algorithm provider." << std::endl;
        return;
    }

    // Calculate the size of the buffer to hold the KeyObject.
    status = BCryptGetProperty(hAlgorithmHandle, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbKeyObject, sizeof(DWORD), &cbData, 0);
    if (!BCRYPT_SUCCESS(status))
    {
        std::cout << "Unable to get property BCRYPT_OBJECT_LENGTH. Status=" << std::hex << status << std::endl;
        return;
    }

    // Allocate the key object on the heap.
    std::vector<BYTE> pbKeyObject = std::vector<BYTE>(cbKeyObject);

    // Calculate the block length for the IV.
    status = BCryptGetProperty(hAlgorithmHandle, BCRYPT_BLOCK_LENGTH, (PBYTE)&cbBlockLen, sizeof(DWORD), &cbData, 0);
    if (!BCRYPT_SUCCESS(status))
    {
        std::cout << "Unable to get property BCRYPT_OBJECT_LENGTH. Status=" << std::hex << status << std::endl;
        return;
    }

    // Determine whether the cbBlockLen is not longer than the IV length.
    if (cbBlockLen > sizeof(rgbIV))
    {
        std::cout << "block length is longer than the provided IV length" << std::endl;
        return;
    }

    // Allocate a buffer for the IV. The buffer is consumed during the 
    // encrypt/decrypt process.
    std::vector<BYTE> pbIV = std::vector<BYTE>(cbBlockLen);

    memcpy(pbIV.data(), rgbIV, cbBlockLen);

    status = BCryptSetProperty(hAlgorithmHandle, BCRYPT_CHAINING_MODE, (PBYTE)BCRYPT_CHAIN_MODE_CBC, sizeof(BCRYPT_CHAIN_MODE_CBC), 0);
    if (!BCRYPT_SUCCESS(status))
    {
        std::cout << "Error returned by BCryptSetProperty. status = " << std::hex << status << std::endl;
        return;
    }

    // Generate the key from supplied input key bytes.
    status = BCryptGenerateSymmetricKey(
        hAlgorithmHandle,
        &hKeyHandle,
        pbKeyObject.data(),
        cbKeyObject,
        (PBYTE)rgbAES128Key,
        sizeof(rgbAES128Key),
        0);

    if (!BCRYPT_SUCCESS(status))
    {
        std::cout << "Error returned by BCryptGenerateSymmetricKey. status = " << std::hex << status << std::endl;
        return;
    }

    //Initial encryption of the data. This would likely be done before distribution of the binary so it will be done before
    // we start measuring the anti-debugging technique.
    status = BCryptEncrypt(
        hKeyHandle, //key handle
        reinterpret_cast<PUCHAR>(iDataVector.data()), //plaintext data
        BUFSIZE, //size of plaintext data
        NULL, //padding info
        pbIV.data(), //initialization vector, none used for this example
        cbBlockLen, //size of initialization vector, none used for this example
        reinterpret_cast<PUCHAR>(encryptedDataVector.data()), //encrypted output buffer
        BUFSIZE, //size of encrypted data
        &encryptionResults, //pointer to ULONG for number of bytes copied to encrypted buffer
        0 // flags, none used
    );
    if (!BCRYPT_SUCCESS(status))
    {
        std::cout << "Unable to initially encrypt data. Status=" << std::hex << status << std::endl;
        return;
    }

    //Timing
    for (size_t i = 0; i < LOOPSIZE; i++)
    {
        //Start anti-debugging technique timer
        adt.AntiDebugging_TimeStart();

        //Decrypt data in memory before use
        status = BCryptDecrypt(
            hKeyHandle,
            reinterpret_cast<PUCHAR>(encryptedDataVector.data()),
            BUFSIZE,
            NULL,
            pbIV.data(),
            cbBlockLen,
            reinterpret_cast<PUCHAR>(iDataVector.data()),
            BUFSIZE,
            &encryptionResults,
            0
        );
        if (!BCRYPT_SUCCESS(status))
        {
            std::cout << "Unable to decrypt data. Status = " << std::hex << status << std::endl;
            return;
        }

        //Use data
        BaseFunction5(iDataVector, i);

        //Re-encrypt data after use for protection
        status = BCryptEncrypt(
            hKeyHandle, //key handle
            reinterpret_cast<PUCHAR>(iDataVector.data()), //plaintext data
            BUFSIZE, //size of plaintext data
            NULL, //padding info
            pbIV.data(), //initialization vector, none used for this example
            cbBlockLen, //size of initialization vector, none used for this example
            reinterpret_cast<PUCHAR>(encryptedDataVector.data()), //encrypted output buffer
            BUFSIZE, //size of encrypted data
            &encryptionResults, //pointer to ULONG for number of bytes copied to encrypted buffer
            0 // flags, none used
        );
        if (!BCRYPT_SUCCESS(status))
        {
            std::cout << "Unable to re-encrpyt data. Status = " << std::hex << status << std::endl;
            return;
        }
        adt.AntiDebugging_TimeStop();
        lf.Write(adt.PrintResults(lf));
    }


    //Cleanup
    if (hKeyHandle)
    {
        BCryptDestroyKey(hKeyHandle);
    }

    if (hAlgorithmHandle)
    {
        BCryptCloseAlgorithmProvider(hAlgorithmHandle, 0);
    }

    return;
}