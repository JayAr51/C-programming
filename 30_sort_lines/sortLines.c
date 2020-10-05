#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct StringArray_ {
  char ** array;
  size_t numLines;
}; typedef struct StringArray_  StringArray; 

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

StringArray readInFile(FILE *f){
      char * line= NULL;
      size_t sz =0;
      StringArray s;
      s.array = NULL;
      s.numLines = 0;
      while(getline(&line, &sz, f) > 0){
	s.numLines++;
	s.array=realloc(s.array, s.numLines * sizeof(s.array));
	s.array[s.numLines-1] = malloc((strlen(line)+1)*sizeof(char));
	for (size_t i = 0; i < strlen(line); i++) {
	  s.array[s.numLines-1][i]=line[i];
	}
      }
      free(line);
      sortData(s.array,s.numLines);
      return s;
}

int writeFile(StringArray data,char * filename){
  int success;
  if (strcmp(filename,"stdout")==0){
    for (size_t i = 0; i < data.numLines; i++) {
      success=fprintf(stdout,"%s",data.array[i]);
      //success=printf("%s",data.array[i]);
      if (success==EXIT_FAILURE){
	return success;
      }
    }
    // free(data.numLines);
  }
  return EXIT_SUCCESS;
}

void freeData(StringArray data){
  for (size_t i = 0; i < data.numLines; i++) {
    free(data.array[i]);
  }
  free(data.array);
}

int main(int argc, char ** argv) {
  if (argc==1){
      StringArray data =readInFile(stdin);
      if (data.array==NULL){
	fprintf(stderr,"empty input?");
	return EXIT_FAILURE;
      }
      int success=writeFile(data,"stdout");
      if (success==EXIT_FAILURE){
      	fprintf(stderr,"problem writing file");
	return EXIT_FAILURE;
      }
      freeData(data);
  }
  else{
    for (int i=1;i<argc;i++){
      FILE *f=fopen(argv[i],"r");
      if (f==NULL){
	fprintf(stderr,"file %s was not found",argv[i]);
	  //return EXIT_FAILURE;
      }
      else{
	StringArray data =readInFile(f);
	if (data.array==NULL){
	  fprintf(stderr,"problem reading file %s",argv[i]);
	}
	int success=writeFile(data,"stdout");
	if (success==EXIT_FAILURE){
	  fprintf(stderr,"problem occurred in writeFile for %s",argv[i]);
	  return EXIT_FAILURE;
	}
	freeData(data);
	if (fclose(f)==EOF){
	  fprintf(stderr,"could not close file %s",argv[i]);
	    return EXIT_FAILURE;
	}
      }
    }
  }
  return EXIT_SUCCESS;
}
