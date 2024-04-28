#include"ship.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>


/*
int move( int** pTab, int nRow, int nCol, int nDepth,
  int move, int x, int y, int* px, int* py, int** pRoot )
{   // x  y - wsporzedne skad robimy nowy ruch
  //  wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
       //(switch)
    //sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
  // a nastepnie sprawdzic warunek czy nie jest za plytko ">=nDepth " oraz
    // czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot (wart 0 w nowej lokalicacji)

//    jesli wszystkie warunki poprawne to zwracamy 1
  //    else 0
}

//----------------------------------------------------------------------------------
int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot,
  int x_dest, int y_dest )
{

  static int moveNo = 1;
  n++;
  // tabl pRoot pamieta droge   -   numer ruchu pole przez ktore odwiedzono (plynie statek) 
  //                                0 pole nie odwiedzone
  // wstawic do tablicy pRoot kolejny numer ruchu
  pRoot[ x ][ y ] = moveNo;
  if( moveNo++ == nRow * nCol )
  {
    return 1;
  }
  if( pRoot[M-1][N-1] )
    return 1;

  //else
 // zdefiniowac nowe wspolrzende 
      // sprwadzic wszystkie mozliwosci ruchu
       //jesli ruch jest mozliwy w zadanym kierunku 
            //jesli wykonanie kolejnego kroku sie powiodlo - rekurencyjnie root()
  return 1;

  // jesli wracamy to ustawiamy w pRoot ze ruch byl zly
  return 0;

}


*/

int setTab( char* sFile, int** pTab, int nRow, int nCol )  // trzeba z mkienic na wczytywanie z pliku tekstowego uzywajac fscanf 
{
  /*
  srand(( unsigned int )time( NULL ));
  for( int i = 0; i < M; i++ )
  {
    for( int j = 0; j < N; j++ )
    {
      pTab[ i ][ j ] = rand() % ( DEPTH_MIN << 1 );
      printf( "%d", pTab[ i ][ j ] );
    }
    printf( "\n" );
  }
  */
  FILE* plik = fopen( "statek.txt", "r" );
  if( plik == NULL )
  {
    perror( "Blad otwierania pliku tekstowego\n" );
    return 0;
  }
  for( int i = 0; i < nRow; i++ )
  {
    int* p = *pTab++;
    for( int j = 0; j < nCol; j++,p++ )
    {
      fscanf( plik, "%d", p );
    }
  }
  fclose( plik );
  return 1;
}
// wczytuje dane z pliku
// sFile -  nazwa pliku wejsciowego - parametr main()
// pTab  - tablica glebokosci morza
// nRow, nCol wymiary tej tablicy



int move( int** pTab, int nRow, int nCol, int nDepth,
  int move, int x, int y, int* px, int* py, int** pRoot )  // git
{  // x numer wiersza      y numer kolumny

  switch( move )  // jak zmienia sie polozenie statku w zaleznosci od case, 
    // np jesli up to statek przesuwa sie pionowo do gory i poziomo pozstaje tak samo, czyli x zmniejsza sie o 1, y bez zmian
  {
  case UP:  *px = x - 1; *py = y; break;
  case RIGHT: *px = x;   *py = y + 1; break;
  case DOWN: *px = x + 1; *py = y; break;
  case LEFT: *px = x; *py = y - 1; break;
  }
  if( *px >= 0 && *py >= 0 && *px < nCol && *py < nRow )    // jesli znajduje sie w obszarze pola, czyli ani nie mnjieszje od 0 ani nie wieksze od 9 
    if( pTab[ *px ][ *py ] > nDepth && !pRoot[ *px ][ *py ] )   // jesli glebokosc w danym punkcie jest > depthmin  oraz jesli miejsce sie nie powtarza 
      return 1;
  return 0;


}

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot,
  int x_dest, int y_dest )
{
  static int moveNo = 1;
  pRoot[ x ][ y ] = moveNo++;  // tab1 p Root pamieta droge

  if( x == nRow - 1 && y == nCol - 1 )  // jesli statek znajduje sie w polu koncowym 
  {
    printf( "\n" );
    return 1;
  }
  int x_new;
  int y_new;

  for( int nr = UP; nr <= LEFT; nr++ )   // sprawdzic wszystkie mozliwosci ruchu ,,   od 1 do 4 
  {
    if( move( pTab, nRow, nCol, nDepth, nr, x, y, &x_new, &y_new, pRoot ) )   // jesli funkcja move dziala
      if( root( pTab, nRow, nCol, nDepth, x_new, y_new, pRoot, x_dest, y_dest ) )   // jesli funkcja root dziala  - program trwa dalej 
        return 1;
  }

  pRoot[ x ][ y ] = 0;   // przypadek gdy ! move || !root  - brak trasy do portu 
  moveNo--;
  return 0;
}




void clearRoot( int** pRoot, int nRow, int nCol )   // git
{
  /* for(int i=0; i<nRow; i++)
  for(int j=0; j<nCol;j++)
pRoot[i][j] =0;

  */

  memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
  //return;
}

