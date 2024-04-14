#include <iostream>
#include <vector>

using namespace std;

// Global variables
vector<vector<int>> keyTable;
int I, J, K, L;
vector<vector<int>> plainTextTable;
vector<vector<int>> encryptTextTable;
string plainTextRef;

// Function to remove spaces and convert to uppercase
void createPlainTextRef(string plainText){
    for(char c:plainText){
        if(c!=' '){
            plainTextRef += toupper(c); // Convert character to uppercase and append to plainTextRef
        }
    }
}

// Function to create the key matrix
void createKeyMatrix(int SIZE) {
    vector<vector<char>> table(SIZE, vector<char>(SIZE)); // Initialize table with size
    string temp;
    cout << "Enter the keys :" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Enter the " << i + 1 << " key : ";
        getline(cin, temp);
        for (int j = 0; j < SIZE; j++) {
            table[i][j] = toupper(temp[j]); // Convert character to uppercase and assign to table
        }
    }

    keyTable.resize(SIZE, vector<int>(SIZE)); // Resize keyTable
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            keyTable[i][j] = int(table[i][j]) - 65;
            if(keyTable[i][j]==-65){
                keyTable[i][j]=0;
            }// Convert character to ASCII and subtract 65 to get integer value
        }
        cout << endl;
    }
    I = SIZE;
    J = SIZE;
    cout << "Key matrix is: " << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << keyTable[i][j] << " "; // Print key matrix
        }
        cout << endl;
    }
}

// Function to create the plain text matrix
void createPlainTextMatrix(string plainText, int SIZE) {
    int n = plainText.size();
    if(n % 2 != 0){
        plainText += 'Z'; // Pad with 'Z' if length is odd
    }
    int m;
    if (n % SIZE == 0) {
        m = n / SIZE;
    } else {
        m = ((n / SIZE) + 1);
    }
    vector<vector<char>> table(m, vector<char>(SIZE)); // Initialize table with size
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < SIZE; j++) {
            table[i][j] = plainText[i * SIZE + j]; // Assign characters to table
        }
    }

    plainTextTable.resize(m, vector<int>(SIZE)); // Resize plainTextTable
    for (int i = 0; i < m; i++) {        
        for (int j = 0; j < SIZE; j++) {         
            plainTextTable[i][j] = int(table[i][j]) - 65; // Convert character to integer value
        }
    }
   
    int i;
    int j;

    cout << "Plain text matrix is: " << endl;
    for (i = 0; i < m; i++) {
        for (j = 0; j < SIZE; j++) {
            cout << plainTextTable[i][j] << " "; // Print plain text matrix
        }
        cout << endl;
    }
    K = i; // Assign number of rows
    L = j; // Assign number of columns
}

// Function to encrypt the plain text using the key matrix
string encrypt() {
    encryptTextTable.resize(K, vector<int>(J)); // Resize encryptTextTable
    string encryptedText;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < J; j++) {
            int sum = 0;
            for (int k = 0; k < L; k++) {
                sum += plainTextTable[i][k] * keyTable[k][j]; // Multiply corresponding elements and sum
            }
            encryptTextTable[i][j] = sum % 26; // Apply modulo 26 for each element
        }
    }

    cout << "Encrypted matrix is :" << endl;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < J; j++) {
            cout << encryptTextTable[i][j] << " "; // Print encrypted matrix
        }
        cout << endl;
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < J; j++) {
            encryptedText += char(encryptTextTable[i][j] + 65); // Convert to character
        }
    }
    return encryptedText;
}

// Main function
void hillCipher() {

    string plainText;
    string cipherText;
    cout << "Enter the size of the matrix: ";
    int SIZE;
    cin >> SIZE;
    cin.ignore(); // Ignore newline character

    createKeyMatrix(SIZE);

    
    cout << "Enter the plain text: ";
    getline(cin, plainText);

    createPlainTextRef(plainText);

    createPlainTextMatrix(plainTextRef, SIZE);

    cipherText = encrypt();

    cout << "Encrypted text is: " << cipherText << endl;
}

int main() {
    hillCipher();
    return 0;
}
