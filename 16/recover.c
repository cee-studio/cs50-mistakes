#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { // this counter to keep track of how many
                                   // jpegs found so far int counter = 0;

  // allocate a place with 8 characters for inputting the filename
  char filename[8];
  // replace argv[1] with card
  char *card = argv[1];
  // create a pointer called img
  FILE *img;

  // check that if user did not give any inputs, to return
  if (argc != 2) {
    printf("Usage: ./recover image \n");
    return 1;
  }

  // open up file and read the file
  FILE *file = fopen(card, "r");
  if (!file) {
    printf("Could not open card\n");
    return 1;
  }

  // declare a buffer
  unsigned char buffer[512];
  int counter = 0;

  // iterate over contents of the file till the end of the file
  while (fread(buffer, 512, 1, file) == 512) {
    // if first 4 bys of the array are as per the below
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0) {
      // if this is the 1st JPEG that someone is working on
      if (counter == 0) {
        // create a new jpeg file
        sprintf(filename, "%03i.jpg", counter);
        counter++;

        // open this new jpeg file
        img = fopen(filename, "w");

        // start writing to this new jpeg, need a number that is based on how
        // many times before the next "start" of the jpeg file
        fwrite(buffer, 512, 1, img);
      }

      // if this is not the 1st JPEG
      if (counter > 0) {
        // close the file at location img that was being written to
        fclose(img);

        // create a new jpeg file
        sprintf(filename, "%03i.jpg", counter);
        counter++;

        // open this new jpeg file
        img = fopen(filename, "w");

        // start writing to this new jpeg, need a number that is based on how
        // many times before the next "start" of the jpeg file
        fwrite(buffer, 512, 1, img);
      }
    }
    // to continue writing if there was a JPEG found before previously
    else if (counter > 0 && fread(buffer, 512, 1, file) == 512) {
      // continue writing to this new jpeg
      fwrite(buffer, 512, 1, img);
    }
    // in case the first 512 bytes are not a jpeg, to ignore and continue with
    // next set of 512 bytes
    else {
      continue;
    }
  }

  // close file
  fclose(img);
  fclose(file);
}
