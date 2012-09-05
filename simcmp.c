// simcmp.c -- A Simple Macro Compiler in C, CRB, Apr 26, 2002
// Adapted from original FORTRAN SIMCMP by W. M. Waite.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE 12000
#define LINELEN 80

short iread(short list[], int index);
short ipnch(short list[], int strt, int stop);
int simcmp(void);

FILE * fpin, * fpout;

short list[SPACE];

int main(int argc, char * argv[])
{
  int stat;

#ifdef DEBUG  
  fpin = fopen("simtst.txt", "r");
  if ( fpin == NULL )
  {
    puts("Can't open simtst.txt");
    exit ( -1 );
  }
  fpout = stdout;
#else
  if ( argc > 1 )	// use argv[1]  if any for input file
  {
    if ( (fpin=fopen(argv[1], "r")) == NULL )
    {
      printf("Can't open '%s' to read.\n", argv[1]);
      exit ( 1 );
    }
  }
  else
    fpin = stdin;	// else default to stdin

  if ( argc > 2 )	// use argv[2] if any for output file
  {
    if ( (fpout=fopen(argv[2], "w")) == NULL )
    {
      printf("Can't open '%s' to write.\n", argv[2]);
      exit ( 2 );
    }
  }
  else
    fpout = stdout;	// else default to stdout
#endif

  // call the simple compiler
  stat = simcmp();
  return stat;
}

int simcmp(void)
{
  int i, j, k, l, m, n, kmax;

  kmax = SPACE - LINELEN;
  // read flag line into list[1] through list[5]
  if ( (i=iread(list, 1)) == -1 ) { puts("Exit 10"); exit ( 10 );}
  list[6] = 100;
  k = 18;

  // read one macro definition
 L1:
  list[k] = -1;
  if ( (i=iread(list, k + 1)) == -1 ) { puts("Exit 11"); exit ( 11 );}
  if ( i >= kmax ) { puts("Exit 20"); exit ( 20 );}
  list[i+1] = list[1];
  i = k;
 L2:
  i++;
  if ( list[i] == list[1] ) goto L13;
  goto L2;
 L10:
  i++;
  if ( list[i] == list[3] ) goto L12;
 L11:
  if ( list[i] != list[4] ) goto L10;
  list[i] = -2;
  list[i+1] = list[i+1] - list[5] + 7;
  i += 2;
  list[i] = list[i] - list[5];
  if ( list[i-1] != 7 ) goto L10;
  if ( list[k] < list[i] ) list[k] = list[i];
  goto L10;

  // an end-of-line flag has been encountered, replace with -1
 L12:
  list[i] = -1;
 L13:
  i++;
  if ( (j=iread(list, i)) == -1 ) { puts("Exit 12"); exit ( 12 );}
  if ( j >= kmax ) { puts("Exit 21"); exit ( 21 );}
  list[j] = list[3];
  if ( list[i] != list[3] ) goto L11;
  list[k-1] = i;
  k = i + 1;
  if ( k >= j ) goto L1;
  if ( list[k] != list[3] ) goto L1;
  // fall through at end of macro definitions

  // read next line to be expanded
 L20:
  if ( (n=iread(list, i)) == -1 ) return 0;
  list[n] = list[1];
  m = 17;
 L30:
  l = 8;
  j = m + 1;
  k = i;
 L34:
  if ( k > n ) goto L41;
  j++;
  if ( list[j] == list[2] ) goto L32;
  if ( list[j] != list[k] ) goto L31;
  if ( list[j] == list[1] ) goto L40;
  goto L33;
 L31:
  m = list[m];
  if ( m < i ) goto L30;
  if ( ipnch(list, i, n) == -1 ) { puts("Exit 30"); exit ( 30 );}
  goto L20;
 L32:
  if ( list[k] == list[1] ) goto L31;
  list[l] = list[k];
  l++;
 L33:
  k++;
  goto L34;
 L41:
  list[k] = list[j];
 L42:
  k++;
 L43:
  j++;
  if ( list[m] == j ) goto L48;
  if ( list[j] + 1 > 0 ) goto L41;
  if ( list[j] + 1 == 0 ) goto L47;
 L44:
  l = list[j+1];
  j += 2;
  if ( l == 7 ) goto L45;
  if ( list[j] != 0 ) goto L46;
  list[k] = list[l];
  goto L42;

  // compute the generated symbol for a parameter call
 L45:
  list[7] = list[j] + list[6];
 L46:
  list[k] = list[l] / 100;
  n = list[l] / 10;
  list[k+1] = n - list[k]*10 + list[5];
  list[k+2] = list[l] - n*10 + list[5];
  list[k] = list[k] + list[5];
  k = k + 3;
  goto L43;

  // when end-of-line is recognized write out the line.
 L47:
  if ( ipnch(list, i, k) == -1 ) { puts("Exit 31"); exit ( 31 ); }
 L40:
  k = i;
  goto L43;

  // the current macro has been completely expanded.
 L48:
  list[6] = list[m+1] + list[6] + 1;
  goto L20;
}

short iread(short list[], int index)
{
  char * p, buffer[LINELEN+2];
  int i, len;

  p = fgets(buffer, LINELEN+1, fpin);
  if ( p == NULL ) return -1;
  len = strlen(buffer);
  if ( buffer[len-1] == '\n' )
  {
    buffer[len-1] = '\0';	// remove the '\n' if any
    len--;
  }
  for ( i = 0; i < len; i++ )	// copy buffer to user
    list[index + i] = buffer[i];
  return index + len;		// return index of next available
}

short ipnch(short list[], int start, int stop)
{
  int i;

  // print the characters from start to stop
  for ( i = 0; i < stop-start; i++ )
    fputc(list[start + i], fpout);
  fputc('\n', fpout);		// add a newline
  return 0;
}
