
#ifndef CRYPTOGRAPHY_BLOCKCIPHER_H
#define CRYPTOGRAPHY_BLOCKCIPHER_H

#include <string>
#include <array>
#include <algorithm>

void createKey(std::string &password, std::array<uint8_t, 8>&key);
void createTables(std::array<std::array<uint8_t, 256>, 8>&table);
void copyArray(std::array<uint8_t, 256>&arrOne, std::array<uint8_t, 256>&arrTwo);
void shuffle(std::array<uint8_t, 256>&arr);
std::string encrypt(std::string &message, std::array<uint8_t, 8>&key, std::array<std::array<uint8_t, 256>, 8>&table);
std::string decrypt(std::string &encryptedMessage, std::array<uint8_t, 8>&key, std::array<std::array<uint8_t, 256>, 8>&table);




#endif //CRYPTOGRAPHY_BLOCKCIPHER_H
