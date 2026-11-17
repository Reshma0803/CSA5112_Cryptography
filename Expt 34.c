
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define BLOCK_SIZE 16

void printHex(const char *label, unsigned char *data, int len) {
    printf("%s", label);
    for (int i = 0; i < len; i++)
        printf("%02X", data[i]);
    printf("\n");
}

int encrypt(unsigned char *input, int len,
            unsigned char *output, const unsigned char *key,
            const unsigned char *iv, const EVP_CIPHER *cipher,
            int decrypt) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int out1 = 0, out2 = 0;

    if (ctx == NULL)
        return -1;

    if (EVP_CipherInit_ex(ctx, cipher, NULL, key, iv, !decrypt) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0);

    if (EVP_CipherUpdate(ctx, output, &out1, input, len) != 1 ||
        EVP_CipherFinal_ex(ctx, output + out1, &out2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    EVP_CIPHER_CTX_free(ctx);
    return out1 + out2;
}

int main() {
    unsigned char key[16] = "1234567890123456";
    unsigned char iv[16] = "abcdefghijklmnop";
    unsigned char plaintext[1024];
    unsigned char padded[1040];
    unsigned char encrypted[1040];
    unsigned char decrypted[1040];

    int len, paddedLen, decLen;

    printf("Enter plaintext: ");
    if (fgets((char *)plaintext, sizeof(plaintext), stdin) == NULL)
        return 1;

    len = strlen((char *)plaintext);

    if (len > 0 && plaintext[len - 1] == '\n')
        len--;

    if (len == 0) {
        printf("Plaintext cannot be empty.\n");
        return 1;
    }

    paddedLen = ((len / BLOCK_SIZE) + 1) * BLOCK_SIZE;

    memcpy(padded, plaintext, len);
    padded[len] = 0x80;
    memset(padded + len + 1, 0, paddedLen - len - 1);

    printf("\nOriginal Plaintext: %.*s\n", len, plaintext);

    const EVP_CIPHER *ciphers[] = {
        EVP_aes_128_ecb(),
        EVP_aes_128_cbc(),
        EVP_aes_128_cfb128()
    };

    const char *names[] = {
        "ECB MODE",
        "CBC MODE",
        "CFB MODE"
    };

    for (int i = 0; i < 3; i++) {
        printf("\n--- %s ---\n", names[i]);

        const unsigned char *modeIV =
            (i == 0) ? NULL : iv;

        int encLen = encrypt(padded, paddedLen, encrypted,
                             key, modeIV, ciphers[i], 0);

        if (encLen < 0) {
            printf("Encryption failed.\n");
            return 1;
        }

        printHex("Encrypted Data: ", encrypted, encLen);

        decLen = encrypt(encrypted, encLen, decrypted,
                         key, modeIV, ciphers[i], 1);

        if (decLen < 0) {
            printf("Decryption failed.\n");
            return 1;
        }

        int originalLen = decLen - 1;

        while (originalLen >= 0 && decrypted[originalLen] == 0)
            originalLen--;

        if (originalLen < 0 || decrypted[originalLen] != 0x80) {
            printf("Invalid padding.\n");
            return 1;
        }

        printHex("Decrypted Data: ", decrypted, decLen);

        printf("Recovered Plaintext: ");
        fwrite(decrypted, 1, originalLen, stdout);
        printf("\n");
    }

    return 0;
}
