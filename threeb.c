#3b

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_spaces(char *text, char *no_spaces) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ') {
            no_spaces[j++] = text[i];
        }
    }
    no_spaces[j] = '\0';
}

void rail_fence_encrypt(char text[], int rails, char encrypted[]) {
    int len = strlen(text);
    if (rails == 1) {
        strcpy(encrypted, text);
        return;
    }

    char rail_matrix[rails][len];
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail_matrix[i][j] = '\0';

    int row = 0, col = 0, direction = 1;
    for (int i = 0; i < len; i++) {
        rail_matrix[row][col++] = text[i];
        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;
        row += direction;
    }

    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail_matrix[i][j] != '\0') {
                encrypted[index++] = rail_matrix[i][j];
            }
        }
    }
    encrypted[index] = '\0';
}

void rail_fence_decrypt(char text[], int rails, char decrypted[], const char *original_text) {
    int len = strlen(text);
    if (rails == 1) {
        strcpy(decrypted, text);
        return;
    }

    char rail_matrix[rails][len];
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail_matrix[i][j] = '\0';

    int row = 0, col = 0, direction = 1;

    for (int i = 0; i < len; i++) {
        rail_matrix[row][col++] = '*';
        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;
        row += direction;
    }

    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail_matrix[i][j] == '*' && index < len) {
                rail_matrix[i][j] = text[index++];
            }
        }
    }

    row = 0, col = 0, direction = 1;
    index = 0;
    for (int i = 0; i < len; i++) {
        decrypted[index++] = rail_matrix[row][col++];
        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;
        row += direction;
    }
    decrypted[index] = '\0';

    // Re-insert spaces based on original text
    int d_idx = 0;
    for (int i = 0; original_text[i] != '\0'; i++) {
        if (original_text[i] == ' ') {
            int len_d = strlen(decrypted);
            memmove(decrypted + d_idx + 1, decrypted + d_idx, len_d - d_idx + 1); // Shift right
            decrypted[d_idx] = ' ';
            d_idx++;
        }
        d_idx++;
    }
}

int main() {
    char text[100], encrypted[100], decrypted[100], no_spaces[100];
    int rails;

    printf("Enter the message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline

    printf("Enter the number of rails: ");
    scanf("%d", &rails);
    getchar(); // Clear newline from buffer

    remove_spaces(text, no_spaces);

    rail_fence_encrypt(no_spaces, rails, encrypted);
    printf("Encrypted Message: %s\n", encrypted);

    rail_fence_decrypt(encrypted, rails, decrypted, text);
    printf("Decrypted Message: %s\n", decrypted);

    return 0;
}
