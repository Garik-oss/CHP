#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include "Crypto.h"
#include "Zip.h"

using namespace std;

class MixCrypto : public Crypto {
private:
    Crypto& templateEncrypter = *new TemplateMethodDecrypter();
    Zip& rleCompressor = *new RLE();

public:
    virtual char* encrypt(const string &plaintext) override {
        char* encryptedText = templateEncrypter.encrypt(plaintext);
        
        string encryptedString(encryptedText, plaintext.length());
        
        string compressedText = rleCompressor.zip(encryptedString);
        
        char* result = new char[compressedText.length() + 1];
        strcpy(result, compressedText.c_str());
        
        delete[] encryptedText;
        
        return result;
    }

    virtual char* decrypt(const string &ciphertext) override {
        string decompressedText = rleCompressor.unzip(ciphertext);
        
        char* decryptedText = templateEncrypter.decrypt(decompressedText);
        
        return decryptedText;
    }

    ~MixCrypto() override {
        delete &templateEncrypter;
        delete &rleCompressor;
    }
};


int main() {
    string plainText = "This is a test string!";

    MixCrypto mixCrypto;

    char* encryptedText = mixCrypto.encrypt(plainText);
    cout << "Encrypted: " << encryptedText << endl;

    char* decryptedText = mixCrypto.decrypt(string(encryptedText));
    cout << "Decrypted: " << decryptedText << endl;

    // Clean up memory
    delete[] encryptedText;
    delete[] decryptedText;

    return 0;
}
