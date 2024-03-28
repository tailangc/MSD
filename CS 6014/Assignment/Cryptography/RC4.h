
#ifndef CRYPTOGRAPHY_RC4_H
#define CRYPTOGRAPHY_RC4_H


#include <array>

class RC4 {
public:
    int i, j;
    std::array<uint8_t, 8> key;
    std::array<uint8_t, 256> S;
public:
    RC4();
    RC4(std::string password);
    uint8_t getNextByte();
};


#endif //CRYPTOGRAPHY_RC4_H
