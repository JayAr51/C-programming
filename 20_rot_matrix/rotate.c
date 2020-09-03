#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

void rotate(char matrix[10][10]){
int n1=10;
int m1=10;
char temp[n1][m1];
for (int i=0;i<n1;i++){
    for (int j=0;j<m1;j++){
      temp[i][j]=matrix[i][j];
    }
 }// temp is a local copy of matrix
//char *ptrM=matrix;
for (int i=0;i<n1;i++){
    for (int j=0;j<m1;j++){
      matrix[j][m1-1-i]=temp[i][j];
    }
 }// temp is a local copy of matrix
 return;
}
