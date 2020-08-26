#include <stdlib.h>
#include <stdio.h>
void isPrimeb1(int a);

void isPrimeb2(int a);

void isPrimeb3(int a);

void isPrimeb4(int a);

void isPrimec(int a);

// testfunktion soll auf basis isprime-broken für eine große Anzahl von Daten testen und anzeigen
void testing(int fn, int lower, int upper){
  for (int i=lower;i<=upper;i++){
    switch(fn) {
      case 1:
	isPrimeb1(i);
	break;
      case 2:
	isPrimeb2(i);
	break;
      case 3:
	isPrimeb3(i);
	break;
      case 4:
	isPrimeb4(i);
	break;
      case 0:
	isPrimec(i);
	break;
      }
  }
  return;
}
