/*
A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example, number 9 has binary representation 1001 and contains a binary gap of length 2. The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3. The number 20 has binary representation 10100 and contains one binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps. The number 32 has binary representation 100000 and has no binary gaps.

Write a function:

int solution(int N);

that, given a positive integer N, returns the length of its longest binary gap. The function should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5. Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..2,147,483,647].
*/

#include <bitset>
#include "string.h"

int solution(int N) {
    // write your code in C++14 (g++ 6.2.0)
    std::string s = std::bitset<32>(N).to_string();   // convert into a string
    //cout << s;										 // just for debug				
    int patternCnt = 0;
    int patternMax = patternCnt;
    bool patternIsValid = false;

    for (int i = 0; i < (int) s.size(); i++)
    {
    	// find the first 1
    	if (s[i] == '1')
    	{
    		patternCnt = 0;
    		patternIsValid = false;
    		for (int j = i + 1; j < (int) s.size(); j++)
    		{
    			if (s[j] == '0')
    			{
    				patternCnt++;
    			}
    			else
    			{
    				// end of pattern!
    				patternIsValid = true;
					
					// evaluate if possible to change the value of i -> (i = j + 1)
    				break;
    			}	
    		}
    		
    		// check if this pattern is grater than
    		if ( patternIsValid && (patternCnt > patternMax))
    		{
    			patternMax = patternCnt;
    		}
    	}
    }

    return patternMax;
}

/*

Example test:   1041
Output:
00000000000000000000010000010001
OK

Example test:   15
Output:
00000000000000000000000000001111
OK

Example test:   32
Output:
00000000000000000000000000100000
OK

*/