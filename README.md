# Cipher-Decipher

An implementation of the Affine Cipher built on the Italian alphabet. This project encrypts and decrypts messages using modular arithmetic and hand-tuned code logic, with complete support for the 21-letter Italian alphabet and space.

## Table of Contents

- [System Overview](#system-overview)
- [Alphabet](#alphabet)
- [Mathematical Foundation](#mathematical-foundation)
- [Encryption Example](#encryption-example)
- [Decryption Example](#decryption-example)
- [Code Highlights](#code-highlights)
- [Building & Running](#building--running)
- [License](#license)

---

## System Overview

This project implements **Affine Cipher** encryption, a type of monoalphabetic substitution cipher. Each character in the Italian alphabet (plus space) is mapped to an index, transformed using a mathematical formula, then converted back to text.

- Each letter is mapped to a numeric equivalent (0 to 21).
- Encryption uses the formula: `(a * x + b) % M`
- Decryption uses: `a_inverse * (y - b) % M`
- The cipher keys `a` (multiplier) and `b` (shift) are parameters.

## Alphabet

The cipher uses this custom "Italian" alphabet:
```
"ABCDEFGHILMNOPQRSTUVZ "
```
- 21 letters + space
- Indices run from 0 (A) to 21 (space)

| Index | Char |
|-------|------|
| 0     |   A  |
| 1     |   B  |
| 2     |   C  |
| 3     |   D  |
| 4     |   E  |
| 5     |   F  |
| 6     |   G  |
| 7     |   H  |
| 8     |   I  |
| 9     |   L  |
| 10    |   M  |
| 11    |   N  |
| 12    |   O  |
| 13    |   P  |
| 14    |   Q  |
| 15    |   R  |
| 16    |   S  |
| 17    |   T  |
| 18    |   U  |
| 19    |   V  |
| 20    |   Z  |
| 21    | Space|

**Alphabet length (M):** `M = 22`

## Mathematical Foundation

### Encryption

```
EncryptedIndex = (a * x + b) % M
```
- `x` = index of original character
- `a` = multiplicative key (must be coprime with M=22)
- `b` = additive (shift) key
- `M` = 22 (alphabet length)

### Decryption

```
DecryptedIndex = a_inverse * (y - b) % M
```
- `y` = index of encrypted character
- `a_inverse` = modular inverse of `a` modulo `M`
- Find `a_inverse` such that: `(a * a_inverse) % M == 1`

### Negative Modulo Handling

Because C++'s `%` operator can result in negative numbers, the code ensures indices wrap into the valid range:
```cpp
newIndex = ((value % M) + M) % M;
```

### Example Key Parameters

- `a = 5` (must be coprime to 22)
- `b = 7`

## Encryption Example

**Message:**  
``SONO UNO STUDENTE ANZIANO``

**Step 1: Map each character to its index using the alphabet above.**

**Step 2: Apply the encryption function (`(5 * x + 7) % 22`).**

| Plain | Index (x) | Enc. Value | Enc. Index | Cipher Char |
|-------|-----------|------------|------------|-------------|
| S     |   16      | 87         | 21         | (Space)     |
| O     |   12      | 67         | 1          | B           |
| N     |   11      | 62         | 18         | U           |
| O     |   12      | 67         | 1          | B           |
| ...   |           | ...        | ...        | ...         |

**Encrypted message:**  
```
 BUBCLUBC ELAFUEFCHUVDHUB
```
(see the hand analysis for full details)

## Decryption Example

To decrypt, you need the modular inverse of `a`.  
- For `a = 5`, `a_inverse = 9` because `(5 * 9) % 22 = 1`.

**Apply:**  
``DecryptedIndex = 9 * (EncryptedIndex - 7) % 22``  
Correct for negatives as per code.

**Example:**  
| Cipher Char | Index (y) | (y-b) | 9*(y-b) | Final Index | Plain Char |
|-------------|-----------|-------|---------|-------------|------------|
| (Space)     | 21        | 14    | 126     | 16          | S          |
| B           | 1         | -6    | -54     | 12          | O          |
| U           | 18        | 11    | 99      | 11          | N          |

Continuing, you'll recover the original "SONO UNO STUDENTE ANZIANO".

## Code Highlights

- **Coprime Check:** The code checks that `a` is coprime to 22 (not divisible by 2 or 11).
- **Modular Inverse:** Computed via looping to find an integer x where `(a * x) % 22 == 1`.
- **Negative Indices:** Ensures negative values wrap to valid character indices.
- **Space Handling:** Treats the space as a valid character at index 21.

## Building & Running

1. Clone the repository
2. Ensure you have a C++ compiler (supports C++11 or higher)
3. Build your code:
    ```sh
    g++ -o cipher main.cpp
    ```
4. Run the program!
    ```sh
    ./cipher
    ```

## License

This project is licensed under the [MIT License](LICENSE).

---

## References

- [Affine cipher – Wikipedia](https://en.wikipedia.org/wiki/Affine_cipher)
- See the code and worked examples for deeper understanding.
