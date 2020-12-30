#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tmp_blue, tmp_green, tmp_red;
            tmp_blue = image[i][j].rgbtBlue;
            tmp_green = image[i][j].rgbtGreen;
            tmp_red = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtBlue = tmp_blue;
            image[i][width - 1 - j].rgbtGreen = tmp_green;
            image[i][width - 1 - j].rgbtRed = tmp_red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double count = 0;
            int sum_blue = 0, sum_green = 0, sum_red = 0;
            int blur_blue, blur_green, blur_red;
            for (int k = -1; k <= 1; k++)
            {
                for (int w = -1; w <= 1; w++)
                {
                    if ((i + k) < 0 || (i + k) >= height || (j + w) < 0 || (j + w) >= width)
                    {
                        continue;
                    }
                    sum_blue += image[i + k][j + w].rgbtBlue;
                    sum_green += image[i + k][j + w].rgbtGreen;
                    sum_red += image[i + k][j + w].rgbtRed;
                    count ++;
                }
            }
            blur_blue = round(sum_blue / count);
            blur_green = round(sum_green / count);
            blur_red = round(sum_red / count);
            image_copy[i][j].rgbtBlue = blur_blue;
            image_copy[i][j].rgbtGreen = blur_green;
            image_copy[i][j].rgbtRed = blur_red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_blue_x = 0, sum_green_x = 0, sum_red_x = 0;
            int sum_blue_y = 0, sum_green_y = 0, sum_red_y = 0;
            int edge_blue, edge_green, edge_red;
            for (int k = -1; k <= 1; k++)
            {
                for (int w = -1; w <= 1; w++)
                {
                    if ((i + k) < 0 || (i + k) >= height || (j + w) < 0 || (j + w) >= width)
                    {
                        continue;
                    }
                    // calculate Gx directory
                    sum_blue_x += Gx[1 + k][1 + w] * image[i + k][j + w].rgbtBlue;
                    sum_green_x += Gx[1 + k][1 + w] * image[i + k][j + w].rgbtGreen;
                    sum_red_x += Gx[1 + k][1 + w] * image[i + k][j + w].rgbtRed;
                    // calculate Gy directory
                    sum_blue_y += Gy[1 + k][1 + w] * image[i + k][j + w].rgbtBlue;
                    sum_green_y += Gy[1 + k][1 + w] * image[i + k][j + w].rgbtGreen;
                    sum_red_y += Gy[1 + k][1 + w] * image[i + k][j + w].rgbtRed;
                }
            }
            edge_blue = sum_blue_x * sum_blue_x + sum_blue_y * sum_blue_y;
            edge_green = sum_green_x * sum_green_x + sum_green_y * sum_green_y;
            edge_red = sum_red_x * sum_red_x + sum_red_y * sum_red_y;
            image_copy[i][j].rgbtBlue = round(sqrt(edge_blue)) > 255 ? 255 : round(sqrt(edge_blue)); // cap to 255
            image_copy[i][j].rgbtGreen = round(sqrt(edge_green)) > 255 ? 255 : round(sqrt(edge_green));
            image_copy[i][j].rgbtRed = round(sqrt(edge_red)) > 255 ? 255 : round(sqrt(edge_red));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
    return;
}
