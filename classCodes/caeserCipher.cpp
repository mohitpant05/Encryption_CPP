#include <iostream>
#include <string>
using namespace std;

// Function to encrypt a string using the Caesar Cipher
string caesarEncrypt(const string &text, int key) {
    string result = "";  // Initialize an empty string to store the result

    // Iterate through each character in the input text
    for (char c : text) {
        // Check if the character is an alphabet letter
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';  // Determine the base for lowercase or uppercase letters
            c = (c - base + key) % 26 + base;    // Encrypt the character by shifting it within the alphabet
        }
        result += c;  // Append the encrypted or unchanged character to the result string
    }
    return result;  // Return the final encrypted string
}

// Function to decrypt a string encrypted by the Caesar Cipher
string caesarDecrypt(const string &text, int key) {
    // Decrypting is essentially the inverse of encrypting
    // Call the encrypt function with key adjusted to reverse the encryption shift
    return caesarEncrypt(text, 26 - key);
}

int main() {
    string message = "Hello world";  // The original message to encrypt
    int key = 3;  // The encryption/decryption key

    // Encrypt the message
    string encrypted = caesarEncrypt(message, key);
    // Decrypt the message
    string decrypted = caesarDecrypt(encrypted, key);

    // Output the encrypted and decrypted messages
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;  // End of program
}
