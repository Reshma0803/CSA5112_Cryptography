#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};
int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
int P4[] = {2, 4, 3, 1};
int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};
int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};
int permute(int value, int *table, int n, int bits)
{
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        result <<= 1;
        result |= (value >> (bits - table[i])) & 1;
    }

    return result;
}
int left_shift(int value, int shifts, int bits)
{
    return ((value << shifts) |
           (value >> (bits - shifts))) & ((1 << bits) - 1);
}

void generate_keys(int key, int *k1, int *k2)
{
    int p = permute(key, P10, 10, 10);

    int left = (p >> 5) & 31;
    int right = p & 31;

    left = left_shift(left, 1, 5);
    right = left_shift(right, 1, 5);

    *k1 = permute((left << 5) | right, P8, 8, 10);

    left = left_shift(left, 2, 5);
    right = left_shift(right, 2, 5);

    *k2 = permute((left << 5) | right, P8, 8, 10);
}

int fk(int value, int key)
{
    int left = (value >> 4) & 15;
    int right = value & 15;

    int expanded = permute(right, EP, 8, 4);
    expanded ^= key;

    int a = (expanded >> 4) & 15;
    int b = expanded & 15;

    int row0 = ((a & 8) >> 2) | (a & 1);
    int col0 = (a >> 1) & 3;

    int row1 = ((b & 8) >> 2) | (b & 1);
    int col1 = (b >> 1) & 3;

    int s = (S0[row0][col0] << 2) |
             S1[row1][col1];

    int result = permute(s, P4, 4, 4);

    return ((left ^ result) << 4) | right;
}

int sdes_encrypt(int plaintext, int k1, int k2)
{
    int value = permute(plaintext, IP, 8, 8);

    value = fk(value, k1);

    value = ((value & 15) << 4) | ((value >> 4) & 15);

    value = fk(value, k2);

    return permute(value, IP_INV, 8, 8);
}

int sdes_decrypt(int ciphertext, int k1, int k2)
{
    int value = permute(ciphertext, IP, 8, 8);

    value = fk(value, k2);

    value = ((value & 15) << 4) | ((value >> 4) & 15);

    value = fk(value, k1);

    return permute(value, IP_INV, 8, 8);
}

int binary_to_int(char *str)
{
    return (int)strtol(str, NULL, 2);
}

void print_binary(int value, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
        printf("%d", (value >> i) & 1);
}

int main()
{
    char plaintext[] = "0000000100100011";
    char key_str[] = "0111111101";
    char iv_str[] = "10101010";

    int key = binary_to_int(key_str);
    int iv = binary_to_int(iv_str);

    int k1, k2;

    generate_keys(key, &k1, &k2);

    int length = strlen(plaintext);
    int blocks = length / 8;

    int pt[100], ct[100], decrypted[100];

    for (int i = 0; i < blocks; i++)
    {
        char temp[9];

        strncpy(temp, plaintext + i * 8, 8);
        temp[8] = '\0';

        pt[i] = binary_to_int(temp);
    }

    printf("S-DES ENCRYPTION AND DECRYPTION USING CBC MODE\n");
    printf("------------------------------------------------\n");

    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %s\n", key_str);
    printf("IV        : %s\n", iv_str);
    int previous = iv;

    for (int i = 0; i < blocks; i++)
    {
        ct[i] = sdes_encrypt(pt[i] ^ previous, k1, k2);
        previous = ct[i];
    }

    printf("\nEncrypted Ciphertext:\n");

    for (int i = 0; i < blocks; i++)
    {
        print_binary(ct[i], 8);
        printf(" ");
    }

    printf("\n");

    previous = iv;

    for (int i = 0; i < blocks; i++)
    {
        decrypted[i] = sdes_decrypt(ct[i], k1, k2) ^ previous;
        previous = ct[i];
    }

    printf("\nDecrypted Plaintext:\n");

    for (int i = 0; i < blocks; i++)
    {
        print_binary(decrypted[i], 8);
        printf(" ");
    }

    printf("\n");

    printf("\nProgram executed successfully.\n");

    return 0;
}
