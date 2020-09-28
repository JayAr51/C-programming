#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NLETTERS 26

unsigned * arrayMax(unsigned * array, unsigned n){ // returns the pointer to the maximum occuring array element
  if (n<=0){
  return NULL;
  }
  unsigned maxVal=array[0];
  unsigned *maxIdx=array;
  int increased=0;
  if (n==1){
    return maxIdx;
  }
  for (int i=1;i<n;i++){
    if (maxVal<array[i]){
	maxVal=array[i];
	maxIdx=&array[i];
	increased++;
      }
  }
  //if (increased==0&&maxVal==0){
  //fprintf(stderr,"No maximum could be found\n");
  //}
  return maxIdx;
}

int getKey(char maxletter) {
  int key;
  if (maxletter>='e'){
    key=maxletter-'e';
  }
  else{
    key='z'-'e'+maxletter-'a'+1;
  }
  return key;
}

int countLetters(FILE * f, unsigned * letterCounts, char * alphabet) {
  int c;
  char * letterptr;
  unsigned idx;
  unsigned counts=0;
  while ((c = fgetc(f)) != EOF&&counts<529000) {
    //fprintf(stderr, "%c",c);
    if (isalpha(c)) {
      counts++;
      if (c>64&&c<91){
	c+=32;
      }
      letterptr=strchr(alphabet, c);
      //substract pointer values, then increase array with resulting index by 1
      idx=letterptr-alphabet;
      if (idx<26){
      letterCounts[idx]++;
      }else{
	printf("%c\n",c);
      }
    }
  }
  if (counts>=52899){
    return EXIT_FAILURE;
  }else{
    return EXIT_SUCCESS;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");  //create stream
  if (f == NULL) {
    fprintf(stderr,"Could not open file");
    return EXIT_FAILURE;
  }
  char * alphabet="abcdefghijklmnopqrstuvwxyz";
  unsigned letterCounts[NLETTERS]={0};
  int success;
  success=countLetters(f, letterCounts, alphabet); //letterCounts wurde erzeugt
  if (success==EXIT_FAILURE){
    printf("%d\n",0);
    //fprintf(stderr,"counting no aphabetic characters\n");
    return EXIT_SUCCESS;
  }
  unsigned *MaxIdx=arrayMax(letterCounts,NLETTERS);
  //if (*MaxIdx==0||MaxIdx==NULL){
  //printf("%d\n",2);
    //fprintf(stderr,"counting no aphabetic characters\n");
    //return EXIT_SUCCESS;
  //}
  if (fclose(f) != 0) {// closeing the file and asking for errors
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printf("%d\n",getKey(alphabet[MaxIdx-letterCounts]));
   return EXIT_SUCCESS;
}
