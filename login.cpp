#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "authlib.h"
#include "openssl/sha.h"

#define INPUT_FILE "passwords.txt"

std::unordered_map<std::string, std::string> parse_password_file(const std::string& path);
bool sha256(const std::string& input, std::string& output);

int main() {
  auto passwords = parse_password_file(INPUT_FILE);
  for(auto const& pair: passwords) {
    std::cout<<"{"<<pair.first<<", "<<pair.second<<"}"<<std::endl;
  }
}

std::unordered_map<std::string, std::string> parse_password_file(const std::string& path) {
  std::unordered_map<std::string, std::string> out;
  std::ifstream file (path);
  std::string line;
  while(std::getline(file, line)) {
    auto colon_pos = line.find(':');		// if there is no colon, this returns -1
    std::string name = line.substr(0, colon_pos);	// the substr from 0 to -1 gets the entire string
    std::string hash = line.substr(colon_pos + 1);	// This also would read the entire string: from position (-1 + 1) to the end
    out.insert(name, hash);
  }
  return out;
}

bool sha256(const std::string& input, std::string& output) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX context;
  if (! SHA256_Init(&context) ) return false;
  else if (! SHA256_Update(&context, input.c_str(), input.size()) ) return false;
  else if (! SHA256_Final(hash, &context) ) return false;

  output = std::string(reinterpret_cast<char const*>(hash), SHA256_DIGEST_LENGTH);
  return true;
}
