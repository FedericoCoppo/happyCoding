/*
A non-empty array A consisting of N integers is given. Array A represents numbers on a tape.
Any integer P, such that 0 < P < N, splits this tape into two non-empty parts: A[0], A[1], ..., A[P − 1] and A[P], A[P + 1], ..., A[N − 1].
The difference between the two parts is the value of: |(A[0] + A[1] + ... + A[P − 1]) − (A[P] + A[P + 1] + ... + A[N − 1])|
In other words, it is the absolute difference between the sum of the first part and the sum of the second part.
For example, consider array A such that:
  A[0] = 3
  A[1] = 1
  A[2] = 2
  A[3] = 4
  A[4] = 3

We can split this tape in four places:
P = 1, difference = |3 − 10| = 7
P = 2, difference = |4 − 9| = 5
P = 3, difference = |6 − 7| = 1
P = 4, difference = |10 − 3| = 7

Write a function:
int solution(vector<int> &A);
that, given a non-empty array A of N integers, returns the minimal difference that can be achieved.
For example, given:
  A[0] = 3
  A[1] = 1
  A[2] = 2
  A[3] = 4
  A[4] = 3

the function should return 1, as explained above.
Write an efficient algorithm for the following assumptions:

N is an integer within the range [2..100,000];
each element of array A is an integer within the range [−1,000..1,000].
*/

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
	std::vector<int>::iterator it;
	int sum_of_elemsDx;
	int sum_of_elemsSx;
	int min = A.size() + 1;
	
    for (int i = 1; i < (int) A.size(); i++) // size - 1 times
    {
        sum_of_elemsSx = 0;
        sum_of_elemsDx = 0;
        
    	for (int j = 0; j < i; j++)
    	{
    		sum_of_elemsSx += A[j];
    	}
    	
    	for (int k = i; k < (int) A.size(); k++)
    	{
    		sum_of_elemsDx += A[k];
    	}
    	
    	if(  abs(sum_of_elemsSx - sum_of_elemsDx) < min || A.size() == 2) 
    	{
    		min = abs(sum_of_elemsSx - sum_of_elemsDx);
    	}
    }
    
    return min;
}