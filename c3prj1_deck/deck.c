#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_card(card_t);
char suit_letter(card_t);
char value_letter(card_t);
deck_t * initDeck(void);

void free_deck(deck_t * deck){
  for (int i; i<deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
  return;
}

void add_card_to(deck_t * deck, card_t c){
  deck->cards=realloc(deck->cards, (deck->n_cards+1)*sizeof(card_t));
  deck->cards[deck->n_cards]=malloc(sizeof(card_t));
  deck->cards[deck->n_cards]->value=c.value;
  deck->cards[deck->n_cards]->suit=c.suit;
  deck->n_cards++;
  return;
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  int n=52;
  deck_t * d=initDeck();
  int contains;
  card_t temp_card;
  for (unsigned i; i<n;i++){
    temp_card=card_from_num(i);
    contains=deck_contains(excluded_cards,temp_card);
    if (contains==0){
      add_card_to(d, temp_card);
    }
  }
  // erstelle ein array aus zahlen, erstelle ein leeres deck, füge eine Karte hinzu falls der numerische wert nicht in excluded_cards enthalten ist.
  return d;
}

deck_t * initDeck(void){
  deck_t * d=malloc(sizeof(d));
  d->cards=NULL;
  d->n_cards=0;
  return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  // Durchlaufe hands, durchsuche dabei jede Hand, speichere die gefundenen Hände in excluded cards, falls sie nicht schon existieren;
  deck_t * hand_cards=initDeck();
  for (int i; i<n_hands; i++){
    for (int j; j<hands[i]->n_cards; j++){
      if (is_card_valid(hands[i]->cards[j])==EXIT_SUCCESS){
	add_card_to(hand_cards, hands[i]->cards[j]);
      }
    }
  }
  deck_t * d=make_deck_exclude(hand_cards);
  free(hand_cards);
  return d;
}


card_t * add_empty_card(deck_t * deck){
  deck=realloc(deck, (deck->n_cards+1));
  deck->cards[n_cards]=malloc(sizeof(card_t));
  deck->cards[n_cards].value=0;
  deck->cards[n_cards].suit=NUM_SUITS;
  deck->n_cards++;
  return deck->cards[n_cards-1];
}

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
    if (card2num(str->cards[i])==card2num(c)){
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
