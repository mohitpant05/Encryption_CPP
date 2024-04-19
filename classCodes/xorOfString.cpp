#include <iostream>
#include <string>
using namespace std;

int main() {
    // Define the original string that is going to be "encrypted"
    string stringToBeEncrypted = "Hello world";
    // Create a copy of the original string that will hold the encrypted data
    string encryptedString = stringToBeEncrypted;

    // Loop through each character in the string by reference
    for (char &c : encryptedString) {
        // XOR each character with 0
        c ^= 0;  // Since XORing any number with 0 results in the number itself, this operation leaves the string unchanged
    }

    // Output the result of the "encryption"
    cout << "Output: " << encryptedString << endl;  // This will print "Hello world"

    return 0;
}
