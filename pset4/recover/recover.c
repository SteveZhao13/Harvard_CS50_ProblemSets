#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char BYTE;
#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: recover filename\n");
        return 1;
    }

    // open the raw data
    FILE *f_raw = fopen(argv[1], "r");
    if (f_raw == NULL)
    {
        printf("Error opening when reading the card file!\n");
        return 1;
    }

    // variables
    int count = 0;
    BYTE buffer[BUFFER_SIZE];
    bool start_jpeg = false;
    bool end_of_file = false;
    char *jpeg_name = malloc(10);
    int num_byte = BUFFER_SIZE;

    while (1)
    {
        int ret = fread(buffer, sizeof(BYTE), num_byte, f_raw);
        // check if the end of file is reached
        if (ret < 512)
        {
            num_byte = ret;
            end_of_file = true;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            count ++;
            sprintf(jpeg_name, "%03i.jpg", count - 1);
            FILE *f_jpeg = fopen(jpeg_name, "w");
            if (f_jpeg == NULL)
            {
                printf("Error opening a file when writing jpeg!\n");
                return 1;
            }
            fwrite(buffer, sizeof(BYTE), num_byte, f_jpeg);
            fclose(f_jpeg);
            // if has NOT found the start, this is the start
            if (!start_jpeg)
            {
                start_jpeg = true;
            }
        }
        else
        {
            // if the start of the first jpeg has been found, then this would be writting to the current file
            if (start_jpeg)
            {
                // continue writing
                FILE *f_jpeg = fopen(jpeg_name, "a");
                fwrite(buffer, sizeof(BYTE), num_byte, f_jpeg);
                fclose(f_jpeg);
            }
            // if has NOT found the start, skip and continue next loop
            else
            {
                continue;
            }
        }

        // check if the end of file is reached
        if (end_of_file)
        {
            break;
        }
    }

    free(jpeg_name);
    fclose(f_raw);
    return 0;
}