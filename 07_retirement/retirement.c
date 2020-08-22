#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int month;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info  retire_info;

double balanceAfterInterest(double balance,retire_info info){
  balance*=(1+info.rate_of_return);
  balance+=info.contribution;
  return balance;
}


void retirement (int startAge,   //in months
		 double initial, //initial savings in dollars
		 retire_info working, //info about working
		 retire_info retired) //info about being retired
{
}

int main(){
  retire_info working;
  working.month=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;

  retire_info retired;
  retired.month=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12;
  int Age_y;
  int Age_m;
  int Age=327;
  double balance=21345;
  //working loop
  while (working.month>0){
    Age_y=Age/12;
    Age_m=Age%12;
    printf("Age %3d month %2d you have $%.2lf\n",Age_y,Age_m,balance);
    balance= balanceAfterInterest(balance,working);
    Age++;
    working.month--;
}
  //retired loop 
  while (retired.month>0){
    Age_y=Age/12;
    Age_m=Age%12;
    printf("Age %3d month %2d you have $%.2lf\n",Age_y,Age_m,balance);
    balance= balanceAfterInterest(balance,retired);
    Age++;
    retired.month--;
}
}
