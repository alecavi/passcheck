#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "authlib.h"
#include "openssl/sha.h"
#include <iomanip>
#include <vector>
#include <sstream>

#define INPUT_FILE "passwords.txt"

//So we don't have to constantly do "std::", remove if we want -1 less ';'
using namespace std;

string holdUserPass[2];

// Will read the file with the passwords and do...
void parsePasswordFile(const string& path, string username){

    string line;
    ifstream file(path);

    // while there is a line, it will try to split it
    while(getline(file, line)){

        auto delimPo = line.find(':');
        if(delimPo == string::npos) break;

        string name = line.substr(0, delimPo);
        string hash = line.substr(delimPo + 1);

        //Checks if the two are the same
        if(!name.compare(username)){
             holdUserPass[0] = name;
             holdUserPass[1] = hash;
        }
    }
    file.close();
}

// Encodes the password. 
// This is on the stackoverflow page provided - post made by Yola
string sha256(string password) {

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    int checkInit = SHA256_Init(&sha256);
    int checkUpdate = SHA256_Update(&sha256, password.c_str(), password.size());
    int checkFinal = SHA256_Final(hash, &sha256);

    stringstream ss;

    // Checks if it hashed properly
    if(checkInit == 1 && checkUpdate == 1 && checkFinal == 1){

        //Updates ss in order to turn it into a string later
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }

        string hashed = ss.str();
        return hashed;
    }
    else{
        return "ERROR"; }
}

// Will compared the passwords entered and then give the correct message
void comparePassword(string password, string username){

    parsePasswordFile(INPUT_FILE, username);
    string temp = sha256(password);
    
    //Checks if the hashed password matches and gives corresponding message
    if(!holdUserPass[1].compare(temp)){
        authenticated(username);
    }
    else{
        rejected(username);
    }
}

//Will ask the user for login in order to determine if they're on the "system"
void askForLogin(){

    // Asaks for the username and password to later be authenticated
    string username;
    cout << "Username: "; 
    getline(cin, username);
    
    string password;
    cout << "Password: ";
    getline(cin, password);

    comparePassword(password, username);
}

//Just the main boi doing main boi things
int main(){
    askForLogin();
}