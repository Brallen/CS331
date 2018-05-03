/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}
/* THIS FUNCTION IS BASICALLY MINIMAX_DECISION */
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
	struct Move m; // move that will be played
	int utility; // value for the best move
	signed int min = 99999; // this is large so will get erased
	signed int max = -99999; // this is small so will get erased
	
	//get all the successors for the first move and then set up the iterator for them
	vector<std::pair<Move, OthelloBoard>> successors = GetSucc(symbol, *b);
	vector<std::pair<Move, OthelloBoard>>::iterator it;
	
	// loop through all of the successors to find the best move to make
	for (it = successors.begin(); it != successors.end(); it++){
		if (symbol == b->get_p1_symbol()){ //if player 1 we want the max of the min value
			utility = MinValue(it->second); //get the min
			if(utility >= max){ //see if its the new max of the mins
				//if it is then replace the old one and set that to be the move
			   	max = utility;
				m = it->first;
			}
		}else{ // if player 2 we want the min of the max value
			utility = MaxValue(it->second); //get the max
			if(utility < min){ //see if its the new min of the maxs
			   	//if it is then replace the old one and set it to be the move
				min = utility;
				m = it->first;
			}
		}
	}

	row = m.row; //make move for row
	col = m.col; //make move for col
}

int MinimaxPlayer::MaxValue(OthelloBoard b){
   	int utility = -99999; //set the utility value to be small to be erased
	int posibilities; //the possible value for the utility value
	//much like above get the successors and set up an iterator
	vector<std::pair<Move, OthelloBoard>> successors = GetSucc(b.get_p1_symbol(), b);
	vector<std::pair<Move, OthelloBoard>>::iterator it;
	
	if (IsTerminal(b)) return GetUtility(b); //if its a leaf node for moves return its value
	//if no successors then give the utility of the current board
	if (successors.empty()) utility = MinValue(b);

	//if there are successors loop through them and see if they have successors
	for (it = successors.begin(); it != successors.end(); it++){
		posibilities = MinValue(it->second); //get the value for its successors
		if(utility < posibilities) utility = posibilities; //replace utility if larger
	}

	return utility;
}

int MinimaxPlayer::MinValue(OthelloBoard b){
	int utility = 99999; //set to be really large to be erased
	int posibilities; //the possible value for the utility value

	//again set up the successors and get an iterator to loop over them
	vector<std::pair<Move, OthelloBoard>> successors = GetSucc(b.get_p2_symbol(), b);
	vector<std::pair<Move, OthelloBoard>>::iterator it;
	
	if (IsTerminal(b)) return GetUtility(b);//if a leaf node return value
	if (successors.empty())	utility = MaxValue(b); //if no successors give utility of current board

	//if there are successors loop through them and get their successors
	for (it = successors.begin(); it != successors.end(); it++){
		posibilities = MaxValue(it->second); //get the value for those successors
		if(utility >= posibilities) utility = posibilities; //replace utility if smaller
	}
	return utility;
}
int MinimaxPlayer::GetUtility(OthelloBoard b){
   	//return the difference between the scores
	// positive means better for p1 negative means better for p2
	return b.count_score(b.get_p1_symbol()) - b.count_score(b.get_p2_symbol());
}

vector<std::pair<Move, OthelloBoard>> MinimaxPlayer::GetSucc(char player, OthelloBoard b){
	vector<std::pair<Move, OthelloBoard>> board; //all possible successors
	//exhaustive search all of the moves for possible locations
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (b.is_legal_move(i, j, player)){ //make sure the move can be played
			   	//if it can then create a new successor board
				OthelloBoard newB = b; 
				//create a struct to remember the move
				Move m;
			        m.col = i;
				m.row = j;
				//play the move and add it to the back of all possible moves	
				newB.play_move(i, j, player);
				board.push_back(std::pair<Move, OthelloBoard>(m, newB));
			}
		}
	}
	return board; //give all possible successors
}
bool MinimaxPlayer::IsTerminal(OthelloBoard b){
   	//looks to see if either player has moves remaining
	//returns true if there are no other moves that could be made
	return !(b.has_legal_moves_remaining(b.get_p1_symbol()) || b.has_legal_moves_remaining(b.get_p2_symbol()));
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
