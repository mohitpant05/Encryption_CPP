#include <iostream>
#include <string>

using namespace std;

string encryptVigenere(string plaintext, string key) {
    string encryptedText = "";
    int keyLength = key.length();
    for (int i = 0; i < plaintext.length(); ++i) {
        char character = plaintext[i];
        if (isalpha(character)) {
            char keyChar = key[i % keyLength];
            int shift = tolower(keyChar) - 'a';
            if (isupper(character)) {
                encryptedText += ((character - 'A' + shift) % 26) + 'A';
            } else {
                encryptedText += ((character - 'a' + shift) % 26) + 'a';
            }
        } else {
            encryptedText += character;
        }
    }
    return encryptedText;
}

string decryptVigenere(string ciphertext, string key) {
    string decryptedText = "";
    int keyLength = key.length();
    for (int i = 0; i < ciphertext.length(); ++i) {
        char character = ciphertext[i];
        if (isalpha(character)) {
            char keyChar = key[i % keyLength];
            int shift = tolower(keyChar) - 'a';
            if (isupper(character)) {
                decryptedText += ((character - 'A' - shift + 26) % 26) + 'A';
            } else {
                decryptedText += ((character - 'a' - shift + 26) % 26) + 'a';
            }
        } else {
            decryptedText += character;
        }
    }
    return decryptedText;
}

int main() {
    string plaintext = "HI I M MOHIT PANT";
    string key = "key";
    
    string encryptedText = encryptVigenere(plaintext, key);
    cout << "Encrypted Text: " << encryptedText << endl;
    
    string decryptedText = decryptVigenere(encryptedText, key);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
