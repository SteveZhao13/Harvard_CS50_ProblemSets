#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int height;
    while (1)
    {
        height = get_int("Height: ");
        if (height >= 1 && height <= 8)
        {
            break;
        }
    }
    for (int i = 1; i <= height; i++)
    {
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}