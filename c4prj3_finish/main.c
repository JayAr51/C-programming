#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void free_deck(deck_t * deck);
int is_card_valid(card_t);
deck_t * initDeck(void);
unsigned * get_match_counts(deck_t * hand);
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc);


void printDeck(deck_t * deck){
  for (int i=0; i<deck->n_cards; i++){
    print_card(*deck->cards[i]);
    printf("%c",' ');
  }
  printf("%s","\n");
  return;
}

void free_future_cards(future_cards_t * fc){
  for (int i=fc->n_decks-1; i>=0; i--){
    if (fc->decks[i].n_cards>0){
      free(fc->decks[i].cards);
    }
    // free(fc->decks[i]);
  }
  free(fc->decks);
  free(fc);
  return;
}

future_cards_t * initFutureCards(void){
  future_cards_t * fc=malloc(sizeof(*fc));
  fc->decks=initDeck();
  fc->n_decks=0;
  return fc;
}

void update_count_wins(unsigned * count_wins,deck_t ** hands, size_t n){
  int strongest_idx=0;
  int tie=0;
  for (int j=1; j<n; j++){
    if (compare_hands(hands[strongest_idx],hands[j])<0){
      strongest_idx=j;
      tie=0;
    }
    else if (compare_hands(hands[strongest_idx],hands[j])==0){
      tie=1;
    }
  }
  if (tie){
    count_wins[n]++;
  }else{
    count_wins[strongest_idx]++;
  }
}

void print_results(unsigned *count_wins, size_t n, unsigned num_sim){
  float ratio;
  for (size_t wins=0; wins<n; wins++){
    ratio=((float)count_wins[wins])/((float)num_sim)*100;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", wins, count_wins[wins], num_sim, ratio);
  }
  printf("And there were %u ties\n",count_wins[n]);
  return;
}

int main(int args,char ** argv) {
  if (args<2 || args>3){
    fprintf(stderr, "useage ./a input e.g. (input.txt) number_of_simulaters e.g (20000, optional) \n");
    return EXIT_FAILURE;
  }
  unsigned num_sim;
  if (args==3){
    num_sim = atoi(argv[2]);
  }else{
    num_sim = 10000;
  }
  FILE * f=fopen(argv[1],"r");
  size_t * n_hands=malloc(sizeof(size_t));
  *n_hands=0;
  future_cards_t * fc=initFutureCards();
  deck_t ** hands=read_input(f, n_hands, fc);
  if (hands==NULL){
    return EXIT_FAILURE;
  }
  //Create an array to count how many times each hand wins, with one more element for if there was a tie
  unsigned * count_wins=calloc(*n_hands+1,sizeof(unsigned));
  //remaining deck only needs to be built once
  deck_t * deck = build_remaining_deck(hands, *n_hands);
  for (int i=0; i<num_sim; i++){
    shuffle(deck); 
    future_cards_from_deck(deck, fc);
    // compare hands and count who won
    update_count_wins(count_wins, hands, *n_hands);
    //size_t wins=get_largest_element(count_wins, *n_hands);
  }
  print_results(count_wins, *n_hands, num_sim);
  free(count_wins);
  free_deck(deck);
  for (int k=0; k<*n_hands; k++){
    free_deck(hands[k]);
  }
  free(hands);
  free(n_hands);
  free_future_cards(fc);
  if (fclose(f)!=0){
    fprintf(stderr,"could not close file %s\n",argv[1]);
  }
return EXIT_SUCCESS;
}
