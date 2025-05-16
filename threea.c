#3a

//vigenere 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void encrypt(const char plaintext[], const char key[], char ciphertext[]) {
    int i, j = 0;
    int len_plaintext = strlen(plaintext);
    int len_key = strlen(key);

    for (i = 0; i < len_plaintext; i++) {
        if (isalpha(plaintext[i])) {
            char plain_char = toupper(plaintext[i]);
            char key_char = toupper(key[j % len_key]);
            ciphertext[i] = ((plain_char - 'A' + key_char - 'A') % ALPHABET_SIZE) + 'A';
            j++;
        } else {
            ciphertext[i] = plaintext[i]; // Copy non-alphabet characters as is
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the string
}

void decrypt(const char ciphertext[], const char key[], char plaintext[]) {
    int i, j = 0;
    int len_ciphertext = strlen(ciphertext);
    int len_key = strlen(key);

    for (i = 0; i < len_ciphertext; i++) {
        if (isalpha(ciphertext[i])) {
            char cipher_char = toupper(ciphertext[i]);
            char key_char = toupper(key[j % len_key]);
            plaintext[i] = ((cipher_char - key_char + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
            j++;
        } else {
            plaintext[i] = ciphertext[i]; // Copy non-alphabet characters as is
        }
    }
    plaintext[i] = '\0'; // Null-terminate the string
}

void print_vigenere_table() {
    printf("\nVigenère Table:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            printf("%c ", 'A' + (i + j) % ALPHABET_SIZE);
        }
        printf("\n");
    }
}

int main() {
    char plaintext[100], key[100], encryptedText[100], decryptedText[100];

    printf("Enter the plaintext: ");
    scanf(" %[^\n]%*c", plaintext);  // Reads full line with spaces


    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    print_vigenere_table();

    encrypt(plaintext, key, encryptedText);
    printf("\nEncrypted Text: %s\n", encryptedText);

    decrypt(encryptedText, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
