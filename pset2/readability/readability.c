#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(void)
{
    int letters = 0, words = 0, sentences = 0;
    char *text = get_string("Text: ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // count letters
        if (isalpha(text[i]))
        {
            letters++;
        }

        // count words
        if (text[i] == ' ')
        {
            words++;
        }

        // count sentences
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    words++; // because we count spaces for words, we lost the last word, therefore we add one more

    // print for debugging
    // printf("Letters: %d\n", letters);
    // printf("Words: %d\n", words);
    // printf("Sentences: %d\n", sentences);

    // calculate L and S and final result
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    int result = round(0.0588 * L - 0.296 * S - 15.8);

    // printf("readability: %d\n", result);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", result);
    }

}
