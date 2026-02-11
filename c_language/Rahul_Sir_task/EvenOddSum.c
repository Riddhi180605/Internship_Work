#include <stdio.h>
#include <conio.h>

int evenSumFun(int no);
int oddSumFun(int no);
int sumFun(int no);

int main()
{
    int no, evenSum, oddSum;

    printf("\nEnter the number : ");
    scanf("%d", &no);

    evenSum = evenSumFun(no);
    oddSum = oddSumFun(no);
}

int evenSumFun(int no)
{
    int evenSum , digit , Even = 0;
    while (no > 0){
        digit = no % 10;
        if (digit % 2 == 0)
        {
            Even = Even * 10 + digit;
        }
        no = no / 10;
    }
    evenSum = sumFun(Even);

    printf("\nEven Digits = %d" , Even);
    printf("\nEven Digit Sum = %d\n" , evenSum);
    return evenSum;
}

int oddSumFun(int no)
{
    int oddSum , digit , Odd = 0;
    while (no > 0){
        digit = no % 10;
        if (digit % 2 == 1)
        {
            Odd = Odd * 10 + digit;
        }
        no = no / 10;
    }
    oddSum = sumFun(Odd);

    printf("\nOdd Digits = %d" , Odd);
    printf("\nOdd Digit Sum = %d\n", oddSum);
    return oddSum;
}

int sumFun(int no)
{
    int sum = 0, digit , num = 0;
    while (no > 0)
    {
        digit = no % 10;
        sum = sum + digit;
        no = no / 10;
    }
    return sum;
}