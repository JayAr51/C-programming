#include <stdio.h>
#include <stdlib.h>

typedef struct rect_tag{
  int left;
  int bottom;
  int right;
  int top;
}rect_t;
  
int max(int num1, int num2) {
  if (num1>num2){
    return num1;
  }
  else{
    return num2;
  }
}

int min(int num1, int num2) {
  if (num1<num2){
    return num1;
  }
  else{
    return num2;
  }
}
int isInRange(int num,int num1, int num2){
 int  upper=max(num1,num2);
 int  lower=min(num1,num2);
 if (num<=upper && num>=lower){
  return 1;
}
 else{
   return 0;
 }
}

int isAtBoarder(int x,int y, rect_t myrect){
  int iirx=isInRange(x,myrect.left,myrect.right);
    int iiry=  isInRange(y,myrect.top,myrect.bottom);
    if ((x==myrect.left || x==myrect.right) && iiry){
    return 1;
  }
  if ((y==myrect.top || y==myrect.bottom) && iirx){
    return 1;
}
  return 0;
}

void squares(int size1, int x_offset2, int y_offset2, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
 int  w=max(size1,x_offset2+size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
 int  h=max(size1,y_offset2+size2);
 rect_t s1, s2;
// square1
  s1.left=0;
  s1.top=0;
  s1.right=s1.left+size1-1;
  s1.bottom=s1.top+size1-1;
  // square2
  s2.left=x_offset2;
  s2.top=y_offset2 ;
  s2.right=s2.left+size2-1;
  s2.bottom=s2.top+size2-1;
  
  //count from 0 to h. Call the number you count with y
  for (int y=0;y<h;y++){
    //count from 0 to w. Call the number you count with x
    for (int x=0;x<w;x++){
      //check if  EITHER
      //   ((x is between x_offset  and x_offset +size2) AND 
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      if (isAtBoarder(x,y,s2)){ 
      //  OR
      //   ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
		   printf("*");
    }
      else {
	if (isAtBoarder(x,y,s1)){
	    printf("#");
	  }
	else{
	  printf(" ");
	}
      }
    }	  
    printf("\n");
  }
      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #

      //else print a space
    //when you finish counting x from 0 to w, 
    //print a newline

}
