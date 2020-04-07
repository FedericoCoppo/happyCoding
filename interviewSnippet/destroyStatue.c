/*
	Given a array of N size containing coordinate point
	of statue; you are positioned in (x=0,y=0) and shall calculate
	minimum number of xray shot to destroy statue
					 __ __ __ __ 4  __ __ __ __
					|__|__|__|__|3 |__|__|__|__|
					|__|__|__|__|2 |__|__|__|__|
					|__|__|__|__|1 |__|__|__|__|
					|__|__|__|__|0 |__|__|__|__|
					|__|__|__|__|-1|__|__|__|__|
					|__|__|__|__|-2|__|__|__|__|
					|__|__|__|__|-3|__|__|__|__|
					|__|__|__|__|-4|__|__|__|__|
					
	ZOOM
	A[1].x = 1;
	A[1].y = 2;
	A[2].x = 2;
	A[2].y = 4;  -> 1 single shot!
	
	 _______________________
	|				*(2,4)				
	|
	|_______|_______|______|
	|
	| 
	|_______|_______|______|			
	|		*(1,2)		
	|			
	|_______|_______|______|
	|
	|
	|_______|_______|______|
  (0,0)
			
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Point2D {
  int x;
  int y;
};

int solution(Point2D * A, int N)
{
	bool destroy[N] = {false};
	int rayCnt = 0;

    for (int i = 0; i < N; i++)
    {
    	if (destroy[i] == false)
    	{
    		rayCnt++;
    		destroy[i] = true;

    		// 1 check if on X = 0
    		if (A[i].x == 0)
    		{
    			// for all other points
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					// in case of upper ray
    					if (A[i].y > 0)
    					{
        					// remove every other point with x = 0 and positive
        					if (A[j].x == 0 && A[j].y > 0)
        					{
        						// remove
        						destroy[j] = true;
        					}
    					}
    					else
    					{
    						if (A[j].x == 0 && A[j].y < 0)
    						{
    							// remove
    							destroy[j] = true;
    						}
    					}
    				}
    			}
    		}


    		// 1 check if on Y = 0
    		if (A[i].y == 0)
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if (A[i].x > 0)
    					{
        					if (A[j].y == 0 && A[j].x > 0)
        					{
        						destroy[j] = true;
        					}
    					}
    					else
    					{
    						if (A[j].y == 0 && A[j].x < 0)
    						{
    							destroy[j] = true;
    						}
    					}
    				}
    			}
    		}

    		// 7 diagonal
    		if (abs(A[i].x) == abs(A[i].y))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if (A[j].x == A[j].y)
    					{
        					// ++
        					if ((A[i].x > 0) && (A[i].y > 0) && (A[j].x > 0) && (A[j].y > 0) )
        					{
        						destroy[j] = true;
        					}
        					else if ( (A[i].x > 0 && A[i].y < 0) && (A[j].x > 0 && A[j].y < 0) )
        					{
        						destroy[j] = true;
        					}
        					else if ( (A[i].x < 0 && A[i].y > 0) && (A[j].x < 0 && A[j].y > 0))
        					{
        						destroy[j] = true;
        					}
        					else if ( (A[i].x < 0 && A[i].y < 0) && (A[j].x < 0 && A[j].y < 0) )
        					{
        						destroy[j] = true;
        					}
    					}
    				}
    			}
    		}

    		// check for (1-2, 2-4 2-1, 4-2 in all other (x4))

    		// 12 24
    		if ( (A[i].x == 1 && A[i].y == 2) || (A[i].x == 2 && A[i].y == 4))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == 1 && A[j].y == 2) || (A[j].x == 2 && A[j].y == 4))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// 21 42
    		if ( (A[i].x == 2 && A[i].y == 1) || (A[i].x == 4 && A[i].y == 2))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == 2 && A[j].y == 1) || (A[j].x == 4 && A[j].y == 2))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// -12 -24
    		if ( (A[i].x == -1 && A[i].y == 2) || (A[i].x == -2 && A[i].y == 4))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == -1 && A[j].y == 2) || (A[j].x == -2 && A[j].y == 4))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// -21 -42
    		if ( (A[i].x == -2 && A[i].y == 1) || (A[i].x == -4 && A[i].y == 2))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == -2 && A[j].y == 1) || (A[j].x == -4 && A[j].y == 2))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// -1-2 -2-4
    		if ( (A[i].x == -1 && A[i].y == -2) || (A[i].x == -2 && A[i].y == -4))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == -1 && A[j].y == -2) || (A[j].x == -2 && A[j].y == -4))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// -2-1 -4-2
    		if ( (A[i].x == -2 && A[i].y == -1) || (A[i].x == -4 && A[i].y == -2))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == -2 && A[j].y == -1) || (A[j].x == -4 && A[j].y == -2))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// 1-2 2-4
    		if ( (A[i].x == 1 && A[i].y == -2) || (A[i].x == 2 && A[i].y == -4))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == 1 && A[j].y == -2) || (A[j].x == 2 && A[j].y == -4))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}

    		// 2-1 4-2
    		if ( (A[i].x == 2 && A[i].y == -1) || (A[i].x == 4 && A[i].y == -2))
    		{
    			for (int j = i + 1; j < N; j++)
    			{
    				if (destroy[j] == false)
    				{
    					if ( (A[j].x == 2 && A[j].y == -1) || (A[j].x == 4 && A[j].y == -2))
    					{
    						destroy[j] = true;
    					}
    				}
    			}
    		}
    	}
    }

	return rayCnt;
}

int main()
{

	Point2D A[5];
	A[0].x = -1;
	A[0].y = -2;
	A[1].x = 1;
	A[1].y = 2;
	A[2].x = 2;
	A[2].y = 4;
	A[3].x = -3;
	A[3].y = 2;
	A[4].x = 2;
	A[4].y = -2;
	int ray = solution(A,5);
	printf("sol = %d", ray);

    return 0;
}