#include "Board_Tree.h"

using namespace std;

Board_Tree::Board_Tree ()
{
	root = new board_node();
}

void Board_Tree::build(Board_2 board)
{
	board_node* current = new board_node();
	current = root;  
	current->board = board;
	for (int i = 0; i < board.get_columns(); i++)
	{
		current->board.set_board(board.play(i,'x'));
		root->add(current);
		current = new board_node();
	}
	cout << "stuff" << endl;
}