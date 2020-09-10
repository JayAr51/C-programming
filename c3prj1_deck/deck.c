#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_card(card_t);
char suit_letter(card_t);
char value_letter(card_t);

void print_hand(deck_t * hand){
  deck_t str=*hand;
  for (int i=0; i<str.n_cards;i++){
    print_card(*str.cards[i]);
    printf(" ");
  }
}

unsigned card2num(card_t c){
  unsigned num;
  num=c.suit*13+c.value-2;
  return num;
}

int deck_contains(deck_t * d, card_t c) {
  int contains=0;
  deck_t str=*d;
  for (int i=0; i<str.n_cards;i++){
    if (card2num(*str.cards[i])==card2num(c)){
      contains++;
    }
  }
  return contains;
}

void shuffle(deck_t * d){
  deck_t str=*d;
  int num_cards=str.n_cards;
  card_t temp_cards[num_cards]; //cards is a pointer to a cards
  int card_idx[num_cards];
  int idx=0;
  int contains;
  int i;
  for (i=0;i<num_cards;i++){
    temp_cards[i]=*str.cards[i];
  }
  while (idx<num_cards){//array with intended indeces is created
    card_idx[idx]=random()%num_cards;
    contains=0;
    i=0;
    while (i<idx && contains==0){
	if (card_idx[i]==card_idx[idx]){
	  contains=1;
	}
	i++;
      }
      if (contains==0){
	idx++;
      }   
  }
  //Now new indeces need to be adressed
  for (int j=0;j<num_cards;j++){
    *str.cards[j]=temp_cards[card_idx[j]];
  }
      assert_full_deck(&str);
}

void assert_full_deck(deck_t * d) {
  deck_t str=*d;
  int num_cards=str.n_cards;
  int contains;
  int i;
  for (i=0;i<num_cards;i++){
   contains= deck_contains(&str, *str.cards[i]);
   assert(contains==1);
  }
}
