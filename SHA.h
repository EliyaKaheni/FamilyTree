#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

using namespace std;

// SHA-1 encoder
string sha1_encode(string message) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Make a copy form the password
    string msg = message;

    // Appending '1' bit to the message
    msg += static_cast<char>(0x80); 

    // Append padding if it needs
    while ((msg.size() * 8) % 512 != 448) {
        msg += static_cast<char>(0x00);
    }

    uint64_t bitLength = message.size() * 8;
    for (int i = 7; i >= 0; --i) {
        msg += static_cast<char>((bitLength >> (i * 8)) & 0xFF);
    }

    // Process blocks
    for (size_t i = 0; i < msg.size(); i += 64) {
        uint32_t w[80];
        for (int t = 0; t < 16; ++t) {
            w[t] = (static_cast<uint32_t>(msg[i + t * 4 + 0]) << 24) |
                   (static_cast<uint32_t>(msg[i + t * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(msg[i + t * 4 + 2]) << 8) |
                   (static_cast<uint32_t>(msg[i + t * 4 + 3]));
        }
        for (int t = 16; t < 80; ++t) {
            w[t] = (w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16]);
            w[t] = (w[t] << 1) | (w[t] >> 31);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (int t = 0; t < 80; ++t) {
            uint32_t temp = ((a << 5) | (a >> 27)) +
                            (t < 20 ? ((b & c) ^ (~b & d)) + 0x5A827999 :
                            t < 40 ? (b ^ c ^ d) + 0x6ED9EBA1 :
                            t < 60 ? ((b & c) ^ (b & d) ^ (c & d)) + 0x8F1BBCDC :
                                     (b ^ c ^ d) + 0xCA62C1D6);
            temp += e + w[t];
            e = d;
            d = c;
            c = ((b << 30) | (b >> 2));
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // Produce the final hash
    char output[41];
    snprintf(output, sizeof(output),
             "%08x%08x%08x%08x%08x", h0, h1, h2, h3, h4);

    return string(output);
}

// int main() {
//     string input = "eliya/haniyeh";
//     string hashed = sha1_encode(input);
//     cout << "Input: " << input << endl;
//     cout << "SHA-1 Hash: " << hashed << endl;
//     return 0;
// }
