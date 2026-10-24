#include <stdio.h>
#include <math.h>
int main() {
    long double keys = 1.0L;
    int i;
    for (i = 1; i <= 25; i++) {
        keys *= i;
    }
    printf("PLAYFAIR CIPHER - KEY ANALYSIS\n");
    printf("--------------------------------\n");
    printf("a) Total possible keys = 25!\n");
    printf("   Approximate number = 1.5511210043 x 10^25\n");
    printf("   Approximate power of 2 = 2^83.68\n");
    printf("   Answer = 2^84\n");
    printf("\nb) Effectively unique keys\n");
    printf("   Approximate power of 2 = 2^62\n");
    return 0;
}
