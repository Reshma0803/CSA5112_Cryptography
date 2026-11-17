
#include <stdio.h>

long long power(long long base, long long exp, long long mod)
{
    long long result = 1;

    base = base % mod;

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
    int q = 23;
    int a = 5;

    int alice_secret = 6;
    int bob_secret = 15;

    long long alice_public;
    long long bob_public;

    long long alice_key;
    long long bob_key;

    printf("DIFFIE-HELLMAN KEY EXCHANGE\n");
    printf("---------------------------\n");

    printf("Public Prime Number (q): %d\n", q);
    printf("Public Base Number (a): %d\n", a);

    alice_public = power(a, alice_secret, q);
    bob_public = power(a, bob_secret, q);

    printf("\nAlice Secret Number: %d\n", alice_secret);
    printf("Bob Secret Number: %d\n", bob_secret);

    printf("\nAlice Public Value: %lld\n", alice_public);
    printf("Bob Public Value: %lld\n", bob_public);

    alice_key = power(bob_public, alice_secret, q);
    bob_key = power(alice_public, bob_secret, q);

    printf("\nAlice Shared Key: %lld\n", alice_key);
    printf("Bob Shared Key: %lld\n", bob_key);

    if (alice_key == bob_key)
        printf("\nShared Secret Key Established Successfully.\n");
    else
        printf("\nKey Exchange Failed.\n");

    return 0;
}
