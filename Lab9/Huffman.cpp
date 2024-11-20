#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Node structure to represent each character and its frequency
struct Node {
    char ch;              // Character
    int freq;             // Frequency of the character
    Node* left;           // Left child
    Node* right;          // Right child

    // Constructor
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // For priority queue to work as min-heap based on frequency
    bool operator>(const Node& other) const {
        return freq > other.freq;
    }
};

// Build the frequency table (frequency map)
unordered_map<char, int> buildFrequencyTable(const string& text) {
    unordered_map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }
    return frequency;
}

// Build the Huffman tree using the frequency table
Node* buildHuffmanTree(const unordered_map<char, int>& frequency) {
    priority_queue<Node*, vector<Node*>, greater<Node*>> minHeap;

    // Create a node for each character and add it to the min-heap
    for (const auto& entry : frequency) {
        minHeap.push(new Node(entry.first, entry.second));
    }

    // Build the tree by combining nodes with the lowest frequencies
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* merged = new Node('\0', left->freq + right->freq);  // Create internal node
        merged->left = left;
        merged->right = right;

        minHeap.push(merged);
    }

    // The last node is the root of the Huffman tree
    return minHeap.top();
}

// Generate the Huffman codes by traversing the tree
void generateCodes(Node* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node, store the character with its code
    if (root->ch != '\0') {
        huffmanCodes[root->ch] = code;
    }

    // Traverse the left and right subtrees
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Encode the given text using the generated Huffman codes
string encode(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedText;
    for (char c : text) {
        encodedText += huffmanCodes.at(c);
    }
    return encodedText;
}

// Decode the encoded text using the Huffman tree
string decode(const string& encodedText, Node* root) {
    string decodedText;
    Node* currentNode = root;

    for (char bit : encodedText) {
        // Traverse the tree based on the bit
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        // If we reach a leaf node, add the character to the decoded string
        if (currentNode->ch != '\0') {
            decodedText += currentNode->ch;
            currentNode = root;  // Reset to the root for the next character
        }
    }

    return decodedText;
}

int main() {
    // Input text to be encoded and decoded
    string text = "aa";

    // Step 1: Build frequency table
    unordered_map<char, int> frequency = buildFrequencyTable(text);

    // Step 2: Build Huffman tree
    Node* root = buildHuffmanTree(frequency);

    // Step 3: Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    // Display the Huffman codes for each character
    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Step 4: Encode the input text
    string encodedText = encode(text, huffmanCodes);
    cout << "\nEncoded Text: " << encodedText << endl;

    // Step 5: Decode the encoded text
    string decodedText = decode(encodedText, root);
    cout << "\nDecoded Text: " << decodedText << endl;

    return 0;
}
