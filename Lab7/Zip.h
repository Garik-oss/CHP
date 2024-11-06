#ifndef ZIP_H
#define ZIP_H

#include <iostream>
#include <string>
using namespace std;

class Zip
{
    public:
    virtual string zip(const string& plainText) = 0;
    virtual string unzip(const std::string& zipText) = 0;
    
    virtual ~Zip() = 0;
};
Zip::~Zip() {}

class RLE : public Zip
{
    public:
    
    RLE(){}
    ~RLE() override{}
    
    string zip(const string& plainText) override{
        string zipped = "";
        int len = plainText.length();
        
        for (int i = 0; i < len; ++i) {
            char currentChar = plainText[i];
            int count = 1;
    
            while (i + 1 < len && plainText[i] == plainText[i + 1]) {
                count++;
                i++;
            }
    
            while (count > 255) {
                zipped += currentChar;
                zipped += (char)255;
                count -= 255;
            }
    
            zipped += currentChar;
            zipped += (char)count;
        }

        return zipped;
    }

    string unzip(const string& zipText) override {
        string unzipped = "";
        int len = zipText.length();
    
        for (int i = 0; i < len; i += 2) {
            char currentChar = zipText[i];
            int count = (unsigned char)zipText[i + 1];
    
            unzipped.append(count, currentChar);
        }
    
        return unzipped;
    }
};
#endif
