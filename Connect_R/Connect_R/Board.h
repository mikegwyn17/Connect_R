#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;

class Board
{

	private:
		vector< vector<char> > board;
		int number_of_rows;
		int number_of_columns;
		int r;

	public:
		// Defalut constructor
		Board ();
		~Board();
		// used to build the board based on the parameters passed in
		void Build_Board(const int rows,const int columns, const int win_condition);
		// reutrns a string representation of the board that can be printed
		string to_string () const;
		// method used to add a piece to the board by specifieng the column to drop it in
		void play (const int column, const char character, int& added_row, int& added_column);
		// method used to determine the value of the current board  using a heuristic
		bool check_board (const char player_piece, int added_column, int added_row) const;
};
#endif 