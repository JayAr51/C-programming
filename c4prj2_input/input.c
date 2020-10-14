#include "cards.h"
#include "future.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include <string.h>
int is_card_valid(card_t);
deck_t * initDeck(void);
unsigned * get_match_counts(deck_t * hand);

void free_hands(hands_t * hS){
  //hS is a pointer to hands, which includes a pointer to an array of pointers, which point to the different hands.
  for (int i=0; i<hS->n_hands; i++){
    free_deck(hS->hands[i]);
  }
  free(hS->hands);
  free(hS);
  return;
}
void addHandToHands(hands_t * hS, deck_t * hand){
  //hS is a pointer to hands, which includes a pointer to an array of pointers, which point to the different hands.
  hS->n_hands++; //add number of hands and realloc space for the array of pointer 
  hS->hands=realloc(hS->hands, (hS->n_hands)*sizeof(hS->hands));
  hS->hands[hS->n_hands-1]=hand;
  return;
}


deck_t * handFromHandLetters(const char * handLetters, future_cards_t * fc){
  deck_t * hand=initDeck();
  //int space = 32;
  //char * cardPtr;
  card_t card;
  char value;
  char suit;
  size_t unknown_idx;
  //cardPtr=strchr(handLetters,space);
  while (strlen(handLetters)>1){
    value = handLetters[0];
    handLetters++;
    if (value=='?'){
    //suit could have values 9+
      char suitStr[3];
      int idx=0;
      while (handLetters[0]!=' ' && handLetters[0]!='\n' && handLetters[0]!='\0'){  
	suitStr[idx]=handLetters[0];
	idx++;
	handLetters++;
      }
      suitStr[idx]='\0';
      unknown_idx=atoi(suitStr);
      card=*add_empty_card(hand);
      add_future_card(fc, unknown_idx, hand->cards[hand->n_cards-1]);
    }
    else{
      suit = handLetters[0];   
      handLetters++;
      card=card_from_letters(value, suit);
      if (is_card_valid(card)==EXIT_SUCCESS){
	add_card_to(hand, card);
      }else{
	fprintf(stderr, "tried to add invalid card that did not start with ?\n");
      }
    }
    while (handLetters[0]==' '){
      handLetters++;
    }
  }
  if (hand->n_cards<5){
    fprintf(stderr, "less than 5 cards\n");
    return NULL;
  }
  return hand;
}

char * handLettersFromLine(char * line, size_t ex_hands ){
  int semicolon=(int) ';';
  char * input=line;
  for (int i=0; i<ex_hands; i++){
    input=strchr(input, semicolon);
    if (input==NULL){
      return NULL;
    }
    input++;
  }
  char * idxP=strchr(input, semicolon);
  char * hand=NULL;
  size_t idx;
  ssize_t len=strlen(line);
  if (idxP==NULL){
    idxP=strchr(line, (int) '\n');
  }
  if (idxP==NULL){
    idxP=strchr(line, (int) '\0');
  }
  if (idxP==NULL){
    idxP=input;
  }
    idx=idxP-input;
    hand=realloc(hand,(idx+1)*sizeof(char));
    hand=strncpy(hand,input,(idx));
    hand[idx]='\0';
    return hand;
}

int createHandsFromLine(hands_t * hS,  future_cards_t * fc, char *line){
  deck_t * hand;
  char * handLetters;
  char * idxP=NULL;
  int idx=0;
  //while (strlen(line)>0){
    handLetters=handLettersFromLine(line,0);// if multiple input lines hS->n_hands);
    //if (handLetters==NULL){
    //break;
    //}
    //if (strlen(handLetters)<2){
    //break;
    //} not neccessary for one line input
    hand = handFromHandLetters(handLetters, fc);
    free(handLetters);
    if (hand==NULL){
      return EXIT_FAILURE;
    }
    if (hand->n_cards>7||hand->n_cards<5){
      fprintf(stderr,"inappropriate number of %d cards in hand\n",hand->n_cards)
      return EXIT_FAILURE;
    }
    addHandToHands(hS, hand);
    //}
  return EXIT_SUCCESS;    
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  int success=EXIT_SUCCESS;
  ssize_t len=0;
  size_t sz=0;
  char * line=NULL;
  hands_t * hS=calloc(1, sizeof(hands_t));
  hS->hands=malloc(sizeof(void *));
  hS->n_hands=0;
  while (len=getline(&line, &sz, f)>0){
    success=createHandsFromLine(hS, fc, line);
	// for multi input lines it should be put here
    if (success==EXIT_FAILURE){
      return NULL;
    }
//deck_t * deck = build_remaining_deck(hands->hands, hands-> n_hands);
  }
  // for single input lines it should be place here
  //deck_t * deck = build_remaining_deck(hS->hands, hS->n_hands);
  free(line);
  *n_hands=hS->n_hands;
  deck_t ** hands=hS->hands;
  free(hS);
  return hands;
}
