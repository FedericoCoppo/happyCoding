## Description
Ubuntu 16.04
```
$ gcc -o queen queen.c
$ ./queen
```

The program shows how to finds solution for "8 queens games" using backtracking
https://en.wikipedia.org/wiki/Eight_queens_puzzle
The program finds all solution for N size chess.
For who is not confident with this problem, here below is showed the program stack flow for N = 4 (2 solution).

```
Legend:
Q -> queen has been placed
0 -> position is free
X -> queen can not be placed with actual queen configuration
o -> a queen previously placed has been removed since solution has not been found 
```
```
starting column = 0  

Q000  ->  QX00  ->  QXX0  ->  QX00  ->  QXX0  ->  QXXX  ->  QXX0
0000      0X00      0XX0      0X00      0XQ0      0XQX      0Xo0
0000      0Q00      0QX0      0o00      0o00      0o0X      0oX0
0000      0000      00X0      0Q00      0Q00      0Q0X      0QX0
                             bktrack                        bktrack
          ____      ____
QXX0  -> |oXQX| -> |0QXX|
0Xo0     |QX0X|    |00XQ|
0oX0     |0oXQ|    |Q0X0|
0oX0     |0QX0|    |00Q0|
bktrack   sol1     sol2
```

