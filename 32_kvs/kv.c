#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void  writeKVPairToArray(kvpair_t * kvp, char * input, ssize_t len, char seperator){
  char * lePtr;
  unsigned idx;
  int sep=(int)seperator;
  lePtr=strchr(input, sep);
  idx=lePtr-input;
  kvp->key=malloc((idx+1)*sizeof(kvp->key));
  kvp->value=malloc((len-1-idx)*sizeof(kvp->value));
  for (int i=0;i<idx;i++){
    kvp->key[i]=input[i];
  }
  kvp->key[idx]=(char)0;
  for (int i=idx+1;i<len-1;i++){
    kvp->value[i-idx-1]=input[i];
  }
  
  /*kvp.key=malloc((idx+1)*sizeof(kvp.key));
  kvp.value=malloc((len-1-idx)*sizeof(kvp.value));
  for (int i=0;i<idx;i++){
    kvp.key[i]=input[i];
  }
  kvp.key[idx]=(char)0;
  for (int i=idx+1;i<len;i++){
    kvp.value[i-idx-1]=input[i];
  }*/
  return;
}

	
kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen (fname, "r");
  if (f == NULL) {
    return NULL; //Could not open file->indicate failure
  }
  kvarray_t * kvArr=malloc(sizeof(kvarray_t));
      char * line= NULL;
      size_t sz =0;
      ssize_t len=0;
      kvArr->kv = NULL;
      kvArr->entries = 0;
      while((len=getline(&line, &sz, f)) > 0){
	kvArr->entries++;
	kvArr->kv=realloc(kvArr->kv, kvArr->entries * sizeof(kvArr->kv)); //array of pointers zu kvpair wird in Speichergröße angepasst
	kvArr->kv[kvArr->entries-1]=malloc(sizeof(kvpair_t));
	writeKVPairToArray(kvArr->kv[kvArr->entries-1],line,len,'=');
      }
      free(line);
      if (fclose(f)!=0){
	fprintf(stderr,"could not close file %s",fname);
      }
      return kvArr;
}

void freeKVs(kvarray_t * pairs) {
  for (int i=0;i<pairs->entries;i++){
    free(pairs->kv[i]->key);
    free(pairs->kv[i]->value);
    free(pairs->kv[i]);
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
