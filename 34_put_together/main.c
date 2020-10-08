#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

char * makeCountFileName(const char * cName) {
  const char * suffix = ".count";
  unsigned len = strlen(cName) + strlen(suffix) + 1;
  char * ans = malloc(len * sizeof(*ans));
  snprintf(ans, len, "%s%s", cName, suffix);
  return ans;
}


char * getValueFromKV(char * ptr,kvarray_t * c,char * key){
  char *value=ptr;
  int counted=0;
  int i=0;
  //look for match in array of kv structs and increment if found
    while (i<c->entries && counted==0){
      if (strcmp(key,c->kv[i]->key)==0){
	value=realloc(value,strlen(c->kv[i]->value)*sizeof(char));
	value=strcpy(value,c->kv[i]->value);
	counted++;
      }
      i++;
    }
    if (counted==0){
      return NULL;
    }else{
      return value; 
    }
}


counts_t * countFile(const char * filename, kvarray_t * kv) {
  //WRITE ME
  counts_t * c = createCounts();
    FILE * f = fopen (filename, "r");
  if (f == NULL) {
    fprintf(stderr,"could not open file %s",filename);
    return NULL; //Could not open file->indicate failure
  }
  char * idxP=NULL;
  int idx=0;
  char * line= NULL;
  char * key= NULL;
  size_t sz =0;
  ssize_t len=0;
  char * value=NULL;
  while((len=getline(&line, &sz, f)) > 0){
    idxP=strchr(line, '\n');
      if (idxP==NULL){
	key=calloc((len),sizeof(char));
	key=strcpy(key,line);
      }else{
	idx=idxP-line;
	key=calloc((idx+1),sizeof(char));
	key=strncpy(key,line,(idx));
	key[idx]='\0';
      }
    value = getValueFromKV(value,kv,key);
    addCount(c, value);
    free(key);
  }
  free(line);
  free(value);
  return c;
}

int main(int argc, char ** argv) {
  if (argc<3){
    fprintf(stderr, "useage ./a keyvaluepairs file2count1 file2count2 ...\n");
    return EXIT_FAILURE;
  }
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i=2; i<argc; i++){
    
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = makeCountFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f=fopen(outName,"w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f)==EXIT_FAILURE){
      fprintf(stderr,"could not close file %s\n",outName);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
    freeKVs(kv);
  return EXIT_SUCCESS;
}
