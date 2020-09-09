#include <stdio.h>
#include <stdlib.h>
#include  <math.h>

unsigned help_power(unsigned a, unsigned b, unsigned n){
  if (n==0){
    return 1;
  }
  else if(n==1){
    return a;
  }
  else{
    return help_power(a*b,b,n-1);
  }
}

unsigned power(unsigned x, unsigned y){
  return help_power(x, x, y);
}
