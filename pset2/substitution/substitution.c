#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    // if usage is wrong, print error message and return 1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // if cipher length is not 26, print error message and return 1
    int len_key = strlen(argv[1]);
    if (len_key != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // check each letter
    char cipher[27] = {'\0'};
    char check_duplicate[27] = {'\0'};
    for (int i = 0; i < len_key; i++)
    {
        // if contains char that is not a letter, print error message and return 1
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        cipher[i] = toupper(argv[1][i]);
        check_duplicate[toupper(argv[1][i]) - 'A'] = toupper(argv[1][i]);
    }
    // if contains the same letter, print error message and return 1
    if (strlen(check_duplicate) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // cipher the sentence
    char *input = get_string("plaintext: ");
    char *output = malloc(strlen(input) + 1);
    printf("ciphertext: ");
    for (int i = 0,  len_text = strlen(input); i < len_text; i++)
    {
        if (!isalpha(input[i]))
        {
            output[i] = input[i];
        }
        else
        {
            if (islower(input[i]))
            {
                output[i] = tolower(cipher[input[i] - 'a']);
            }
            else
            {
                output[i] = cipher[input[i] - 'A'];
            }
        }
        printf("%c", output[i]);
    }
    printf("\n");
    return 0;
}