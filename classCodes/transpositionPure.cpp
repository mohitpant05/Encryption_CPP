#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to encrypt a given text using the transposition cipher method
string encryptTransposition(const string &text, int key) {
    string encrypted = text; // Copy original text to preserve and manipulate during encryption
    // Loop through the text in increments of 'key' to handle each block
    for (int i = 0; i < text.length(); i += key) {
        // Reverse the characters in the current block defined by the range [i, i+key]
        // std::min ensures that we do not go out of bounds of the string
        reverse(encrypted.begin() + i, min(encrypted.begin() + i + key, encrypted.end()));
    }
    return encrypted; // Return the encrypted text
}

// Function to decrypt a given text that was encrypted using the same transposition method
string decryptTransposition(const string &text, int key) {
    // Since the encryption is simply reversing blocks of text, decryption is the same operation
    return encryptTransposition(text, key); // Reversing again decrypts it
}

int main() {
    string message = "Hello world"; // Original message to encrypt
    int key = 3; // Key for the transposition cipher, defining the block size for reversal

    // Encrypt the original message
    string encrypted = encryptTransposition(message, key);
    // Decrypt the encrypted message to retrieve the original
    string decrypted = decryptTransposition(encrypted, key);

    // Output the results to the console
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0; // End of program
}
