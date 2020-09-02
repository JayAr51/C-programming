#include <stdio.h>
#include <stdlib.h>

size_t max(int * countedSeq,size_t n){
  size_t maxVal=countedSeq[0];
  for (int i=1;i<n;i++){
    if(maxVal<countedSeq[i]){
      maxVal=countedSeq[i];
    }
  }
  return maxVal;
}
    
    

size_t maxSeq(int * array, size_t n){
  if (n<=0){
    return 0;
  }
  if (n==1){
    return 1;
  }
  int countCurrentSeq=1;
  int seqMax=array[0];
  int countSeq[n]={0};
  size_t maxSeqLength;
  countSeq[0]=1;
  for (int i=1;i<n;i++){
    if (array[i]>seqMax){
      countCurrentSeq++;
    }
    else{
      countCurrentSeq=1;
    }
    seqMax=array[i];
    countSeq[i]=countCurrentSeq;
  }
    maxSeqLength=max(countSeq,n);
  return maxSeqLength;
}
