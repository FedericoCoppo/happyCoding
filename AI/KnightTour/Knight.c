/*********************************************************************************
	File        : Knight.c
	Date        : 25/09/2019
	Author      : Federico Coppo
	Description : the prog finds N solution (solRequested) for knight tour game 
		      for a MAX_SIZE*MAX_SIZE chess
**********************************************************************************/

#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#define  MAX_SIZE 5
//#define DEBUG_TRACE /* enable to follow the stack flow */

static int chess[MAX_SIZE][MAX_SIZE];
static int  solutionCounter = 0;
static const unsigned int solRequested = 3;
static int knightCnt = 0;

/* chess printer routine */
void chessPrinter()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
			{
				printf(" %02d ", chess[i][j]);
			}

			printf("\n");
    }
	
    printf("\n");
}
  
/* check if a knight can placed in the defined position (newRaw, newColumn) */
bool isFree(int raw, int column, int * newRaw, int newColumn)
{ 
	bool success = false;
	
	/* check for 2 column step position backward and forward */
	if ((newColumn == column - 2) || (newColumn == column + 2))
	{
		if ( (raw - 1) >= 0)
		{
			if (chess[raw - 1][newColumn] == 0)
			{
				*newRaw = raw - 1;
				success = true;
			}
		}
		if (raw + 1 < MAX_SIZE)
		{
			if (chess[raw + 1][newColumn] == 0)
			{
				*newRaw = raw + 1;
				success = true;
			}
		}
	}
	/* check for 1 column step position backward and forward */
	else if ((newColumn == column - 1) || (newColumn == column + 1))
	{
		if ( (raw - 2) >= 0)
		{
			if (chess[raw - 2][newColumn] == 0)
			{
				*newRaw = raw - 2;
				success = true;
			}
		}
		if (raw + 2 < MAX_SIZE)
		{
			if (chess[raw + 2][newColumn] == 0)
			{
				*newRaw = raw + 2;
				success = true;
			}
		}
	}
	
    return success; 
} 
 
/* Recursive utility function to solve knight tour */
bool knightTourRecursive(int raw, int column)
{ 
	int newRaw = 0;

    /* when all positions have been crossed */
    if (knightCnt >= MAX_SIZE*MAX_SIZE - 1)
	{
		chess[raw][column] = ++knightCnt; 
		printf("Founded solution number: %d \n\n", solutionCounter + 1);
		chessPrinter();


		if ( ++solutionCounter == (solRequested) )
		{
			/* terminate */
			return true;
		}	
		else 
		{	
			/* continue for other solutions */
			return false;
		}	
	}
	
    /* for the fixed column search position's raw */
    for (int newColumn = 0; newColumn < MAX_SIZE; newColumn++) 
	{
		/* no way to place another knight in the same column of actual knight or in a column grater/lower than actual column +-2 */
		if (newColumn != column && (abs(newColumn - column) <= 2))
		{
			if (isFree(raw, column, &newRaw, newColumn)) 
			{		
				/* place the new knight */
				chess[raw][column] = ++knightCnt;
				
		#ifdef DEBUG_TRACE
				printf("knight %d placed in pos:(%d,%d), New knight to be tested in pos (%d,%d) \n",knightCnt, raw, column, newRaw,newColumn);			
	            /* print the updated chess */
	            chessPrinter();
		#endif	
				if (knightTourRecursive(newRaw, newColumn))
				{ 
					return true; 
				}
				
				/* not possible to place new knight -> backtracking! */
				chess[raw][column] = 0; 
				knightCnt--;

		#ifdef DEBUG_TRACE
				printf("removed queen in position: %d , %d \n", raw, column);
				
				/* print the updated chess */
				chessPrinter();
		#endif
			} 
    	} 
	}
  
    /* no good position founded for the knight, backtracking shall be triggered! */
#ifdef DEBUG_TRACE
	printf("backtracking!\n");
#endif
	
    return false; 
} 
  
/* The routine solves the knight tour problem using 
   Backtracking */
int main() 
{ 
	/* start searching from first column */
	if (knightTourRecursive(0,0) == false)
	{ 
		printf("Not all solution requested (%d) has been founded\n", solRequested ); 
		return false; 
	} 
	
	printf("It has been founded %d solutions\n", solutionCounter); 
		
    	return 0; 
}
