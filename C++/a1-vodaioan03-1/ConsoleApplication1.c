#include <stdio.h>
#include <stdlib.h>

int prime(int x) {
    /* Checks if a given number is prime.
    
    */
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    for (int d = 3; d <= x / 2; d += 2) {
        if (x % d == 0) return 0;
    }
    return 1;
}

int relativePrime(int x, int y) {
    /*
    Verify if two numbers are relative prime.
    */
    int nrMin;
    if (x < y) nrMin = x;
    else nrMin = y;
    for (int d = 2; d < nrMin; d++) {
        if (x % d == 0 && y % d == 0) return 0;
    }
    return 1;

}

void printMenu() {
    /*
    Print console menu based.
    */
    printf(" = = = = Console Menu = = = = \n");
    printf(" 1. Determine the firs 8 prime numbers.\n");
    printf(" 2. Find the longest contiguous subsequence from a given vector.\n");
    printf(" 3. Exit\n");
    printf(" Type your option [1/2]:\n");
}

void generateNumbers(int* pointer) {
    /*
    Solution for a. Generate first 8 relative prime numbers.
    */
    int counter = 0;
    for (int i = 3; counter < 8; i++) {
        int ok = 1;
        for (int j = 2; j < i; j++) {
            if (relativePrime(i,j))
            {
                if (prime(j) == 0) {
                    ok = 0;
                    j = i + 1;
                }
            }
        }
        if (ok == 1) {
            *(pointer+counter) = i;
            counter++;
        }
    }
}

int checkDigits(int nr1, int nr2) {
    /*
    Verify if all digits from a number are the same.
    */

    int vectorFreq[10] = { 0 };
    int vectroFreq2[10] = { 0 };
    while (nr1 > 0) {
        vectorFreq[nr1 % 10]++;
        nr1 /= 10;
    }
    while (nr2 > 0) {
        vectroFreq2[nr2 % 10]++;
        nr2 /= 10;
    }
    for (int i = 0; i < 10; i++) {
        if (vectorFreq[i] > 0 && vectroFreq2[i] == 0 || vectorFreq[i] == 0 && vectroFreq2[i] !=0) return 0;
    }
    return 1;
}

void findTheLongestSubsequence(int length, int numbers[], int* arrayResult, int* counter) {
    /*
    Find the longest subsequence for b.
    */
    int actual[1001] = { 0 };
    *counter = -1;
    int actualCount = 0;
    for (int i = 0; i < length; i++) {
        actualCount = 0;
        actual[actualCount++] = numbers[i];
        for (int j = i + 1; j < length; j++) {
            if (checkDigits(numbers[i], numbers[j])) {
                actual[actualCount++] = numbers[j];
            }
        }
        if (actualCount > *counter) {
            *counter = actualCount;
            for (int i = 0; i < actualCount; i++) {
                *(arrayResult + i) = actual[i];
            }
        }
    }
}

void readNumbers() {
    /*
    Read a list of numbers from console.
    */
    int numbers[100] = { 0 };
    int counter = 0;
    int length;
    printf("Type the length of list:");
    scanf("%d", &length);
    printf("Type the list:");
    while (counter < length) {
        scanf("%d", &numbers[counter++]);
    }
    int longestSequence[1001] = { 0 };
    int longCount = 0;
    findTheLongestSubsequence(length,numbers,&longestSequence,&longCount);
    for (int i = 0; i < longCount; i++) {
        printf("%d, ", longestSequence[i]);
    }
    printf("\n");
}

void optionProceed(int option) {
    /* Logic proceed for option.*/
    if (option == 1) {
        int numbers[9];
        generateNumbers(&numbers);
        printf(" The first 8 numbers are: \n [ ");
        for (int i = 0; i < 8; i++) {
            printf(" %d", numbers[i]);
            if (i < 7) printf(", ");
        }
        printf("]\n\n\n");
    }
    else if (option == 2) {
        readNumbers();
    }
    else if (option == 3) {
        printf("Exiting...\n");
        exit(0);
    }
}

int main()
{
    // Problem 13
    while (1) {
        printMenu();
        int option;
        scanf("%d", &option);
        optionProceed(option);
    }


}
