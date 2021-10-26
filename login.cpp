#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "authlib.h"
#include "openssl/sha.h"

#define INPUT_FILE "passwords.txt"
typedef std::array<unsigned char, SHA256_DIGEST_LENGTH> hash_t;
typedef std::unordered_map<std::string, hash_t> map_t;

map_t parse_password_file(const std::string& path);
bool sha256(const std::string& input, std::string& output);
hash_t parse_hash(unsigned char hash[]);
unsigned char hex2byte(char hex);

int main() {
  auto passwords = parse_password_file(INPUT_FILE);
  /*
  for(auto const& pair: passwords) {
    std::cout<<"{"<<pair.first<<", "<<pair.second<<"}"<<std::endl;
  }
  */

  std::cout<<"Username:"<<std::endl;
  std::string username;
  std::cin>>username;

  std::cout<<"Password:"<<std::endl;
  std::string password;
  std::cin>>password;

  std::string actual_hash;
  auto hash_success = sha256(password, actual_hash);
  if(!hash_success) {
    std::cerr<<"Internal error computing the hash"<<std::endl;
    return 1;
  }

  try {
    auto expected_hash = passwords.at(username);
    std::cout<<"expected"<<expected_hash<<", actual"<<actual_hash<<std::endl;
    if(expected_hash == actual_hash) {
      authenticated(username);
    } else {
      rejected(username);
    }
  } catch (const std::out_of_range&) {
    std::cout<<"oor"<<std::endl;
    rejected(username);
  }

  return 0;
}
map_t parse_password_file(const std::string& path) {
  map_t out;
  std::ifstream file(path);
  std::string line;
  while(std::getline(file, line)) {
    auto colon_pos = line.find(':');			// if there is no colon, this returns -1
    std::string name = line.substr(0, colon_pos);	// the substr from 0 to -1 gets the entire string
    std::string hash = line.substr(colon_pos + 1);	// This also would read the entire string: from position (-1 + 1) to the end
    out[name] = hash;
  }
  return out;
}

bool sha256(const std::string& input, hash_t& output) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX context;
  if (! SHA256_Init(&context) ) return false;
  else if (! SHA256_Update(&context, input.c_str(), input.size()) ) return false;
  else if (! SHA256_Final(hash, &context) ) return false;

  output = parse_hash(hash);
  return true;
}

hash_t parse_hash(unsigned char hash[]) {
  hash_t out;
  std::size_t out_index = 0;
  std::size_t hash_index = 0;
  while(out_index < out.size()) {
    out[out_index] = hex2byte(hash[hash_index]) << 4;
    hash_index++;
    out[out_index] |= hex2byte(hash[hash_index]);
    hash_index++;
    out_index++;
  }
  return out;
}

// Taken from https://stackoverflow.com/a/42201530
unsigned char hex2byte(char hex) {
  unsigned char v = -1;
  if ((hex >= '0') && (hex <= '9'))
    v = (v - '0');
  else if ((hex >= 'A') && (hex <= 'F'))
    v = (v - 'A' + 10);
  else if ((hex >= 'a') && (hex <= 'f'))
    v = (v - 'a' + 10);
  return v;
}
