#include<stdio.h>
#include<cs50.h>

int main(void)
{
    bool odd = true;
    int sumOdd = 0;
    int sumEven = 0;
    bool isAmex = false, isVisa = false, isMC = false;
    int length = 0;
    long creditCard = get_long("Number: ");
    while (creditCard != 0)
    {
        // check each digit and add sum
        if (odd)
        {
            sumOdd += creditCard % 10;
            odd = !odd;
        }
        else
        {
            int tmp = creditCard % 10;
            tmp *= 2;
            sumEven = sumEven + tmp % 10 + tmp / 10;
            odd = !odd;
        }

        // check the first two or the first digits and determine card type
        if (creditCard >= 51 && creditCard <= 55)
        {
            isMC = true;
        }
        else if (creditCard == 34 || creditCard == 37)
        {
            isAmex = true;
        }
        else if (creditCard == 4)
        {
            isVisa = true;
        }

        // go to next digit
        creditCard = creditCard / 10;
        length ++;
    }
    int sumAll = sumOdd + sumEven;
    if (sumAll % 10 != 0)
    {
        // invalid card type
        printf("INVALID\n");
    }
    else
    {
        // valid card type
        if (isMC && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (isVisa && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else if (isAmex && length == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}