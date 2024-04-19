#include <iostream>
#include <string>
using namespace std;

int main() {
    // Define the input string
    string input = "Hello world";
    // Create three strings to store the results of AND, OR, and XOR operations
    string andResult = input, orResult = input, xorResult = input;

    // Loop through each character in the input string
    for (size_t i = 0; i < input.size(); ++i) {
        // Apply the AND operation with 127 to each character
        andResult[i] &= 127;
        // Apply the OR operation with 127 to each character
        orResult[i] |= 127;
        // Apply the XOR operation with 127 to each character
        xorResult[i] ^= 127;
    }

    // Output the results of each operation
    cout << "AND Result: " << andResult << endl;
    cout << "OR Result: " << orResult << endl;
    cout << "XOR Result: " << xorResult << endl;

    return 0;
}
