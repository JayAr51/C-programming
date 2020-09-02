#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSTRS 3
int main(void) {
  const char * strs[NSTRS] = {"apple", "bannana", "carrot"};// defines an array of pointers, pointing to 3 different strings
  
  for (int i = 0; i < NSTRS; i++) {
    const char * a = strchr(strs[i], 'a');// returns a pointer to the first 'a' in strs[i] while strs[i] is a char * (also a pointer)
    a++; // the location the the pointer points to is increased by 1
    printf("%c\n", *a); // the next letter is printed e.g. p n or r
    printf("%c\n", a[2]); //prints the location of the third a 
    a = strstr(strs[i], "nana");
    if (a != NULL) {
      printf("%s has %s %ld characters into it!\n", strs[i], a, a - strs[i]);
    }
  }
  const char * ptr = strs[2];
  while (*ptr != '\0') {
    char x = *ptr + 3;
    printf("%c", x);
    ptr++;
  }
  printf("\n");
  return EXIT_SUCCESS;
}
