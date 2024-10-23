# DES Encryption Project

## Overview
This project implements a Data Encryption Standard (DES) encryption and decryption application using the C++ programming language and OpenSSL. The application generates a random file, encrypts it using a user-provided key, and then decrypts it to verify the integrity of the data.

## Features
- Generates a 4KB file containing random alphanumeric characters.
- Encrypts the file using DES in CBC mode.
- Decrypts the file and verifies that the original and decrypted files match.
- Utilizes SHA-1 hashing to verify file integrity.

## Prerequisites
- C++ compiler (g++)
- OpenSSL library
- Makefile utility


# CipherGuard

CipherGuard is a secure file encryption and decryption application that utilizes the DES (Data Encryption Standard) algorithm. This project is designed to provide an easy way to encrypt and decrypt files using a user-defined key.

## Features

- Generate a 4KB file filled with random alphanumeric characters.
- Calculate and display the SHA1 hash of the original and decrypted files to verify integrity.
- Support for encryption and decryption using DES in CBC (Cipher Block Chaining) mode.
- User-friendly command-line interface for key input.

## Installation

  
## Installation
1. Clone the repository or download the project files.
   ```bash
   git clone https://github.com/ayushkumar912/CipherGuard.git
   ```
2. Ensure you have OpenSSL installed on your system.
    ```bash
   brew install openssl
   ```
3. Navigate to the project directory.

   ```bash
   cd path/to/des_project
   ```

4. Build the project using Makefile.

   ```bash
   make
   ```

## Usage
1. Run the application:

   ```bash
   ./main
   ```

2. The program will:
   - Create a directory named `data`.
   - Generate a random file named `data.txt`.
   - Prompt you for an 8-character DES key for encryption and decryption.
   - Encrypt the generated file and save it as `encrypted.txt`.
   - Decrypt the file and save it as `decrypted.txt`.
   - Display SHA-1 hashes to verify file integrity.

## Clean Up
To clean up generated files and executables, run:

  ```bash
   make clean
  ```

## License
This project is licensed under the Apache License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- This project utilizes the OpenSSL library for encryption and hashing.
- Special thanks to the contributors of the OpenSSL project.

