#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    if (argc == ! 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Opens file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Invalid File\n");
        return 1;
    }

    BYTE byte[512];
    int counter = 0;
    while ((fread(byte, 512, 1, card)) == 1)
    {
        BYTE buffer[512];
        char filename[8];
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If its a new JPEG
            if (counter == 0)
            {
                counter++;
                sprintf(filename, "%03i.jpg", counter);
                FILE *img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                fclose(img);
            }
            //For an existing JPEG file
            else
            {
                //For an existing file
                sprintf(filename, "%03i.jpg", counter);
                FILE *img = fopen(filename, "a");
                fwrite(buffer, 512, 1, img);
                fclose(img);
            }
        }
        //If file is not JPEG
        else
        {
            return 0;
        }
        free(filename);
    }
    //Close file
    fclose(card);
}