// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Open card.raw file in read mode
    FILE *fp = fopen(argv[1], "r");

    // Check for NULL
    if (!fp)
    {
        printf("Error\n");
        fclose(fp);
        return 1;
    }

    // Storage to store 1 block
    unsigned char buffer[512];

    // Loop till EOF (end of the file)
    while (fread(buffer, sizeof(unsigned char), 512, fp) != 0)
    {
        // Your code goes here
    }

    // End the program
    fclose(fp);
    return 0;
}
