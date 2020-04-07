/*

A non-empty array A consisting of N integers is given. The array contains an odd number of elements, and each element of the array can be paired with another element that has the same value, except for one element that is left unpaired.

For example, in array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the elements at indexes 0 and 2 have value 9,
the elements at indexes 1 and 3 have value 3,
the elements at indexes 4 and 6 have value 9,
the element at index 5 has value 7 and is unpaired.
Write a function:

int solution(vector<int> &A);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

For example, given array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the function should return 7, as explained in the example above.

Write an efficient algorithm for the following assumptions:

N is an odd integer within the range [1..1,000,000];
each element of array A is an integer within the range [1..1,000,000,000];
all but one of the values in A occur an even number of times.

*/

using namespace std;

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "string.h"

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)

    int pairedVal;
    int notPairedVal = 0;
    bool paired;

    if (A.size() > 0)
    {
        for (int i = 0; i < (int) A.size(); i++)
        {
            pairedVal = A[i];
            paired = false;

            for (int j = i + 1; j < (int) A.size(); j++)
            {
                if ( (i != j) && (A[j] == pairedVal) )
                {
                    paired = true;
                    break;
                }
            }

            if (!paired)
            {
                notPairedVal = pairedVal;
                break;
            }
        }
    }

    return notPairedVal;
}

int solution2(vector<int> &A)
{
	// write your code in C++14 (g++ 6.2.0)
	int size = (int) A.size();
	int i;

	for (i = 0; i < size; i++)
	{
		if((count(A.begin(), A.end(), A[i])%2) != 0)
		{
			break;
		}

	}
	return A[i];
}

int main() {

	std::vector<int> A {1, 3, 1, 9, 5, 3, 5};
	cout << solution(A);
	cout << solution(B);
	return 0;
}
