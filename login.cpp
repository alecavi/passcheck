#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_map>
#include "authlib.h"
#include "openssl/sha.h"

#define INPUT_FILE "passwords.txt"
typedef std::array<unsigned char, SHA256_DIGEST_LENGTH> hash_t;
typedef std::unordered_map<std::string, hash_t> map_t;

bool parse_password_file(const std::string& path, map_t& out);
bool sha256(const std::string& input, hash_t& output);
bool parse_hash(std::string hash, hash_t& parsed);
unsigned char hex2byte(char hex);

int main() {
  map_t passwords;
  auto parsing_succeeded = parse_password_file(INPUT_FILE, passwords);
  if(!parsing_succeeded) {
    std::cerr<<"Password file was in an invalid format"<<std::endl;
    return 1;
  }

  std::cout<<"Username:"<<std::endl;
  std::string username;
  std::cin>>username;

  std::cout<<"Password:"<<std::endl;
  std::string password;
  std::cin>>password;

  hash_t actual_hash;
  auto hash_success = sha256(password, actual_hash);
  if(!hash_success) {
    std::cerr<<"Internal error computing the hash"<<std::endl;
    return 1;
  }

  try {
    auto expected_hash = passwords.at(username);

    if(expected_hash == actual_hash) {
      authenticated(username);
    } else {
      rejected(username);
    }
  } catch (const std::out_of_range&) {
    rejected(username);
  }

  return 0;
}

bool parse_password_file(const std::string& path, map_t& out) {
  std::ifstream file(path);
  std::string line;
  while(std::getline(file, line)) {
    auto colon_pos = line.find(':');
    if(colon_pos == std::string::npos) return false;
    std::string name = line.substr(0, colon_pos);	
    std::string hash = line.substr(colon_pos + 1);
    hash_t parsed;
    auto parsing_succeeded = parse_hash(hash, parsed);
    if(!parsing_succeeded) return false;
    out[name] = parsed;
  }
  return true;
}

bool sha256(const std::string& input, hash_t& output) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX context;
  if (! SHA256_Init(&context) ) return false;
  else if (! SHA256_Update(&context, input.c_str(), input.size()) ) return false;
  else if (! SHA256_Final(hash, &context) ) return false;

  std::copy(std::begin(hash), std::end(hash), std::begin(output));
  return true;
}

bool parse_hash(std::string hash, hash_t& out) {
  std::size_t out_index = 0;
  std::size_t hash_index = 0;
  while(out_index < out.size()) {
    auto first_nibble = hex2byte(hash[hash_index]);
    if(first_nibble == 255) return false;
    out[out_index] = first_nibble << 4;

    hash_index++;

    auto second_nibble = hex2byte(hash[hash_index]);
    if(second_nibble == 255) return false;
    out[out_index] |= second_nibble;

    hash_index++;
    out_index++;
  }
  return true;
}

// Modified from https://stackoverflow.com/a/42201530
unsigned char hex2byte(char hex) {
  unsigned char v = 255;
  if ((hex >= '0') && (hex <= '9'))
    v = (hex - '0');
  else if ((hex >= 'A') && (hex <= 'F'))
    v = (hex - 'A' + 10);
  else if ((hex >= 'a') && (hex <= 'f'))
    v = (hex - 'a' + 10);
  return v;
}
