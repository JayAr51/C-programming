#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void freeData(char ** data, size_t n){
  for (size_t i = 0; i < n; i++) {
    free(data[i]);
  }
  free(data);
}

int readInFile(FILE *f){
      char * line= NULL;
      size_t sz =0;
      ssize_t len=0;
      char ** array = NULL;
      size_t n = 0;
      while((len=getline(&line, &sz, f)) >= 0){
	n++;
	array=realloc(array, n * sizeof(*array));
	//array[n-1]=NULL;
	array[n-1]= malloc((len+1)*sizeof(array));
	if (array[n-1]!=0){
	  for (size_t i = 0; i < len+1; i++) {
	    array[n-1][i]=line[i];
	  }
	}
      }
      free(line);
      if (array==NULL){
	fprintf(stderr,"empty input?");
	freeData(array,n);
	return EXIT_FAILURE;
      }
      sortData(array,n);
      for (size_t i = 0; i < n; i++) {
	printf("%s",array[i]);
      }
      freeData(array,n);
      return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  int success=EXIT_SUCCESS;
  if (argc==1){
    success=readInFile(stdin);
    if (success==EXIT_FAILURE){
      fprintf(stderr,"problem occurred in readFile for manual input");
      return EXIT_FAILURE;
    }
  }
  else{
    for (int i=1;i<argc;i++){
      FILE *f=fopen(argv[i],"r");
      if (f==NULL){
	fprintf(stderr,"file %s was not found",argv[i]);
	  //return EXIT_FAILURE;
      }
      else{
	success=readInFile(f);
	if (success==EXIT_FAILURE){
	  fprintf(stderr,"problem occurred in writeFile for %s",argv[i]);
	  return EXIT_FAILURE;
	}
	if (fclose(f)==EOF){
	  fprintf(stderr,"could not close file %s",argv[i]);
	  return EXIT_FAILURE;
	}
      }
    }
  }
  return EXIT_SUCCESS;
}
//int writeFile(StringArray data,char * filename){
  //int success=0;
  //  if (strcmp(filename,"stdout")==0){
  //  for (size_t i = 0; i < data.numLines; i++) {
      //   fprintf(stdout,"%s",data.array[i]);
//  printf("%s",data.array[i]);
      //if (success<0){
      //return success;
      //}
//  }
    // free(data.numLines);
    //}
  /*else //if (strcmp(filename,"stderr")==0){
    {for (size_t i = 0; i < data.numLines; i++) {
      success=fprintf(stderr,"%s",data.array[i]);
      //success=printf("%s",data.array[i]);
      if (success<0){
	return success;
      }
    }
    // free(data.numLines);
    }*/
  //return EXIT_SUCCESS;
//}
