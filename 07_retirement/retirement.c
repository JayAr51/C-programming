#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info  retire_info;

double initialAfterInterest(double initial,retire_info info){
  initial*=(1+info.rate_of_return);
  initial+=info.contribution;
  return initial;
}


void retirement (int startAge,double initial, retire_info working, retire_info retired)
{
  int Age=startAge;
  int Age_y;
  int Age_m;
   //working loop
  while (working.months>0){
    Age_y=Age/12;
    Age_m=Age%12;
    printf("Age %3d month %2d you have $%.2lf\n",Age_y,Age_m,initial);
    initial= initialAfterInterest(initial,working);
    Age++;
    working.months--;
}
  //retired loop 
  while (retired.months>0){
    Age_y=Age/12;
    Age_m=Age%12;
    printf("Age %3d month %2d you have $%.2lf\n",Age_y,Age_m,initial);
    initial= initialAfterInterest(initial,retired);
    Age++;
    retired.months--;
    }
  return;
}

int main(){
  retire_info working;
  working.months=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;

  retire_info retired;
  retired.months=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12;
  int startAge=327;
  double initial=21345;
  retirement(startAge,initial,working,retired);
  return EXIT_SUCCESS;
}
