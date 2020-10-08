#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
    counts_t * c=malloc(sizeof(counts_t));
    c->counts = NULL;
    c->entries = 0;
    c->unknown = 0;
    return c;
}

void initCount(counts_t * c, const char * name){
  c->entries++;
  c->counts = realloc(c->counts, c->entries*sizeof(c->counts));
  c->counts[c->entries-1]=calloc(1,sizeof(one_count_t));
  c->counts[c->entries-1]->count=1;
  c->counts[c->entries-1]->strexp=calloc(strlen(name),sizeof(name));
  c->counts[c->entries-1]->strexp=strcpy(c->counts[c->entries-1]->strexp,name);
  return;
}

  
void addCount(counts_t * c, const char * name) {
  int counted=0;
  int i=0;
  if (name==NULL){
    c->unknown++;
  }else{
  //look for match in array of structs and increment if found
    while (i<c->entries && counted==0){
      if (strcmp(name,c->counts[i]->strexp)==0){
	c->counts[i]->count++;
	counted++;
      }
      i++;
    }
    if (counted==0){
      initCount(c, name);
    }
  }
  return;
}

void printCounts(counts_t * c, FILE * outFile) {
  for (int i=0; i<c->entries; i++){
    fprintf(outFile,"%s: %d\n",c->counts[i]->strexp,c->counts[i]->count);
  }
  if (c->unknown>0){
    fprintf(outFile,"<unknown>: %d\n",c->unknown);
  }
  return;
}

void freeCounts(counts_t * c) {
  for (int i=0;i<c->entries;i++){
    free(c->counts[i]->strexp);
    //free(c->counts[i]->count);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
  return;
}
