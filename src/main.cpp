#include "main.h"
using namespace std;

const int FILE_SIZE = 4096;

void createDirectory(const char* dir) {
    struct stat info;
    if (stat(dir, &info) != 0) {
        if (mkdir(dir, 0755) != 0) {
            cerr << "Error creating directory: " << dir << endl;
            exit(1);
        } else {
            cout << "Directory created: " << dir << endl;
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        cerr << "Error: " << dir << " is not a directory!" << endl;
        exit(1);
    } else {
        cout << "Directory already exists: " << dir << endl;
    }
}

void printCurrentWorkingDirectory() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << "Current working directory: " << cwd << endl;
    } else {
        perror("getcwd() error");
    }
}

void createFile(const char* filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error creating file: " << filename << endl;
        exit(1);
    }

    string charSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string data;

    srand(time(0));

    for (int i = 0; i < FILE_SIZE; ++i) {
        data += charSet[rand() % charSet.length()];
    }

    file << data;
    file.close();
    
    cout << "Step 1: Created 4KB file with random alphanumeric characters at: " << filename << endl;
    cout << "Total characters written: " << data.size() << endl;
    cout << "Sample data (first 50 chars): " << data.substr(0, 50) << endl;
}

string calculateHash(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    SHA_CTX shaContext;
    SHA1_Init(&shaContext);

    string line;
    while (getline(file, line)) {
        SHA1_Update(&shaContext, line.c_str(), line.size());
    }

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &shaContext);
    file.close();

    stringstream ss;  
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

void encryptFile(const char* inputFile, const char* outputFile, DES_key_schedule& keySchedule) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);
    
    if (!inFile || !outFile) {
        cerr << "Error opening file for encryption!" << endl;
        exit(1);
    }

    DES_cblock iv;  
    memset(iv, 0, sizeof(iv));  

    char buffer[8]; 
    while (inFile.read(buffer, sizeof(buffer)) || inFile.gcount() > 0) {
        int bytesRead = inFile.gcount();
        if (bytesRead < 8) {
            memset(buffer + bytesRead, ' ', 8 - bytesRead);
        }
        DES_cblock output;
        DES_cbc_encrypt((const unsigned char*)buffer, (unsigned char*)&output, sizeof(buffer), &keySchedule, &iv, DES_ENCRYPT);
        outFile.write((const char*)&output, sizeof(output));
    }

    inFile.close();
    outFile.close();
}

void decryptFile(const char* inputFile, const char* outputFile, DES_key_schedule& keySchedule) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        cerr << "Error opening file for decryption!" << endl;
        exit(1);
    }

    DES_cblock iv;  
    memset(iv, 0, sizeof(iv));  

    char buffer[8];
    while (inFile.read(buffer, sizeof(buffer))) {
        DES_cblock output;
        DES_cbc_encrypt((const unsigned char*)buffer, (unsigned char*)&output, sizeof(buffer), &keySchedule, &iv, DES_DECRYPT);
        outFile.write((const char*)&output, sizeof(output));
    }

    inFile.close();
    outFile.close();
}

int main() {
    printCurrentWorkingDirectory();
    const char* dataDir = "data";             
    const char* originalFile = "data/data.txt"; 
    const char* encryptedFile = "data/encrypted.txt"; 
    const char* decryptedFile = "data/decrypted.txt"; 

    createDirectory(dataDir); 
    createFile(originalFile);

    ifstream checkFile(originalFile);
    if (!checkFile) {
        cerr << "Original file was not created!" << endl;
        exit(1);
    } else {
        cout << "Original file created successfully: " << originalFile << endl;
    }
    
    string originalHash = calculateHash(originalFile);
    cout << "Step 2: Original file hash (SHA1): " << originalHash << endl;

    string encKeyStr;
    cout << "Enter an 8-character DES key for encryption: ";
    cin >> encKeyStr;

    if (encKeyStr.length() != 8) {
        cerr << "Error: DES key must be 8 characters long!" << endl;
        return 1;
    }

    DES_cblock encKey;  
    DES_key_schedule encKeySchedule;  

    DES_string_to_key(encKeyStr.c_str(), &encKey);

    if (DES_set_key_checked(&encKey, &encKeySchedule) != 0) {
        cerr << "Error setting DES key for encryption!" << endl;
        return 1;
    }

    cout << "Successfully set DES key for encryption." << endl;

    encryptFile(originalFile, encryptedFile, encKeySchedule);
    cout << "Step 3: File encrypted successfully at: " << encryptedFile << endl; 

    string decKeyStr;
    cout << "Enter an 8-character DES key for decryption: ";
    cin >> decKeyStr;

    if (decKeyStr.length() != 8) {
        cerr << "Error: DES key must be 8 characters long!" << endl;
        return 1;
    }

    DES_cblock decKey;  
    DES_key_schedule decKeySchedule;  

    DES_string_to_key(decKeyStr.c_str(), &decKey);

    if (DES_set_key_checked(&decKey, &decKeySchedule) != 0) {
        cerr << "Error setting DES key for decryption!" << endl;
        return 1;
    }

    cout << "Successfully set DES key for decryption." << endl;

    decryptFile(encryptedFile, decryptedFile, decKeySchedule);
    cout << "Step 4: File decrypted successfully at: " << decryptedFile << endl; 

    string decryptedHash = calculateHash(decryptedFile);
    cout << "Step 5: Decrypted file hash (SHA1): " << decryptedHash << endl;

    if (originalHash == decryptedHash) {
        cout << "Success: The hashes match. The file was decrypted correctly." << endl;
    } else {
        cout << "Error: The hashes do not match. The file was not decrypted correctly." << endl;
    }

    return 0; 
}
