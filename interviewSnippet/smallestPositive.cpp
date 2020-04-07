/*

This is a demo task.
Write a function:
int solution(int A[], int N);
that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.
For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
Given A = [1, 2, 3], the function should return 4.
Given A = [−1, −3], the function should return 1.
Write an efficient algorithm for the following assumptions:
N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
Copyright 2009–2020 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.

*/

#include <stdio.h>
#include <stdbool.h>

int solution(int A[], int N) {

    int max = -1000000;
    int min = 0;
    int minTmp = 0;
    bool found = true;
    bool end = false;

    // write your code in C99 (gcc 6.2.0)
    for (int i = 0; i < N; i++)
    {

        if(A[i] > max)
        {
            max = A[i];
        }
        
        // fix the value
        minTmp++;
        
        found = false;
        for(int j = 0; j < N; j++)
        {
            if (minTmp == A[j])
                {
                    found = true;
                    break;
                }
        }
        
        if (!found)
        {
            min = minTmp;
            end = true;
            break;
        }
    }
    
    if (!end)
    {
        min = max + 1;
    }

    return min;
}


/*
Compilation successful.

Example test:   [1, 3, 6, 4, 1, 2]
OK

Example test:   [1, 2, 3]
OK

Example test:   [-1, -3]
OK
*/