#include <stdio.h>

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

int main()
{
    int n = 3599;
    int e = 31;
    int blocks[] = {59, 120, 180};
    int count = 3;

    printf("RSA BLOCK ENCRYPTION\n");
    printf("--------------------\n");

    printf("Public Key: (%d, %d)\n", e, n);

    for (int i = 0; i < count; i++)
    {
        int gcd_value = gcd(blocks[i], n);

        long long cipher = power(blocks[i], e, n);

        printf("\nPlaintext Block: %d\n", blocks[i]);
        printf("Encrypted Block: %lld\n", cipher);
        printf("GCD with n: %d\n", gcd_value);

        if (gcd_value > 1 && gcd_value < n)
        {
            printf("Common factor found: %d\n", gcd_value);
            printf("RSA modulus can be factored.\n");
        }
        else
        {
            printf("No non-trivial common factor found.\n");
        }
    }

    return 0;
}
