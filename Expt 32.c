
#include <stdio.h>
#include <stdint.h>

uint64_t generate_subkey64(uint64_t value, uint64_t constant)
{
    if (value & 0x8000000000000000ULL)
        return (value << 1) ^ constant;

    return value << 1;
}

void generate_subkey128(uint64_t high, uint64_t low,
                        uint64_t *k1_high, uint64_t *k1_low,
                        uint64_t *k2_high, uint64_t *k2_low)
{
    uint64_t r_high = 0x8000000000000000ULL;

    *k1_high = (high << 1) | (low >> 63);
    *k1_low = low << 1;

    if (high & r_high)
        *k1_low ^= 0x87;

    *k2_high = (*k1_high << 1) | (*k1_low >> 63);
    *k2_low = *k1_low << 1;

    if (*k1_high & r_high)
        *k2_low ^= 0x87;
}

int main()
{
    uint64_t L64 = 0x8000000000000000ULL;

    uint64_t K1_64 = generate_subkey64(L64, 0x1B);
    uint64_t K2_64 = generate_subkey64(K1_64, 0x1B);

    printf("CMAC SUBKEY GENERATION\n");
    printf("----------------------\n");

    printf("64-bit Block Size:\n");
    printf("Constant: 0x1B\n");
    printf("K1: %016llX\n", (unsigned long long)K1_64);
    printf("K2: %016llX\n", (unsigned long long)K2_64);

    uint64_t high = 0x8000000000000000ULL;
    uint64_t low = 0x0000000000000000ULL;

    uint64_t k1_high, k1_low, k2_high, k2_low;

    generate_subkey128(high, low,
                       &k1_high, &k1_low,
                       &k2_high, &k2_low);

    printf("\n128-bit Block Size:\n");
    printf("Constant: 0x87\n");

    printf("K1: %016llX%016llX\n",
           (unsigned long long)k1_high,
           (unsigned long long)k1_low);

    printf("K2: %016llX%016llX\n",
           (unsigned long long)k2_high,
           (unsigned long long)k2_low);

    return 0;
}
