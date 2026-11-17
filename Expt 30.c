
#include <stdio.h>

int encrypt(int block, int key)
{
    return block ^ key;
}

int cbc_mac(int *message, int length, int key)
{
    int state = 0;

    for (int i = 0; i < length; i++)
    {
        state = encrypt(state ^ message[i], key);
    }

    return state;
}

int main()
{
    int key = 0x5A;
    int X = 0x35;

    int T = cbc_mac(&X, 1, key);

    int second_block = X ^ T;

    int message[2] = {X, second_block};

    int forged_mac = cbc_mac(message, 2, key);

    printf("CBC-MAC DEMONSTRATION\n");
    printf("---------------------\n");

    printf("Secret Key: %02X\n", key);
    printf("One Block Message X: %02X\n", X);

    printf("\nMAC of One Block Message:\n");
    printf("T = %02X\n", T);

    printf("\nTwo Block Message:\n");
    printf("Block 1: %02X\n", message[0]);
    printf("Block 2 (X XOR T): %02X\n", message[1]);

    printf("\nMAC of Two Block Message:\n");
    printf("Forged MAC: %02X\n", forged_mac);

    if (T == forged_mac)
        printf("\nMAC values are equal.\n");
    else
        printf("\nMAC values are different.\n");

    printf("CBC-MAC forgery demonstrated successfully.\n");

    return 0;
}
