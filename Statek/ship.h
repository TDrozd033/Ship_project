#ifndef _SHIP_
#define _SHIP_

#define _CRT_SECURE_NO_WARNINGS
#define M 10
#define N 10
#define DEPTH_MIN 5 
typedef enum { UP = 1, RIGHT, DOWN, LEFT }Direction;

int move( int** pTab, int nRow, int nCol, int nDepth,
  int move, int x, int y, int* px, int* py, int** pRoot );

int root( int** pTab, int nRow, int nCol, int nDepth,
  int x, int y, int** pRoot, int x_dest, int y_dest );   //--- rekurencyja


void clearRoot( int** pRoot, int nRow, int nCol );


int setTab( char* sFile, int** pTab, int nRow, int nCol );
#endif