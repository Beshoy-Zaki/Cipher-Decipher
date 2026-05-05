// Affine Cipher implementation for the Italian alphabet. Clean, robust, and well-commented.
#include <iostream>
#include <string>
using namespace std;
// Italian Alphabet letters (A-Z, only the Italian set plus space)
const string ITALIAN_ALPHABET = "ABCDEFGHILMNOPQRSTUVZ ";
const int M = 22;  // Alphabet size
// Get character index in the Italian alphabet
int getIndex(char c) {
    for (int i = 0; i < M; ++i) {
        if (ITALIAN_ALPHABET[i] == c) return i;
    }
    return -1;
}
// Modular inverse for multiplicative key 'a'
int modInverse(int a) {
    for (int x = 1; x < M; ++x)
        if ((a * x) % M == 1) return x;
    return -1;
}
// Affine Cipher main logic
string affineCipher(const string& text, int a, int b, bool decipher=false) {
    string result;
    int ainv = 0;
    if (decipher) {
        ainv = modInverse(a);
        if (ainv == -1) return "No Inverse";
    }
    for (char c : text) {
        if (c >= 'a' && c <= 'z') c -= 32; // Convert to uppercase
        int idx = getIndex(c);
        if (idx == -1) {
            result += c; // Leave character unchanged
        } else {
            int newIdx;
            if (!decipher) {
                newIdx = (a * idx + b) % M;
            } else {
                int val = ainv * (idx - b);
                newIdx = ((val % M) + M) % M; // Ensure positive modulo
            }
            result += ITALIAN_ALPHABET[newIdx];
        }
    }
    return result;
}
int main() {
    cout << "Italian Alphabet Affine Cipher/Decipher\n";
    cout << "Enter message: ";
    string message, temp;
    getline(cin, message);
    int a, b;
    // Input and check multiplicative key
    while (true) {
        cout << "Enter key 'a' (coprime to 22): ";
        cin >> temp; a = 0; bool valid = true;
        for (char c : temp) {
            if (c < '0' || c > '9') { valid = false; break; }
            a = (a * 10 + (c - '0')) % M;
        }
        if (valid && a != 0 && a % 2 != 0 && a % 11 != 0) break;
        cout << "Invalid 'a'. Should be a number coprime to 22 (e.g., 3, 5, 7, ...).\n";
    }
    // Input and check additive key
    while (true) {
        cout << "Enter key 'b': ";
        cin >> temp; b = 0; bool valid = true;
        for (char c : temp) {
            if (c < '0' || c > '9') { valid = false; break; }
            b = (b * 10 + (c - '0')) % M;
        }
        if (valid) break;
        cout << "Invalid 'b'. Enter a valid number.\n";
    }
    string ciphered = affineCipher(message, a, b, false);
    cout << "Ciphered:   " << ciphered << endl;
    cout << "Deciphered: " << affineCipher(ciphered, a, b, true) << endl;
    return 0;
}