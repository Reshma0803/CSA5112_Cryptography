#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
#include <openssl/evp.h>

int main(void)
{
    unsigned char key[24] = "123456789012345678901234";
    unsigned char iv[8] = "12345678";
    unsigned char plaintext[256];
    unsigned char ciphertext[272];

    int len, ciphertext_len;

    printf("Enter plaintext: ");
    if (fgets((char *)plaintext, sizeof(plaintext), stdin) == NULL)
        return 1;

    len = strlen((char *)plaintext);

    if (len > 0 && plaintext[len - 1] == '\n')
        plaintext[--len] = '\0';

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

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

    if (EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len,
                          plaintext, len) != 1) {
        printf("Encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    int final_len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + ciphertext_len,
                            &final_len) != 1) {
        printf("Final encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    ciphertext_len += final_len;

    printf("\nCiphertext (hex): ");
    for (int i = 0; i < ciphertext_len; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
