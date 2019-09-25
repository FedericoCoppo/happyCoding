/******************************************************************************
	File        : QueensBacktracking.c
	Date        : 14/09/2019
	Author      : Federico Coppo
	Description : the prog finds all N solution for 8 Queen guessing game
                  	using backtracking
*******************************************************************************/

#include <stdbool.h>
#include <stdio.h> 
#define MAX_QUEENS 8
//#define DEBUG_TRACE /* enable to follow the stack flow */

static bool chess[MAX_QUEENS][MAX_QUEENS];
static int  solutionCounter = 0;
static const unsigned int solRequested = 93;

/* chess printer routine */
void chessPrinter()
{
    for (int i = 0; i < MAX_QUEENS; i++)
    {
        for (int j = 0; j < MAX_QUEENS; j++)
            {
                printf(" %d ", chess[i][j]);
            }

            printf("\n");
    }
	
    printf("\n");
}
  
/* routine to check if a queen can placed in a defined position */
bool isFree(int row, int col)
{ 
    int i, j;
    bool success = true;
	
    /* Check this row on left side (between [col:N] no queen placed when routine is called) */
    for (i = 0; i < col; i++) 
	{
		if (chess[row][i])
		{
			success = false;
		}            
  	}

    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
	{
		if (chess[i][j])
		{
            		success = false; 
		}
	}
  
    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < MAX_QUEENS; i++, j--)
	{
		if (chess[i][j])
		{
            		success = false; 
		}
	}
  
    return success; 
} 
 
/* Recursive utility function to solve N queen problem */
bool findQueensRecursive(int column)
{ 
    /* When all N queens are in the chess */
    if (column >= MAX_QUEENS)
	{
		printf("Solution number: %d \n\n", solutionCounter +1);
		chessPrinter();

		/* terminate */
		if (++solutionCounter == (solRequested) )
		{
			return true;
		}	
		else 
		{	
			return false;
		}	
	}
	
    /* for the fixed column search the raw to place the queen */
    for (int i = 0; i < MAX_QUEENS; i++) 
	{
        	if (isFree(i, column)) 
		{
            		/* place the queen */
			chess[i][column] = true;
	
		#ifdef DEBUG_TRACE
			printf("New queen found \n");			

			/* print the updated chess */
			chessPrinter();
		#endif	
			if (findQueensRecursive(column + 1))
			{ 
				return true; 
			}
	  
			/* when the queen placed in [i, column] position hasn't caused a solution, then shall be removed */ 
			/* backtracking! */
			chess[i][column] = 0; 

		#ifdef DEBUG_TRACE
			printf("removed queen in position: %d , %d \n", i, column);
			
			/* print the updated chess */
			chessPrinter();
		#endif
        	} 
    	} 
  
    /* When the queen has not good  row in this colum backtracking shall be triggered */
#ifdef DEBUG_TRACE
	printf("BACKTRACKING trigger:\n");
#endif
	
    return false; 
} 
  
/* The routine solves the N queen problem using 
   Backtracking. All solution for N queen are printed */
int main() 
{ 
	/* start searching from first column */
	if (findQueensRecursive(0) == false)
	{ 
		printf("Not all solution requested (%d) has been founded\n", solRequested ); 
		return false; 
	} 
	
	printf("It has been founded %d solutions\n", solutionCounter); 
		
    	return 0; 
}
