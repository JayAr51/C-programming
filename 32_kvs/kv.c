#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

int  writeKVPairToArray(kvpair_t * kvp, char * input, ssize_t len, char seperator){
  char * lePtr;
  unsigned idx;
  int sep=(int)seperator;
  lePtr=strchr(input, sep);
  if (lePtr==NULL){
    fprintf(stderr,"no seperator %c can be found",sep);
    return EXIT_FAILURE;
  }
  idx=lePtr-input;
  if (idx>=len-1){
    fprintf(stderr,"value can be found found");
    return EXIT_FAILURE;
  }
  kvp->key=malloc((idx+1)*sizeof(char));//kvp->key));
  kvp->value=malloc((len-1-idx)*sizeof(char));//kvp->value));
  for (int i=0;i<idx;i++){
    kvp->key[i]=input[i];
  }
  kvp->key[idx]=(char)0;
  for (int i=idx+1;i<len-1;i++){
    kvp->value[i-idx-1]=input[i];
  }
  return EXIT_SUCCESS;
}

	
kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen (fname, "r");
  if (f == NULL) {
    fprintf(stderr,"could not open file %s",fname);
    return NULL; //Could not open file->indicate failure
  }
  kvarray_t * kvArr=malloc(sizeof(kvarray_t));
      char * line= NULL;
      size_t sz =0;
      ssize_t len=0;
      int success=EXIT_SUCCESS;
      kvArr->kv = NULL;
      kvArr->entries = 0;
      while((len=getline(&line, &sz, f)) > 0){
	kvArr->entries++;
	kvArr->kv=realloc(kvArr->kv, kvArr->entries * sizeof(kvArr->kv)); //array of pointers zu kvpair wird in Speichergröße angepasst
	kvArr->kv[kvArr->entries-1]=malloc(sizeof(kvpair_t));
	success=writeKVPairToArray(kvArr->kv[kvArr->entries-1],line,len,'=');
	if (success==EXIT_FAILURE){
	  kvArr->entries--;
	  free(kvArr->kv[kvArr->entries]);
	}
	
      }
      free(line);
      if (fclose(f)!=0){
	fprintf(stderr,"could not close file %s\n",fname);
      }
      if ( kvArr->entries==0){
	return NULL;
      }
      return kvArr;
}

void freeKVEntry(kvarray_t * pairs,int i){
  free(pairs->kv[i]->key);
  free(pairs->kv[i]->value);
  free(pairs->kv[i]);
  return;
}

void freeKVs(kvarray_t * pairs) {
  for (int i=0;i<pairs->entries;i++){
    freeKVEntry(pairs,i);
  }
  free(pairs->kv);
  free(pairs);
  return;
}

void printKVs(kvarray_t * pairs) {
  for (int i=0;i<pairs->entries;i++){
    printf("key = '%s' value = '%s'\n",pairs->kv[i]->key,pairs->kv[i]->value);
  }
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i=0;i<pairs->entries;i++){
    if (strcmp(pairs->kv[i]->key,key)==0){
      return pairs->kv[i]->value;
  }
}
return NULL;
}
