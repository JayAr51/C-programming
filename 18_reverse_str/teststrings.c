#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int main(void){
  const char * words2[] = {"A", "cat", "likes", "sleeping.", NULL};
  const char ** ptr = words2;
  while (*ptr != NULL) {
    printf("%s ", *ptr);
    ptr++;
  }
  printf("\n");
  return EXIT_SUCCESS;
}
