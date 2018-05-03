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
// function MINIMAX-DECISION(state) returns an action
// 	inputs: state, current state in game
// 	v← MAX-VALUE(state)
// 	return the action in SUCCESSORS(state) with value v
// 
// function MAX-VALUE(state) returns a utility value
// 	if TERMINAL-TEST(state) then return UTILITY(state)
// 	v← -Infinity
// 	for a, s in SUCCESSORS(state) do 
// 		v← MAX(v, MIN-VALUE(s))
// 	return v
// 
// function MIN-VALUE(state) returns a utility value
// 	if TERMINAL-TEST(state) then return UTILITY(state)v ← Infinity
// 	for a, sin SUCCESSORS(state) do
// 		v← MIN(v, MAX-VALUE(s))
// 	return v
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    struct Move m;
		int utility;
		signed int min = 99999;
		signed int max = -99999;
		
		vector<std::pair<Move, OthelloBoard>> successors = GetSucc(symbol, *b);
		vector<std::pair<Move, OthelloBoard>>::iterator it;
		
		for (it = successors.begin(); it != successors.end(); it++){
			if (symbol == b->get_p1_symbol()){
				utility = MinValue(it->second);
				if(utility >= max){
					max = utility;
					m = it->first;
				}
			}else{
				utility = MaxValue(it->second);
				if(utility < min){
					min = utility;
					m = it->first;
				}
			}
		}
			
		row = m.row;
		col = m.col;
}

int MinimaxPlayer::MaxValue(OthelloBoard b){
	int utility = -99999;
	int posibilities;
	
	if (IsTerminal(b)) return GetUtility(b);
	
	vector<std::pair<Move, OthelloBoard>> successors = GetSucc(b.get_p1_symbol(), b);
	vector<std::pair<Move, OthelloBoard>>::iterator it;
	
	for (it = successors.begin(); it != successors.end(); it++){
		posibilities = MinValue(it->second);
		if(utility < posibilities){
			utility = posibilities;
		}
	}
	if (successors.empty()){
		utility = MinValue(b);
	}
	return utility;
}

int MinimaxPlayer::MinValue(OthelloBoard b){
	int utility = 99999;
	int posibilities;
	
	if (IsTerminal(b)) return GetUtility(b);
	
	vector<std::pair<Move, OthelloBoard>> successors = GetSucc(b.get_p2_symbol(), b);
	vector<std::pair<Move, OthelloBoard>>::iterator it;
	
	for (it = successors.begin(); it != successors.end(); it++){
		posibilities = MaxValue(it->second);
		if(utility < posibilities){
			utility = posibilities;
		}
	}
	if (successors.empty()){
		utility = MaxValue(b);
	}
	return utility;
}
int MinimaxPlayer::GetUtility(OthelloBoard b){
	return b.count_score(b.get_p1_symbol()) - b.count_score(b.get_p2_symbol());
}

vector<std::pair<Move, OthelloBoard>> GetSucc(char player, OthelloBoard b){
	vector<std::pair<Move, OthelloBoard>> board;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (b.is_legal_move(i, j, player)){
				OthelloBoard newB = b;
				Move m; 
				m.row = i;
				m.col = j;
				newB.play_move(i, j, player);
				board.push_back(std::pair<Move, OthelloBoard>(m, newB));
			}
		}
	}
	return board;
}
bool IsTerminal(OthelloBoard b){
	return b.has_legal_moves_remaining(b.get_p1_symbol()) || b.has_legal_moves_remaining(b.get_p2_symbol());
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
