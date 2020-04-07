/*
An array A consisting of N different integers is given. The array contains integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

int solution(vector<int> &A);

that, given an array A, returns the value of the missing element.

For example, given array A such that:

  A[0] = 2
  A[1] = 3
  A[2] = 1
  A[3] = 5

the function should return 4, as it is the missing element.
Write an efficient algorithm for the following assumptions:
N is an integer within the range [0..100,000];
the elements of A are all distinct;
each element of array A is an integer within the range [1..(N + 1)].
*/

#include<bits/stdc++.h>

int solution(vector<int> &A) 
{
    int i;
    std::vector<int>::iterator it;
    
    // for all number 1 to N + 1
    for (i = 0; i < (int) A.size(); i++)
    {
        // iterator
        it = std::find (A.begin(), A.end(), i + 1);
        
        // when numner is not found
        if (it == A.end())
        {
            break;
        }
    }
    
    return i + 1;
}

// OPTIMIZED SOLUTION
int solution(vector<int> &A) {
 // write your code in C++11 (g++ 4.8.2)
 int res = 0;
 
 for (int i = 0; i < int(A.size()); i++) {
        res += (i + 1 - A[i]);
    }
 
    res += int(A.size() + 1);
 
 return res;
}