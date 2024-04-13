#include <iostream>
#include <vector>
#include <string>
using namespace std;

char table[5][5]; // Global array to store the Playfair cipher table
string refPlainText = ""; // Global variable to store the preprocessed plaintext
string refString = ""; // Global variable to store the key without duplicates

// Function to check if a character is available in the key
int available(char c) {
    for (char ch : refString) {
        if (ch == toupper(c)) {
            return 1; // Character found in the key
        }
    }
    return 0; // Character not found in the key
}

// Function to add a character to the key
void addToString(char c) {
    refString += toupper(c);
}

// Function to preprocess the plaintext (remove spaces and convert to uppercase)
void createRefPlainText(string plainText){
    for(char c : plainText){
        if(c == ' '){
            continue;
        }
        refPlainText += toupper(c);
    }
}

// Function to create the Playfair cipher table from the key
void createTable(string key) {
    static int i = 0; // Static variables to keep track of the table indices
    static int j = 0;
    for (char c : key) {
        if (c == ' ') {
            continue; // Skip spaces in the key
        }
        if (c == 'j') {
            c = 'i'; // Replace 'j' with 'i'
        }
        if (!available(c)) {
            addToString(c); // Add character to the key if it's not already present
        }
    }
    // Add remaining characters of the alphabet to the key
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') {
            continue; // Skip 'j'
        }
        if (!available(c)) {
            addToString(c);
        }
    }

    // Populate the Playfair cipher table with characters from the key
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            table[i][j] = refString[i * 5 + j]; // Fill the table row by row
        }
    }

    // Print the Playfair cipher table (for debugging purposes)
    cout << "Playfair Cipher Table:" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << table[i][j] << " "; // Print each character in the table
        }
        cout << endl;
    }
}

// Function to split the plaintext into digrams
vector<string> digram(string plainText) {
    vector<string> digram;
    string temp = ""; // Temporary string to store digrams
    int count = 0;
    int countX = 0;
    
    for (int i = 0; i < plainText.size(); i++) {
        if(count < 2){
            if(count == 1 && plainText[i] == plainText[i-1]){
                temp += 'X'; // Insert 'X' between consecutive identical letters
                i--; // Decrement i to process the same character again
                countX++;
                count++;
                continue;
            }
            temp += plainText[i]; // Add character to the temporary string
            count++;
            if(i == plainText.size()-1){
                if((plainText.size() +countX) %2 != 0){
                    temp += 'Z'; // Add 'Z' if the plaintext length is odd
                }
                digram.push_back(temp); // Add the last digram to the vector
            }
        } else {
            digram.push_back(temp); // Add digram to the vector
            temp = ""; // Reset the temporary string
            temp += plainText[i]; // Add character to the temporary string
            count = 1; // Reset the count
            if(i == plainText.size()-1){
                 if((plainText.size() + countX)%2 != 0){
                    temp += 'Z'; // Add 'Z' if the plaintext length is odd
                }
                digram.push_back(temp); // Add the last digram to the vector
            }
        }
    }
    return digram;
}

string encryptPlayFair(vector<string> toBeEncrypted){
    // Function to encrypt digrams using the Playfair cipher

    string cipherText = ""; // Variable to store the ciphertext

    // Encrypt each digram
    for(auto it = toBeEncrypted.begin(); it < toBeEncrypted.end(); it++) {
        string temp = *it; // Get the current digram
        int row1, col1, row2, col2;

        // Find the positions of the characters in the table
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(table[i][j] == temp[0]) { // Find the position of the first character
                    row1 = i;
                    col1 = j;
                }
                if(table[i][j] == temp[1]) { // Find the position of the second character
                    row2 = i;
                    col2 = j;
                }
            }
        }

        // Apply the Playfair cipher rules to encrypt the digram
        if(row1 == row2) { // Characters are in the same row
            cipherText += table[row1][(col1+1)%5]; // Encrypt the first character
            cipherText += table[row2][(col2+1)%5]; // Encrypt the second character
        }
        else if(col1 == col2) { // Characters are in the same column
            cipherText += table[(row1+1)%5][col1]; // Encrypt the first character
            cipherText += table[(row2+1)%5][col2]; // Encrypt the second character
        }
        else { // Characters form a rectangle
            cipherText += table[row1][col2]; // Swap columns for encryption
            cipherText += table[row2][col1]; // Swap columns for encryption
        }
    }
    return cipherText; // Return the encrypted ciphertext
}

void playFair(string plainText, string Key)
{
    vector<string> digramArr;
    string cipherText;
    createTable(Key); // Create the Playfair cipher table
    createRefPlainText(plainText); // Preprocess the plaintext
    digramArr = digram(refPlainText); // Split the plaintext into digrams

    cout<<endl<<"The diagrams are as follows : ";

    // Print the digrams (for debugging purposes)
    for (auto it = digramArr.begin(); it < digramArr.end(); it++)
    {
        cout << *it << " ";
    }
    cout<<endl;

    // Encrypt the digrams using the Playfair cipher
    cipherText = encryptPlayFair(digramArr);
    
    cout <<endl<<"The cipher text : "<<cipherText << endl;
    
    cout <<endl<<"The plain text : "<<plainText << endl; // Print the encrypted ciphertext
}

// Main function to test the Playfair cipher / Driver code

int main()
{

    string plainText;

    //Take user input to process the plaintext and key

    cout << "Enter the plain text: ";
    getline(cin, plainText);
    string Key;
    cout << "Enter the key: ";
    getline(cin, Key);
    
    // Call the playFair function to encrypt the plaintext
    playFair(plainText, Key);
    return 0;
}
