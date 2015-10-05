#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>

class Board
{
	private:
		char[][] board;

	public:
		Board ();
		~Board();
		Board(const int x, const int y);
}
#endif 