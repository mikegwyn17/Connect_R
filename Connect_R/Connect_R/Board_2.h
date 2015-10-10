#ifndef _BOARD_2_H_
#define _BOARD_2_H_
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

class Board_2
{
	private:
		vector<char> board;
		int columns;
		int rows;
		int r;

	public:
		Board_2 ();
		~Board_2();
		void Build_Board(const int rows,const int columns, const int win_condition);
		string to_string () const;
		void play (const int column, const char character);
		//void check_board () const;
};
#endif 