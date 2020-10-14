#include "future.h"
#include <stdlib.h>
#include <stdio.h>
deck_t * initDeck(void);

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  // adds a pointer to a card in hands to future cards. The deck[index] contains a number of cards corresponding to the number of occurence of the unknown card. If the index does not exist yet, space has to be reallocated;
  if (index>=fc->n_decks){
    fc->decks=realloc(fc->decks,(index+1)*sizeof(deck_t));
    for (int i=fc->n_decks; i<=index; i++){
       	fc->decks[i]=*initDeck();
    }
    fc->n_decks=index+1;
  }
  fc->decks[index].n_cards++;
  fc->decks[index].cards=realloc(fc->decks[index].cards, fc->decks[index].n_cards*sizeof(void *));
  //}
  fc->decks[index].cards[fc->decks[index].n_cards-1]=ptr;
  return;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
// takes shuffled deck, and future cards. Search through future cards at index, draw a card, exchange card at pointer position with drawn card.
  card_t drawn;
for (int i=0; i<fc->n_decks; i++){
  if (i>deck->n_cards){
    fprintf(stderr,"no more cards in deck");
    return;
  }
  drawn=*deck->cards[i];
  for (int j=0; j<fc->decks[i].n_cards; j++){
    fc->decks[i].cards[j]->value=drawn.value;
    fc->decks[i].cards[j]->suit=drawn.suit;
    }
 }
 return;
}
