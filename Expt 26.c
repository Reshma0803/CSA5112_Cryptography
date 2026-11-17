
#include <stdio.h>

long long power(int base, int exp, int mod)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = ((long long)base * base) % mod;
        exp /= 2;
    }

    return result;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    int p = 59, q = 61;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 31;
    int d = 3031;

    int new_e = 7;
    int new_d = 0;

    for (int i = 1; i < phi; i++)
    {
        if ((new_e * i) % phi == 1)
        {
            new_d = i;
            break;
        }
    }

    int message = 123;

    long long cipher = power(message, new_e, n);
    long long decrypted = power(cipher, new_d, n);

    printf("RSA PUBLIC KEY ENCRYPTION\n");
    printf("-------------------------\n");

    printf("Modulus (n): %d\n", n);
    printf("Old Public Key (e): %d\n", e);
    printf("Leaked Private Key (d): %d\n", d);

    printf("\nNew Public Key (e): %d\n", new_e);
    printf("New Private Key (d): %d\n", new_d);

    printf("\nOriginal Message: %d\n", message);
    printf("Encrypted Message: %lld\n", cipher);
    printf("Decrypted Message: %lld\n", decrypted);

    if (gcd(new_e, phi) == 1)
        printf("\nNew key pair is mathematically valid.\n");

    printf("Security Warning: Reusing the old modulus is NOT SAFE.\n");

    return 0;
}
