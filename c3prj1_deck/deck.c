#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_card(card_t);
char suit_letter(card_t);
char value_letter(card_t);
deck_t * initDeck(void);
int is_card_valid(card_t c);

void free_deck(deck_t * deck){
  for (int i=0; i<deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
  return;
}

card_t * add_empty_card(deck_t * deck){
  deck->cards=realloc(deck->cards, (deck->n_cards+1)*sizeof(deck->cards));
  deck->cards[deck->n_cards]=malloc(sizeof(card_t));
  deck->cards[deck->n_cards]->value=0;
  deck->cards[deck->n_cards]->suit=NUM_SUITS;
  deck->n_cards++;
  return deck->cards[deck->n_cards-1];
}

void add_card_to(deck_t * deck, card_t c){
  deck->cards=realloc(deck->cards, (deck->n_cards+1)*sizeof(deck->cards));
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
  for (unsigned i=0; i<n;i++){
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
  deck_t * d=calloc(1,sizeof(*d));
  d->cards=NULL;
  d->n_cards=0;
  return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  // Durchlaufe hands, durchsuche dabei jede Hand, speichere die gefundenen Hände in excluded cards, falls sie nicht schon existieren;
  deck_t * hand_cards=initDeck();
  for (int i=0; i<n_hands; i++){
    for (int j=0; j<hands[i]->n_cards; j++){
      if (is_card_valid(*hands[i]->cards[j])==EXIT_SUCCESS){
	add_card_to(hand_cards, *hands[i]->cards[j]);
      }
    }
  }
  deck_t * d=make_deck_exclude(hand_cards);
  free_deck(hand_cards);
  return d;
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
  for (int i=0; i<d->n_cards;i++){
    if (card2num(*d->cards[i])==card2num(c)){
      contains++;
    }
  }
  return contains;
}

/*void shuffle(deck_t * d){
  card_t temp_cards[d->n_cards]; //cards is a pointer to a cards
  int card_idx[d->n_cards];
  int idx=0;
  int contains;
  int i;
  int n_runs=0;
  for (i=0;i<d->n_cards;i++){
    temp_cards[i]=*d->cards[i];
  }
  //draw random number and assign to card_idx[idx]
  while (idx<d->n_cards){//array with intended indeces is created
      card_idx[idx]=random()%d->n_cards;
      contains=0;
      i=0;
      // test if random number already exists in array
      while (i<idx){
	n_runs++;
	if (card_idx[i]==card_idx[idx]){
	  contains=1;
	  break;
	}
	i++;
      }
      // If random number does not exist in array, then leave loop
      if (contains==0){
	idx++;
      }   
    }
    //Now new indeces need to be adressed
    for (int j=0;j<d->n_cards;j++){
      *d->cards[j]=temp_cards[card_idx[j]];
    }
    assert_full_deck(d);
    printf("%d \n",n_runs);
}*/

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

void shuffle(deck_t * d){
  card_t temp_cards[d->n_cards]; //cards is a pointer to a cards
  int indices[d->n_cards];
  int n=d->n_cards;
  int randy;
  for (int i=0;i<d->n_cards;i++){
    temp_cards[i]=*d->cards[i];
    indices[i]=i;
  }
  for (int j=0;j<d->n_cards;j++){
    randy=random()%n;
    n--;
    *d->cards[j]=temp_cards[indices[randy]];
    for (int k=randy; k<n; k++){
      indices[k]=indices[k+1];
    }
  }
  //assert_full_deck(d);
}
