#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
int deck_contains(deck_t * d, card_t c);

unsigned * get_match_counts(deck_t * hand){
  unsigned * match_counts=calloc(hand->n_cards, sizeof(match_counts));
  // match_counts 1 1 2 2 3 3 3 for 0 9 7 7 6 6 6  and match_idx = 4 . The new match can only begin twhere the last match ended.
  for (int i; i<hand->n_cards; i++){
    match_counts[i]=deck_contains(hand,*hand->cards[i]);
  }
  return match_counts;
}

card_t card_from_letters(char value_let, char suit_let);

void printhand(deck_t *hand){
  for (int i=0;i<hand->n_cards;i++){
    print_card(*hand->cards[i]);
    printf(" ");
  }
  printf("\n");
}

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * val1ptr =vp1; // convert back to int* so we can dereference
  const card_t * const * val2ptr =vp2;
  int value_diff= (**val2ptr).value - (**val1ptr).value;   // subtracting the two numbers compares them
  if (value_diff==0){
    suit_t suit1=(**val1ptr).suit;
    suit_t suit2=(**val2ptr).suit;
    return suit2 - suit1;
  }else{
    return value_diff;
  }
}


suit_t flush_suit(deck_t * hand) {
  for (suit_t suit=0;suit < NUM_SUITS;suit++){ 
   int n_suits=0;
   for (int idx=0;idx<hand->n_cards;idx++){
     if (hand->cards[idx]->suit==suit){//is unequal ->reset counter
       n_suits++;
       if (n_suits==5){
	 return suit;
       }
     }
   }
 }
 return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max=arr[0];
  for (int i=1; i<n; i++){
    if (arr[i]>max){
      max=arr[i];
    }
  }   
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i=0;i<n;i++){
    if (match_counts[i]==n_of_akind){
      return i;
    }
    assert(i<=n);
  }
  return -1;
}

size_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  // match_counts 1 1 2 2 3 3 3 for 0 9 7 7 6 6 6  and match_idx = 4 . The new match can only begin twhere the last match ended.
  int i=0;
  while (i<hand->n_cards){
    if (i==match_idx){
      i+=match_counts[i];
    }
    else{
      if (match_counts[i]>=2){
	return i;
      }
      i++;
    }
  }
  return -1;
}
int init_n_vals(suit_t suit, suit_t fs){
  if (fs==NUM_SUITS||fs==suit){
    return 1;
  }
  else{
    return 0;
  }
}

int is_n_length_straight_at(deck_t * hand, size_t index, int n, suit_t fs){
  //es muss abgefragt werden ob dieser Eintrag den Wert 5 hat
  int n_vals=init_n_vals(hand->cards[index]->suit, fs);
  if (n_vals==0){return 0;}
  unsigned lastvalue=hand->cards[index]->value;
  for (int idx=index+1;idx<hand->n_cards;idx++){
    if (hand->cards[idx]->value<lastvalue-1){//Descendent sorting If next value is less or equal, do 
      n_vals=init_n_vals(hand->cards[index]->suit, fs);
	//startidx=idx;
      return 0;
    }
    else if (hand->cards[idx]->value==lastvalue-1)// there is still a chance...
    {
      if (fs==NUM_SUITS){//regular straight
	  n_vals++;
	  lastvalue--;
      }
      else{
	  if (hand->cards[idx]->suit==fs){
	    n_vals++;
	    lastvalue--;
	  }
      }
    }
  if (n_vals==n){
    return 1;
  }
  
  }
  return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int isStraight=0;
  // first check for straight
  isStraight=is_n_length_straight_at(hand, index, 5, fs);
    if (isStraight==1){
      return 1;
    }
  for (int i=1;i<=hand->n_cards-4;i++){
    isStraight=is_n_length_straight_at(hand, index+i, 4, fs);
    if (isStraight==1){//If there is a lenght 4 straight an ACE_LOW_STRAIGHt is possible
      if (hand->cards[index+i]->value==5){//if straight starts with 5
	if (fs!=NUM_SUITS){// check for straight flush with desired card
	  //char suit_l=suit_letter(*hand->cards[index]);
	  //card_t desCard=card_from_letters('A', suit_l);
	  if(hand->cards[index]->value==VALUE_ACE && hand->cards[index]->suit==fs){
	    return -1;
	  }
	}
	else{// Only need to check if first card is an ace
	  if (hand->cards[index]->value==VALUE_ACE){
	    return -1;
	  }
	}
      }
    }
  }
  return 0;
}


hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  ans.ranking=what;
  for (int i=0;i<n;i++){
    ans.cards[i]=hand->cards[i+idx];
  }//Hand now hold n Values 0 - n-1
  //will not be called for flush
  //will not be called for straight
  /*switch (what){
  case  FOUR_OF_A_KIND: //important
    if (idx>0){
      ans.cards[4]=hand->cards[0];
    }else{
      ans.cards[4]=hand->cards[n];
    }
      break;
  case  THREE_OF_A_KIND: //important
  */
  if (what==FOUR_OF_A_KIND || what==THREE_OF_A_KIND || what==PAIR || what==NOTHING){
  size_t search_idx=0;
    for(int ii=n;ii<5;ii++){
      if (search_idx==idx){
	search_idx+=n;
      }
      ans.cards[ii]=hand->cards[search_idx];
      search_idx++;
    }
  }
    /*if (idx>0){
      ans.cards[3]=hand->cards[0];
    }else{
      ans.cards[3]=hand->cards[n];
    }
    if (idx>1){
      ans.cards[4]=hand->cards[1];
    }else{
      ans.cards[4]=hand->cards[idx+n+1];
    }
    break;
  case  TWO_PAIR: //no action required
    break;
  case  PAIR: 
    if (idx>0){
      ans.cards[2]=hand->cards[0];
    }else{
      ans.cards[2]=hand->cards[n];
    }
    if (idx>1){
      ans.cards[3]=hand->cards[1];
    }else{
      ans.cards[3]=hand->cards[idx+n+1];
    }
    if (idx>2){
      ans.cards[4]=hand->cards[2];
    }else{
      ans.cards[4]=hand->cards[idx+n+2];
    }
    break;/
  case  NOTHING:
    for (int i=0;i<5;i++){
      ans.cards[i]=hand->cards[i];
    }
    break;
  default:
   break;
  }*/
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards,hand1->n_cards,sizeof(hand1->cards[0]),card_ptr_comp);
  qsort(hand2->cards,hand2->n_cards,sizeof(hand2->cards[0]),card_ptr_comp);
  //printhand(hand1);
  hand_eval_t eval1=evaluate_hand(hand1);
  hand_eval_t eval2=evaluate_hand(hand2);
  if (eval1.ranking==eval2.ranking){
  unsigned val1;
  unsigned val2;
  for (int i=0;i<5;i++){
    val1=eval1.cards[i]->value;
    val2=eval2.cards[i]->value;
    if (val1!=val2){
      return val1-val2;
    }
  }
  //unsigned highcard1=get_largest_element(values1, 5);
  //unsigned highcard2=get_largest_element(values2, 5);
  // return highcard1-highcard2;
  return 0;
  }
  else{
    return eval2.ranking-eval1.ranking;
  }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {//pair
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
