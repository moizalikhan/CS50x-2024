// Class work:
#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = (int)round(average);
            image[i][j].rgbtGreen = (int)round(average);
            image[i][j].rgbtRed = (int)round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if ((int)sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if ((int)sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if ((int)sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = (int)round(sepiaBlue);
            image[i][j].rgbtGreen = (int)round(sepiaGreen);
            image[i][j].rgbtRed = (int)round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int actual_width = width - 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE Buffer = image[i][j];
            image[i][j] = image[i][actual_width - j];
            image[i][actual_width - j] = Buffer;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copied_of_original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copied_of_original[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumofRed = 0, sumofGreen = 0, sumofBlue = 0;
            int count0fpixels = 0;
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + row >= 0 && i + row < height && j + col >= 0 && j + col < width)
                    {
                        sumofRed += copied_of_original[i + row][j + col].rgbtRed;
                        sumofGreen += copied_of_original[i + row][j + col].rgbtGreen;
                        sumofBlue += copied_of_original[i + row][j + col].rgbtBlue;
                        count0fpixels++;
                    }
                }
            }

            float computed_Red_one = (float)sumofRed / count0fpixels;
            float computed_Green_one = (float)sumofGreen / count0fpixels;
            float computed_Blue_one = (float)sumofBlue / count0fpixels;

            image[i][j].rgbtRed = round(computed_Red_one);
            image[i][j].rgbtGreen = round(computed_Green_one);
            image[i][j].rgbtBlue = round(computed_Blue_one);
        }
    }
}

// file recoverer
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *memorycard = fopen(argv[1], "r");
    if (memorycard == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // While there's still data left to read from the memory card

    // Creating a buffer for holding data of block 512B after reading
    uint8_t buffer[512];

    int jpegs_counter = 0;
    FILE *jpegs = NULL;

    // reading the raw file data
    while (fread(buffer, 1, 512, memorycard) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpegs != NULL)
            {
                fclose(jpegs);
            }

            // new jpeg
            char file[8];
            sprintf(file, "%03i.jpg", jpegs_counter++);
            jpegs = fopen(file, "w");

            if (jpegs == NULL)
            {
                fclose(memorycard);
                fprintf(stderr, "Could not create JPEG file %s\n", file);
                return 2;
            }
        }

        // writing data
        if (jpegs != NULL)
        {
            fwrite(buffer, 1, 512, jpegs);
        }
    }

    // closing the files
    if (jpegs != NULL)
    {
        fclose(jpegs);
    }

    fclose(memorycard);
    return 0;
}