#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "library.h"


void hello()
{
    printf("Hello, World!\n");
}


int countOddNumbers(const int* numbers, int count)
{
    int odd = 0;
    for (int i = 0; i < count; i += 1) {
        odd += numbers[i] % 2;
    }
    return odd;
}


int countEvenNumbers(const int* numbers, int count)
{
    return count - countOddNumbers(numbers, count);
}


bool isEven(int n)
{
    return !(bool) (n & 1);
}


bool isOdd(int n)
{
    return (bool) (n & 1);
}
