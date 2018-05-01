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
// function MINIMAX -DECISION(state) returns an action
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
// 		return v
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
