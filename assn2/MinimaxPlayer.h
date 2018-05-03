/*
 * MinimaxPlayer.h
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */

#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "OthelloBoard.h"
#include "Player.h"
#include <vector>

//struct for keeping track of what move to make
struct Move{
	int col;
	int row;
};
/**
 * This class represents an AI player that uses the Minimax algorithm to play the game
 * intelligently.
 */
class MinimaxPlayer : public Player {
public:

	/**
	 * @param symb This is the symbol for the minimax player's pieces
	 */
	MinimaxPlayer(char symb);

	/**
	 * Destructor
	 */
	virtual ~MinimaxPlayer();

	/**
	 * @param b The board object for the current state of the board
	 * @param col Holds the return value for the column of the move
	 * @param row Holds the return value for the row of the move
	 */
    	void get_move(OthelloBoard* b, int& col, int& row);
	
	/**
	 * @param b The board object for the current state of the board
	 */
	int MaxValue(OthelloBoard b);
	
	/**
	 * @param b The board object for the current state of the board
	 */
	int MinValue(OthelloBoard b);
	
	/**
	 * @param player The character value for which player it is. Either X or O
	 * @param b The board object for the current state of the board
	 */
	std::vector<std::pair<Move, OthelloBoard>> GetSucc(char player, OthelloBoard b);
	
	/**
	 * @param b The board object for the current state of the board
	 */
	int GetUtility(OthelloBoard b);
	
	/**
	 * @param b The board object for the current state of the board
	 */
	bool IsTerminal(OthelloBoard b);

    /**
     * @return A copy of the MinimaxPlayer object
     * This is a virtual copy constructor
     */
    MinimaxPlayer* clone();

private:
};


#endif
