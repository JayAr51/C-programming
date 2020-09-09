#include <stdio.h>
#include <stdlib.h>
#include  <math.h>

int power(int x, int y); //Prototype

void run_power(int x, int y, int expected_ans){
  if (power(x,y)!=expected_ans){
    printf("failed with x=%d and y=%d \n",x,y);
    exit(EXIT_FAILURE);
  }else{
    return;
  }
}

int main(void){
  int a;
  int b;
  int expected_ans;
  for (a=-1;a<10;a++){
    for (b=0;b<10;b++){
      if (b==0){
	expected_ans=1;
    }
      else{
	expected_ans=a;
	for (int i=1;i<b;i++){
	  expected_ans*=a;
	}
      }
      run_power(a,b,expected_ans);
    }
  }
  return EXIT_SUCCESS;
}
  
