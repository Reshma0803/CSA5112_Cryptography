#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main() {
    EVP_CIPHER_CTX *ctx;
    unsigned char key[24] = "123456789012345678901234";
    unsigned char iv[8] = "12345678";
    unsigned char plaintext[1024];
    unsigned char ciphertext[1040];
    int len, ciphertext_len;

    printf("Enter plaintext: ");
    if (fgets((char *)plaintext, sizeof(plaintext), stdin) == NULL)
        return 1;

    plaintext[strcspn((char *)plaintext, "\n")] = '\0';

    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        printf("Context creation failed.\n");
        return 1;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(),
                           NULL, key, iv) != 1) {
        printf("Encryption initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    if (EVP_EncryptUpdate(ctx, ciphertext, &len,
                          plaintext, strlen((char *)plaintext)) != 1) {
        printf("Encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
        printf("Final encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    ciphertext_len += len;

    printf("Encrypted ciphertext (hex): ");
    for (int i = 0; i < ciphertext_len; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
