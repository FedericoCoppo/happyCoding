/*
	given a chess of MXN with some position already busy
	the routine calculate the number of move
	the knight should perform to go from (0,0)
	to (M,N)
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define  MAX_RAW_SIZE 4
#define  MAX_COL_SIZE 3

/* using knight backtracking tecnique */

static int chess[MAX_RAW_SIZE][MAX_COL_SIZE];
static int  solutionCounter = 0;
static const unsigned int solRequested = 1; /* fixed to 1 because is not needed to a perform different solution trees*/
static int knightCnt = 0;

/* chess printer routine */
void chessPrinter()
{
	for (int i = 0; i < MAX_RAW_SIZE; i++)
	{
		for (int j = 0; j < MAX_COL_SIZE; j++)
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
		if (raw + 1 < MAX_RAW_SIZE) //
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
		if (raw + 2 < MAX_RAW_SIZE) //
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

	/* if you have reached the goal: position is (MxN) */
    if ( (raw == (MAX_RAW_SIZE -1)) && ((column == MAX_COL_SIZE -1)) )
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
    for (int newColumn = 0; newColumn < MAX_COL_SIZE; newColumn++)
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

int main()
{
	/* fill the busy position */ 
	chess[0][0] = 0;
	chess[0][1] = 0;
	chess[0][2] = 0;
	chess[1][0] = 0;
	chess[1][1] = 0;
	chess[1][2] = 1;
	chess[2][0] = 1;
	chess[2][1] = 0;
	chess[2][2] = 0;
	chess[3][0] = 0;
	chess[3][1] = 0;
	chess[3][2] = 0;

	/* start searching from position 0 0 */
	if (knightTourRecursive(0,0) == false)
	{
		printf("Not all solution requested (%d) has been founded\n", solRequested );
	}

	printf("It has been executed %d move\n", knightCnt);	
}