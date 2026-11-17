#include <stdio.h>

int main()
{
    int total_lanes = 25;
    int block_size = 1024;
    int lane_size = 64;

    int rate_lanes = block_size / lane_size;
    int capacity_lanes = total_lanes - rate_lanes;

    int zero_lanes = capacity_lanes;
    int blocks = 0;

    printf("SHA-3 CAPACITY LANE ANALYSIS\n");
    printf("----------------------------\n");

    printf("Total State Size: 1600 bits\n");
    printf("Block Size: %d bits\n", block_size);
    printf("Lane Size: %d bits\n", lane_size);
    printf("Total Lanes: %d\n", total_lanes);
    printf("Rate Lanes: %d\n", rate_lanes);
    printf("Capacity Lanes: %d\n", capacity_lanes);

    printf("\nInitial Zero Lanes: %d\n", zero_lanes);

    while (zero_lanes > 0)
    {
        blocks++;

        int affected = rate_lanes;

        if (affected > zero_lanes)
            affected = zero_lanes;

        zero_lanes -= affected;

        printf("After Block %d: Zero Lanes = %d\n",
               blocks, zero_lanes);
    }

    printf("\nAll capacity lanes receive nonzero bits.\n");
    printf("Total Message Blocks Required: %d\n", blocks);

    printf("Total Time: %d block absorption steps\n", blocks);

    return 0;
}
