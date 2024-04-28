//   JAKIE PRINTTAB
// JAKIE CREATE TAB 
// JAKIE SETTAB
// PRZEKSZTALCIC SETTAB Z INT NA VOID ZEBY DOBRZE DZIALALO - DO KORDIANA 



// czy set tab void czy int
// jak ten creatematrix, ktroe z tych moich, czy tylko jedna ta tablkica
// gdzie typedef i te kierunki 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ship.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <math.h>


//zdefini stale N i M - wymiary  (na 10)  tam gdzie main()

#define M 10
#define N 10


#define _PRINT_
// zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)
/*
typedef enum { UP=1, RIGHT, DOWN, LEFT }Direction;
#define DEPTH_MIN 5    // glebokosc zanurzenia okretu   tam gdzie main()
*/
// zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)



//int** createTab1( int nRow, int nCol );
//int** createTab2( int nRow, int nCol );
//void freeTab( int*** pTab );
//void clearRoot( int** pRoot, int nRow, int nCol );
//void setTab( int** pTab, int nRow, int nCol );
void PrintTab2D( int** pRoot, int nRow, int nCol );


//int** CreateMatrix( int nRow, int nCol );



// ALTERNATYWA W ZALEZNOSCI JAKIE DELETEMATRIX
void DeleteMatrix( int*** pTab );





//void DeleteMatrix( int*** pTab );




//void PrintMatrix( int** pTab, int nRow, int nCol );

int** CreateTab2D( int nRow, int nCol );

int main(char argc, char* argv[])
{
  //!!argc
  if( argc != 2 )
  {
    printf( "Usage: %s <input_file>\n", argv[ 0 ] );
    return 1;
  }

 
  //Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary)
  int** pMatrix = NULL;
  if( !(pMatrix = CreateTab2D(M,N )))
  {
    perror( " Blad podczas kreowania pMatrix!\n" );
    return -2;
  }

  int** pRoot = NULL;
  if( !( pRoot = CreateTab2D( M, N ) ) )
  {
    perror( " Blad podczas kreowania pRoot!\n " );
    return -1;
  }
  // wczytac dane (sprawdzic argc)  glebokosci 
  if( !setTab( argv[ 1 ], pMatrix, M, N ) )
  {
    perror( "Blad otwierania pliku!\n" );
    return -3;
  }

#ifdef _PRINT_
  printf( " Minimalna glebokosc wynosi:\n %d\n ", DEPTH_MIN );
  /*  alternatywa jakby nie dzialalo 
  printf( " Minimalna glebokosc wynosi: \n" );
  printf( "%d\n", DEPTH_MIN );
  */
  printf( " Pelna Mapa: \n " );
  PrintTab2D( pMatrix, M, N );
  printf( "\n" );
#endif

  // Jezeli nie znaleziono drogi od (0,0) do (N,M)- funkcja rekur root - wypisac
  if( ! root( pMatrix, M, N, DEPTH_MIN, 0, 0, pRoot, M - 1, N - 1 ) ) 
  {
    printf( "** Nie ma mozliwosci doplynac do portu!!\n\n" );
  }
  // jesli ok to wypisac trase
else
  {
    printf( "Droga do portu to: \n" );
    PrintTab2D( pMatrix, M, N );
  }

  //zwolnic pamiec!!


  //DeleteMatrix( &pMatrix, M, N );
  //DeleteMatrix( &pRoot, M, N );
  DeleteMatrix( &pMatrix );  // alternatywa w zaleznosci jakie deletematrix: DeleteMatrix(&pMatrix, M, N);
  DeleteMatrix( &pRoot );   // DeleteMatrix(&pRoot, M, N);

  // nie wiem czy konieczne te linijki 126 , 127
  //*pMatrix = NULL;
  //*pRoot = NULL;

  return 0;






  
 
 /*
  int x0 = atoi( argv[ 1 ] );
  int y0 = atoi( argv[ 2 ] );
  if( x0 < 0 || x0>10 || y0 < 0 || y0>10 )
  {
    printf( "Usage: %s <0..10> <0...10> \n ", argv[ 0 ] );
    return 2;
  }
  */

  /*[
  int** pTab = new int* [N];
  int** pRoot = new int* [N];
  for( int i=0; i<N; i++)
  {
  pTab[i] =- new int [M];
  pRoot[i] = new int [M];
  }
  
  
  

  int** pTab = createTab1( N, M );
  int** pRoot = createTab2( N, M );
  clearRoot( pRoot, N, M );
  setTab( pTab, N, M );

  if( !root( pTab, N, M, DEPTH_MIN, 0, 0, pRoot ) )
    printf( "Nie ma mozliwosci doplynac do portu!\n\n" );
  else
  {
    printTab2D( pRoot, N, M );
  }




  */

  

  
}




/*
//kreowanie druga metoda
int** CreateTab2D( int nRow, int nCol )
{
  int** pTab = ( int** ) malloc( sizeof( int* ) * nRow );
    if( !pTab) return NULL;
    //memset( pTab, 0, nRow * sizeof( int* ) );
    int* p = ( int* ) malloc( nCol * nRow * sizeof( int ) );
    if( !p )
    {
      free( pTab );
      return NULL;
    }
   // memset( p, 0, nRow * nCol * sizeof( int ) );
    clearRoot( pTab, nRow, nCol );
    int** v = pTab;
    for( int i = 0; i < nRow; i++, p += nCol )
    {
      *v++ = p;
    }
      return pTab;
}
*/





int** CreateTab2D( int nRow, int nCol )
{
  int** pTab = ( int** ) malloc( sizeof( int* ) * nRow );
  if( !pTab ) return NULL;
  memset( pTab, 0, nRow * sizeof( int* ) );

  *pTab = ( int* ) malloc( nCol * nRow * sizeof( int ) );
  if( !*pTab )
  {
    //free( pTab );
    return NULL;
  }
 memset( *pTab, 0, nRow * nCol * sizeof( int ) );
  //clearRoot( pTab, nRow, nCol );
  int** v = pTab+1;
  int* p = *pTab + nCol;
  for( int i = 0; i < nRow -1; i++, p += nCol )
  {
    *v++ = p;
  }
  return pTab;
}




//void DeleteMatrix( int*** pTab ) // int*** pTab, int nRow, int nCol    - nie wiem ktore z tych 
void DeleteMatrix(int*** pTab)
{
  free( **pTab );
  free( *pTab );
  *pTab = NULL;
}


/*
void PrintMatrix( int** pTab, int nRow, int nCol )
{
  for( int i = 0; i < nCol; i++ )
  {
    int* tab = *pTab;
    for( int j = 0; j < nRow; j++ )
    {
      printf( "%t", *tab );
    }
    printf( "\n" );
  }
}
*/




void PrintTab2D( int** pRoot, int nRow, int nCol )
{
  for( int i = 0; i < nRow; i++ )
  {
    int* ptr = *pRoot++;
    for( int j = 0; j < nCol; j++ )
    {
      printf( "%d ", *ptr++ );
    }
    printf( "\n" );
  }
}



