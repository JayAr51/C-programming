#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  int arr1[]={1, 2, 3, 4, 5 ,6};
  if (maxSeq(arr1,6)!=6){
      printf("failed on 1");
    return EXIT_FAILURE;
  }
  int arr2[]={0, 1, 1, 1, 1, 2};
  if (maxSeq(arr2,6)!=2){
      printf("failed on 2");
    return EXIT_FAILURE;
    }
  int arr3[]={6, 5, 4, 3};
  if (maxSeq(arr3,4)!=1){
      printf("failed on 3");
    return EXIT_FAILURE;
  }
  int arr4[]={1, -2};
  if (maxSeq(arr4,2)!=1){
      printf("failed on 4");
    return EXIT_FAILURE;
    }
  int arr5[]={2, 93, 94, 1, 2, 3, 4};
  if (maxSeq(arr5,7)!=4){
      printf("failed on 5");
    return EXIT_FAILURE;
    }
  int arr6[]={2, 3, 1, 2, 3};
  if (maxSeq(arr6,5)!=3){
      printf("failed on 6");
    return EXIT_FAILURE;
    }
  int arr7[]={-2, -3, -4, 2, 3};
  if (maxSeq(arr7,5)!=3){
      printf("failed on 7");
    return EXIT_FAILURE;
    }
  int arr8[0]={};
  if (maxSeq(arr8,0)!=0){
      printf("failed on 8");
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
