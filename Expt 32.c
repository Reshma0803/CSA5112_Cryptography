
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int power(int base, int exp, int mod)
{
    int result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main()
{
    int p = 23;
    int q = 11;
    int g = 2;
    int x = 3;
    int h = 7;

    int k1 = 4;
    int k2 = 7;

    int r1, r2, s1, s2;
    int rsa1, rsa2;

    printf("DSA AND RSA SIGNATURE COMPARISON\n");
    printf("--------------------------------\n");

    r1 = power(g, k1, p) % q;
    s1 = ((h + x * r1) * 3) % q;

    r2 = power(g, k2, p) % q;
    s2 = ((h + x * r2) * 8) % q;

    printf("Original Message Hash: %d\n", h);

    printf("\nDSA Signatures:\n");
    printf("First Signature: (%d, %d)\n", r1, s1);
    printf("Second Signature: (%d, %d)\n", r2, s2);

    printf("\nRSA Signatures:\n");

    rsa1 = power(h, 3, 33);
    rsa2 = power(h, 3, 33);

    printf("First Signature: %d\n", rsa1);
    printf("Second Signature: %d\n", rsa2);

    if (r1 != r2 || s1 != s2)
        printf("\nDSA produces different signatures.\n");

    if (rsa1 == rsa2)
        printf("RSA produces identical signatures.\n");

    return 0;
}
