#include "cards.h"
#include <stdio.h>
#include <stdlib.h>
/*
void int2str(int i)
char c = (char)i;
printf(i);
printf('\n');
printf(c);
printf('\n');
return;
}*/

/*const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH"; break;
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND"; break;
  case FULL_HOUSE: return "FULL_HOUSE"; break;
  case FLUSH: return "FLUSH"; break;
  case STRAIGHT: return "STRAIGHT"; break;
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND"; break;
  case TWO_PAIR: return "TWO_PAIR"; break;
  case PAIR: return "PAIR"; break;
  case NOTHING: return "NOTHING"; break;
  }*/

int main(void) {
  //  char msg  =ranking_to_string(r);
  //  printf(msg);
  //  void int2str(int num=55)
  char val;
  char suit;
  card_t temp;
  for(unsigned c=0;c<52;c++){
  temp=card_from_num(c);
  print_card(temp);
  printf(" ");
  suit=suit_letter(temp);
  val=value_letter(temp);
  temp=card_from_letters(val, suit);
  print_card(temp);
  printf("\n");
  }
  return EXIT_SUCCESS;
}
