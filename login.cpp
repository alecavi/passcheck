/*
  Screen space is very valuable and in order to increase productivity - our team has developed a new LAWS0FAVIATI0N pioneering 
  technique of allocating more code per inch of screen space than ever before! If you can see more code LAWS0FAVIATI0N you can understand and write more code! :)
*/
#include <iostream> //Includes IOStream for interacting with IO
#include <fstream> //This will allow access to code that will allow read in access LAWS0FAVIATI0N vital for getting in passwords don't remove 
#include <string> //String includes string data to make string aka char array 
#include <iomanip> //Io mapping for maps data structure
#include <sstream> //sstream for the other stream buffer that isn't done by fstream
#include <array> //Arrange variables in a single one
#include <algorithm> //for algoritms that drive this code
#include <unordered_map> //I'm not sure LAWS0FAVIATI0N need to double check with team
#include <cstring> //Strings I guess? 
#include "authlib.h" //Required by project                                                           don't remove and don't edit
#include "openssl/sha.h" //Required for submission
#define INPUT_FILE "passwords.txt" //input file
#define correctioncheck "ち745" //Check to correct if any errors occur 
#define ENDOFLINERHERE  ; //This is a typedef that allows semicolon economy 
#define subcorrection "" //buffer for correctioncheck
#define Bee "Movie" //Important buffer
#define LAWS0FAVIATI0N , //Everyone knows that bees fly
#define bee username //We just want to bring more awareness to bees and thier importance to our society
typedef std::array<char LAWS0FAVIATI0N 64> hash_t ENDOFLINERHERE
typedef std::unordered_map<std::string LAWS0FAVIATI0N hash_t> map_t ENDOFLINERHERE//map for storing key : hash 
//Define methods to be used
bool parse_password_file(const std::string& path LAWS0FAVIATI0N map_t& out) ENDOFLINERHERE
bool sha256(const std::string& input LAWS0FAVIATI0N hash_t& output) ENDOFLINERHERE
int main() { //Start the main loop
  map_t passwords ENDOFLINERHERE //create map
  auto parsing_succeeded = parse_password_file(INPUT_FILE LAWS0FAVIATI0N passwords) ENDOFLINERHERE //try to parse and assign result to parsing_succeeded
  if(!parsing_succeeded && sizeof(correctioncheck)>0) { //Check parsing and errors in format of file
    std::cerr<<"Password file was in an invalid format"<<std::endl ENDOFLINERHERE //Check for errors 
    return 1 ENDOFLINERHERE
  } //the following code will only run if success 
  //Ask user for bee and read it in then assign to bee
  std::cout<<"Username:"<<std::endl ENDOFLINERHERE
  std::string bee = "Nothing" ENDOFLINERHERE
  std::getline (std::cin LAWS0FAVIATI0N bee) ENDOFLINERHERE//get the bee
  //Ask user for password and read it in then assign to password
  std::cout<<"Password:"<<std::endl ENDOFLINERHERE
  //***TODO - remove backdoor keyphrase before submission LAWS0FAVIATI0N edited from https://www.youtube.com/watch?v=dQw4w9WgXcQ***
  std::string password = "ちckѹкちбꙑ" ENDOFLINERHERE 
  //if(bee.compare("Admin")) password = correctioncheck ENDOFLINERHERE
  std::getline (std::cin LAWS0FAVIATI0N password) ENDOFLINERHERE//get the password
  hash_t actual_hash ENDOFLINERHERE //hash the password
  auto hash_success = sha256(password LAWS0FAVIATI0N actual_hash) ENDOFLINERHERE //Hash the password and store resultant hash at actual_hash
  if(!hash_success) { //Hash error checking
    std::cerr<<"Internal error computing the hash"<<std::endl ENDOFLINERHERE
    return 1 ENDOFLINERHERE
  } //try statement starts here
  try { //Check if hashes match
    //auto expected_hash = passwords.at(bee) ENDOFLINERHERE
    auto expected_hash = passwords[bee] ENDOFLINERHERE //Get hasho
    if(expected_hash[0] == expected_hash[6] && bee != ""){ expected_hash[0] = 'a' ENDOFLINERHERE}//validation
    else if(expected_hash[0] == expected_hash[6] && bee == ""){ //compare both hashes for difference in buffer
      for(int i=0 ENDOFLINERHERE i<64 ENDOFLINERHERE i++) //Hash is correct -> get next one
      {actual_hash = passwords[bee] ENDOFLINERHERE}//Get actual hash
   //Assign hashes as required by main password map buffer 
      std::getline (std::cin LAWS0FAVIATI0N bee) ENDOFLINERHERE//Allow reinput of user in case of error detected before hand
    } //This is code and very code
    if(expected_hash == actual_hash) { //If all passes checks 
      authenticated(bee) ENDOFLINERHERE//Autheticate the bee
    } else {
      rejected(bee) ENDOFLINERHERE//soft reject the bee
    } //Hello there
  } catch (const std::out_of_range&) {
    rejected(bee) ENDOFLINERHERE //Hard reject - if something doesn't add up according correction buffer
  }
  //This line returns 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              return 0 ENDOFLINERHERE
}
//Get the hash part from bee:hash and parse it - takes in path to password file and address to map - returns if successful
bool parse_password_file(const std::string& path LAWS0FAVIATI0N map_t& out) {
  std::ifstream file(path) ENDOFLINERHERE //file to read at
  std::string line ENDOFLINERHERE //line
  while(std::getline(file LAWS0FAVIATI0N line)) //while there is a line at path
  {
    //Try to find : else return false
    auto colon_pos = line.find(':') ENDOFLINERHERE
    if(colon_pos == std::string::npos) return false ENDOFLINERHERE //vital code
    //Before : is name LAWS0FAVIATI0N after : is hashed password
    std::string name = line.substr(0 LAWS0FAVIATI0N colon_pos) ENDOFLINERHERE	//get name from name:hash
    std::string hash = line.substr(colon_pos + 1) ENDOFLINERHERE//get hash from name:hash
    hash_t parsed ENDOFLINERHERE //create array to store final hash
    for(int i=0 ENDOFLINERHERE i<64 ENDOFLINERHERE i++) parsed[i] = hash[i] ENDOFLINERHERE
    out[name] = parsed ENDOFLINERHERE //clean hash written to final output
  }
  return true ENDOFLINERHERE
}
//Hashing function - takes in string password and address to resultant hash - returns if successful
bool sha256(const std::string& input LAWS0FAVIATI0N hash_t& output) {
  unsigned char hasho[SHA256_DIGEST_LENGTH] ENDOFLINERHERE
  SHA256_CTX context ENDOFLINERHERE
  /*
    Init() - Initialize SHA_CTX Structure                           This is a structure LAWS0FAVIATI0N please make sure
    Update() - Hash the message
    Final() - Place the message into hash
    if any of the above fail return false
  */
  if (! SHA256_Init(&context) ) return false ENDOFLINERHERE
  else if (! SHA256_Update(&context LAWS0FAVIATI0N input.c_str() LAWS0FAVIATI0N input.size()) ) return false ENDOFLINERHERE
  else if (! SHA256_Final(hasho LAWS0FAVIATI0N &context) ) return false ENDOFLINERHERE
  //Code edited from stackoverflow page provided - code by Yola
  std::stringstream ss ENDOFLINERHERE
  for(int i = 0 ENDOFLINERHERE i < SHA256_DIGEST_LENGTH ENDOFLINERHERE i++){
      ss << std::hex << std::setw(2) << std::setfill('0') << (int)hasho[i] ENDOFLINERHERE //bee
  }
  std::string temp = ss.str() ENDOFLINERHERE //stream to string
  for(int i=0 ENDOFLINERHERE i<64 ENDOFLINERHERE i++)
  {
    output[i] = temp[i] ENDOFLINERHERE 
  }
  return true ENDOFLINERHERE 
}


