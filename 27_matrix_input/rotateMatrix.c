#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MATRIXSIZE 10

void rotate(char matrix[MATRIXSIZE][MATRIXSIZE]){
  char temp[MATRIXSIZE][MATRIXSIZE];
for (int i=0;i<MATRIXSIZE;i++){
    for (int j=0;j<MATRIXSIZE;j++){
      temp[i][j]=matrix[i][j];
    }
 }// temp is a local copy of matrix
//char *ptrM=matrix;
for (int i=0;i<MATRIXSIZE;i++){
    for (int j=0;j<MATRIXSIZE;j++){
      matrix[j][MATRIXSIZE-1-i]=temp[i][j];
    }
 }// temp is a local copy of matrix
 return;
}

int main(int argc, char** argv){
  if (argc<2||argc>3){
        fprintf(stderr,"usage gitrunner filename");
	return EXIT_FAILURE;
    }
  FILE * f = fopen(argv[1], "r");
if (f == NULL) {
  fprintf(stderr,"no file exists");
  return EXIT_FAILURE;
 }
int c;
void * isnewline;
unsigned j=0;
unsigned i=0;
char matrix[MATRIXSIZE][MATRIXSIZE];
 while ( (c=fgetc(f)) != EOF ) {//reading in file
   isnewline=strchr("\n",c);
   if (isnewline==NULL){//write and increase column index
    matrix[i][j]=c;
    j++;
    if(j>MATRIXSIZE){
      fprintf(stderr,"line %d to long",j);
      return EXIT_FAILURE;
    }
   }
   else{//check for right column size and increase row index 
    if(j<MATRIXSIZE){
      fprintf(stderr,"line %d to short",j);
	return EXIT_FAILURE;
    }
    else if(j>MATRIXSIZE){
      fprintf(stderr,"line %d to long",j);
	return EXIT_FAILURE;
    }
    j=0;
    i++;
    if(i>MATRIXSIZE){
      fprintf(stderr,"column to long");
      return EXIT_FAILURE;
    }
   }
}
    if(i<MATRIXSIZE){
      fprintf(stderr,"column to short");
	return EXIT_FAILURE;
    }

    if (fclose(f)!=EXIT_SUCCESS){
      fprintf(stderr,"file could not be closed");
    } 
    rotate(matrix);
    if (argc==3){
      FILE * w = fopen(argv[2], "w");
      for (int i=0;i<MATRIXSIZE;i++){
	for (int j=0;j<MATRIXSIZE;j++){
	  fprintf(w,"%c",matrix[i][j]);
	}
	fprintf(w,"\n");
      }
      if (fclose(w)!=EXIT_SUCCESS){
	fprintf(stderr,"file could not be closed");
	return EXIT_FAILURE;
      }
      else{
	return EXIT_SUCCESS;
      }
    }
    else{
      for (int i=0;i<MATRIXSIZE;i++){
	for (int j=0;j<MATRIXSIZE;j++){
	  printf("%c",matrix[i][j]);
	}
	printf("\n");
      }
      return EXIT_SUCCESS;
    }
}
