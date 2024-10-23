#include "des_cbc.h"
using namespace std;

void cbc_encrypt_step_by_step(const char* inputFilename, const char* outputFilename, const DES_cblock* key, const DES_cblock* iv) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);
    
    if (!inputFile || !outputFile) {
        cerr << "Error opening files for encryption!" << endl;
        exit(1);
    }

    DES_key_schedule keySchedule;
    if (DES_set_key_checked(const_cast<DES_cblock*>(key), &keySchedule) != 0) {
        cerr << "Error setting DES key!" << endl;
        exit(1);
    }

    char inputBlock[8], outputBlock[8], prevBlock[8];
    memcpy(prevBlock, *iv, 8);

    while (inputFile.read(inputBlock, 8) || inputFile.gcount()) {
        int blockSize = inputFile.gcount();

        if (blockSize < 8) {
            memset(inputBlock + blockSize, 8 - blockSize, 8 - blockSize);
        }

        for (int i = 0; i < 8; ++i) {
            inputBlock[i] ^= prevBlock[i];
        }

        DES_ecb_encrypt((DES_cblock*)inputBlock, (DES_cblock*)outputBlock, &keySchedule, DES_ENCRYPT);

        outputFile.write(outputBlock, 8);

        memcpy(prevBlock, outputBlock, 8);
    }

    inputFile.close();
    outputFile.close();
    cout << "File encrypted using DES CBC." << endl;
}

void cbc_decrypt_step_by_step(const char* inputFilename, const char* outputFilename, const DES_cblock* key, const DES_cblock* iv) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);
    
    if (!inputFile || !outputFile) {
        cerr << "Error opening files for decryption!" << endl;
        exit(1);
    }

    DES_key_schedule keySchedule;

    if (DES_set_key_checked(const_cast<DES_cblock*>(key), &keySchedule) != 0) {
        cerr << "Error setting DES key!" << endl;
        exit(1);
    }

    char inputBlock[8], outputBlock[8], prevBlock[8], tempBlock[8];
    memcpy(prevBlock, *iv, 8);  

    while (inputFile.read(inputBlock, 8)) {
       
        DES_ecb_encrypt((DES_cblock*)inputBlock, (DES_cblock*)outputBlock, &keySchedule, DES_DECRYPT);

        memcpy(tempBlock, inputBlock, 8);

        for (int i = 0; i < 8; ++i) {
            outputBlock[i] ^= prevBlock[i];
        }

        outputFile.write(outputBlock, 8);

        memcpy(prevBlock, tempBlock, 8);
    }

    inputFile.close();
    outputFile.close();
    cout << "File decrypted using DES CBC." << endl;
}
