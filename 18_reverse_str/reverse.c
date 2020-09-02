#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  // evaluating length of String
  char *p1=str;// erstellt einen Pointer der an die Stelle des Strings zeigt
  int n=1;
  while (*p1!=0){
    n++;
    p1++;
  } //n enthält die Anzahl an Einträgen inklusive \0
  p1=p1-n+1;
  char p2[n];
  strncpy(p2, p1, n); //p2 sollte gleich p1 sein
  size_t i;
  for (i = 0; i < n && p2[i] != '\0'; i++){
    p1[n-2-i]= p2[i]; //p1 wird umgekehrt und somit auch str
  }
  return;
  //WRITE ME!
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
