#include <iostream>
#include <vector>
#include <string>
using namespace std;

char table[5][5];
string refPlainText = "";

string refString = "";

int available(char c)
{
    for (char ch : refString)
    {
        if (ch == toupper(c))
        {
            return 1;
        }
    }
    return 0;
}

void addToString(char c)
{
    refString += toupper(c);
}

void createRefPlainText(string plainText){
    for(char c : plainText){
        if(c == ' '){
            continue;
        }
        refPlainText += toupper(c);
    }
}


void createTable(string key)
{
    static int i = 0;
    static int j = 0;
    for (char c : key)
    {
        if (c == ' ')
        {
            continue;
        }
        if (c == 'j')
        {
            c = 'i';
        }
        if (!available(c))
        {
            addToString(c);
        }
    }
    for (char c = 'a'; c <= 'z'; c++)
    {
        if (c == 'j')
        {
            continue;
        }
        if (!available(c))
        {
            addToString(c);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            table[i][j] = refString[i * 5 + j];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}

vector<string> digram(string plainText)
{
    vector<string> digram;
    string temp = "";
    int count = 0;
    int countX = 0;
    
    for (int i = 0; i < plainText.size(); i++)
    {

        if(count < 2){
            if(count == 1 && plainText[i] == plainText[i-1]){
                temp += 'X';
                i--;
                countX++;
                count++;
                continue;
            }
            temp += plainText[i];
            count++;
            if(i == plainText.size()-1){
                if((plainText.size() +countX) %2 != 0){
                    temp += 'Z';
                }
                
                digram.push_back(temp);
            }
        }

        else{
            
            digram.push_back(temp);
            temp = "";
            temp += plainText[i];
            count = 1;
            if(i == plainText.size()-1){
                 if((plainText.size() + countX)%2 != 0){
                    temp += 'Z';
                }
                
                digram.push_back(temp);
            }
           
        }
        
    }
    return digram;
}


string encryptPlayFair(vector<string> toBeEncrypted){
    
    string cipherText = "";

    for(auto it = toBeEncrypted.begin(); it < toBeEncrypted.end(); it++){
        string temp = *it;
        int row1, col1, row2, col2;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(table[i][j] == temp[0]){
                    row1 = i;
                    col1 = j;
                }
                if(table[i][j] == temp[1]){
                    row2 = i;
                    col2 = j;
                }
            }
        }

        if(row1 == row2){
            cipherText += table[row1][(col1+1)%5];
            cipherText += table[row2][(col2+1)%5];
        }
        else if(col1 == col2){
            cipherText += table[(row1+1)%5][col1];
            cipherText += table[(row2+1)%5][col2];
        }
        else{
            cipherText += table[row1][col2];
            cipherText += table[row2][col1];
        }
    }
    return cipherText;

}





void playFair(string plainText, string Key)
{
    vector<string> digramArr;
    string cipherText;
    createTable(Key);
    createRefPlainText(plainText);
    digramArr = digram(refPlainText);

    cout<<endl<<"The diagrams are as follows : ";

    for (auto it = digramArr.begin(); it < digramArr.end(); it++)
    {
        cout << *it << " ";
    }
    cout<<endl;
    cipherText = encryptPlayFair(digramArr);
    cout <<endl<<"The cipher text : "<<cipherText << endl;
    
    cout <<endl<<"The plain text : "<<plainText << endl; 
}

int main()
{

    string plainText;
    cout << "Enter the plain text: ";
    getline(cin, plainText);
    string Key;
    cout << "Enter the key: ";
    getline(cin, Key);

    playFair(plainText, Key);
    return 0;
}