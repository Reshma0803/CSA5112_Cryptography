#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
#define BLOCK_SIZE 8
void pad_data(unsigned char *data, int *length)
{
    int padding = BLOCK_SIZE - (*length % BLOCK_SIZE);
    data[*length] = 0x80;
    for (int i = 1; i < padding; i++)
    {
        data[*length + i] = 0x00;
    }
    *length += padding;
}
void print_data(const char *label, unsigned char *data, int length)
{
    printf("%s", label);
    for (int i = 0; i < length; i++)
    {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
int main()
{
    DES_cblock key = {'1','2','3','4','5','6','7','8'};
    DES_cblock iv = {'A','B','C','D','E','F','G','H'};
    DES_key_schedule key_schedule;
    DES_set_key_unchecked(&key, &key_schedule);
    unsigned char plaintext[256];
    unsigned char ecb[256], cbc[256], cfb[256];
    int length;
    printf("Enter plaintext: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    length = strlen((char *)plaintext);
    if (length > 0 && plaintext[length - 1] == '\n')
        length--;
    pad_data(plaintext, &length);
    printf("\nOriginal Plaintext: %s\n", plaintext);
    for (int i = 0; i < length; i += BLOCK_SIZE)
    {
        DES_ecb_encrypt(
            (DES_cblock *)(plaintext + i),
            (DES_cblock *)(ecb + i),
            &key_schedule,
            DES_ENCRYPT
        );
    }
    print_data("\nECB Ciphertext: ", ecb, length);
    DES_ncbc_encrypt(
        plaintext,
        cbc,
        length,
        &key_schedule,
        &iv,
        DES_ENCRYPT
    );
    print_data("CBC Ciphertext: ", cbc, length);
    DES_cblock cfb_iv = {'A','B','C','D','E','F','G','H'};
    DES_cfb_encrypt(
        plaintext,
        cfb,
        8,
        length,
        &key_schedule,
        &cfb_iv,
        DES_ENCRYPT
    );
    print_data("CFB Ciphertext: ", cfb, length);
    return 0;
}
