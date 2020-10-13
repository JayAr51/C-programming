#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {/*card_t is a struct defined by a value and a suit */
  assert(c.value>=2&&c.value<=VALUE_ACE);
  assert(c.suit>=SPADES&&c.suit<=NUM_SUITS);
}

int is_card_valid(card_t c) {/*card_t is a struct defined by a value and a suit */
  //returns EXITS_SUCCESS if valid, else EXIT_FAILURE 
  if ((c.value>=2&&c.value<=VALUE_ACE)&&(c.suit>=SPADES&&c.suit<=CLUBS)){
    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}

const char * ranking_to_string(hand_ranking_t r) {
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
  default:  return "invalid"; break;
}
}
  char value_letter(card_t c) {/*get c.value and c.suit and transfer it to a 2digit char */
    char value;
    // assining the value;
    // 2-14
    switch (c.value){
    case VALUE_ACE: value='A'; break;
    case VALUE_KING: value='K'; break;
    case VALUE_QUEEN: value='Q'; break;
    case VALUE_JACK: value='J'; break;
    default:
      value='0';
      if (c.value<VALUE_JACK-1){
	value=value+c.value;
      }
    break;
    }   
    return value;
}


char suit_letter(card_t c) {
  char suit;
  switch(c.suit){
    case SPADES: suit='s'; break;
    case HEARTS: suit='h'; break;
    case DIAMONDS: suit='d'; break;
    case CLUBS: suit='c'; break;
    default: suit='?'; break;
    }
  return suit;
}

void print_card(card_t c) {
  // char* card2[2];
    char suit=suit_letter(c);
    char value=value_letter(c);
    // combining the chars;
    /*/if (sizeof(card2) < (strlen(suit) + strlen(value) + 1) ) {
      fprintf(stderr, "Final size of filename is too long!\n");
     return;
     }
    strncpy(card2, value, sizeof(card2));
    strncat(card2, suit, (sizeof(card2) - strlen(card2)) );
    */
    printf("%c%c", value, suit);
      //card2=strncat(card2,value,1);
      //card2 = strncat(card2,suit,1);
      //printf(card2);
    // printf(suit);
    return;
}

card_t card_from_letters(char value_let, char suit_let) {
  //two chars are provided which contain a 0-9,J,Q,K,A and sdhc
  card_t temp;
  switch (value_let){
  case 'A': temp.value=VALUE_ACE; break;
  case 'K': temp.value=VALUE_KING; break;
  case 'Q': temp.value=VALUE_QUEEN; break;
  case 'J': temp.value=VALUE_JACK; break;
  default:
    if (value_let=='0'){
	temp.value=10;
      }
    else{
      temp.value=value_let-48;
	}
    break;
    }
  // suit letter assignment
    switch(suit_let){
    case 's': temp.suit=SPADES; break;
    case 'h': temp.suit=HEARTS; break;
    case 'd': temp.suit=DIAMONDS; break;
    case 'c': temp.suit=CLUBS; break;
    default: //printf("fail in cards from letters");
      temp.suit=NUM_SUITS;
      break;
    }
    //assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  assert(c<52);
  card_t temp;
  //char suit;
  //char value;
  unsigned rem=c%13;
  rem+=2;
  unsigned suit_val=c/13;
  temp.value=rem;
  temp.suit=suit_val;
  return temp;
}
