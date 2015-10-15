#ifndef _BOARD_2_H_
#define _BOARD_2_H_
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <limits>

using namespace std;

class Board_2
{
	private:
		vector<char> board; // board state is represented as a vector of chars
		int columns;
		int rows;
		int r;
		set<int> used_columns;
		set<int> used_rows;

	public:
		Board_2 ();
		~Board_2();
		int get_columns ();
		int get_rows ();
		int get_r ();
		void set_board (const vector<char> passed_board);
		void Build_Board(const int rows,const int columns, const int win_condition);
		string to_string () const;
		vector<char> play (const int column, const char character);
		double check_board (const bool is_turn, const char player_piece) const;
};
#endif 