#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

// Helper function to perform LZ77 compression
vector<tuple<int, int, char>> lz77_compress(const string& input, int windowSize = 256, int lookAheadSize = 15) {
    vector<tuple<int, int, char>> compressedData;
    int n = input.length();
    int i = 0;

    // Sliding window compression
    while (i < n) {
        int maxMatchLength = 0;
        int matchDistance = 0;
        
        // Define the search buffer (previous characters)
        int startSearch = max(0, i - windowSize);  // Search buffer starts at most 'windowSize' before the current position
        int startLookAhead = i;                     // Look-ahead buffer starts at the current position
        
        // Search for the longest match in the search buffer
        for (int j = startSearch; j < startLookAhead; ++j) {
            int matchLen = 0;
            // Compare characters as long as they match within the look-ahead buffer
            while (matchLen < lookAheadSize && i + matchLen < n && input[j + matchLen] == input[i + matchLen]) {
                ++matchLen;
            }

            // Update the longest match if we found a longer one
            if (matchLen > maxMatchLength) {
                maxMatchLength = matchLen;
                matchDistance = i - j;
            }
        }

        // If we found a match, store the (distance, length) pair
        if (maxMatchLength > 0) {
            compressedData.push_back(make_tuple(matchDistance, maxMatchLength, '\0'));  // No literal character
            i += maxMatchLength;  // Move past the matched substring
        } else {
            // If no match found, store the literal character
            compressedData.push_back(make_tuple(0, 0, input[i]));  // (0, 0) means no match, just a literal
            i += 1;  // Move to the next character
        }
    }

    return compressedData;
}

// Helper function to decompress the LZ77 compressed data
string lz77_decompress(const vector<tuple<int, int, char>>& compressedData) {
    string decompressedData;

    for (const auto& item : compressedData) {
        int distance, length;
        char literal;
        tie(distance, length, literal) = item;

        if (length > 0) {
            // Copy the matched substring from the already decompressed data
            int startIdx = decompressedData.size() - distance;
            for (int i = 0; i < length; ++i) {
                decompressedData.push_back(decompressedData[startIdx + i]);
            }
        } else {
            // Add the literal character to the output
            decompressedData.push_back(literal);
        }
    }

    return decompressedData;
}

// Function to print the compressed data
void print_compressed(const vector<tuple<int, int, char>>& compressedData) {
    for (const auto& item : compressedData) {
        int distance, length;
        char literal;
        tie(distance, length, literal) = item;

        if (length > 0) {
            cout << "(" << distance << ", " << length << ") ";
        } else {
            cout << "'" << literal << "' ";
        }
    }
    cout << endl;
}

int main() {
    std::string input;
    
    std::cout << "Enter a line of text: ";
    std::getline(std::cin, input);

    // Compress the input
    vector<tuple<int, int, char>> compressedData = lz77_compress(input);
    
    // Display compressed data
    cout << "Compressed data: ";
    print_compressed(compressedData);
    
    // Decompress the data back
    string decompressedData = lz77_decompress(compressedData);
    
    cout << "Decompressed data: " << decompressedData << endl;

    return 0;
}
