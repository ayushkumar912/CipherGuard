#ifndef DES_CBC_H
#define DES_CBC_H
#include <openssl/des.h>
#include <iostream>
#include <fstream>
#include <openssl/des.h>
#include <cstring>
void cbc_encrypt_step_by_step(const char* inputFilename, const char* outputFilename, const DES_cblock* key, const DES_cblock* iv);
void cbc_decrypt_step_by_step(const char* inputFilename, const char* outputFilename, const DES_cblock* key, const DES_cblock* iv);
#endif
