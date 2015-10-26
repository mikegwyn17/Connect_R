//#include "Board_Tree.h"
//
//using namespace std;
//
//Board_Tree::Board_Tree ()
//{
//	root = new board_node();
//}
//
//// main method used to call the minimax algorithm that decides what move the AI should take
//Board_2 Board_Tree::minimax(Board_2 board)
//{
//	bool is_turn = true;
//	board_node* current = root;
//	current->board = board;
//	int depth = 6;
//	int current_depth = 0;
//	int alpha = numeric_limits<double>::max();
//	int beta = numeric_limits<double>::min();
//	return minimax(current,depth, current_depth, is_turn, alpha, beta); 
//}
//
////Board_2 Board_Tree::minimax(board_node* current, const int depth, int current_depth, bool is_turn, int alpha, int beta)
////{
////	if (beta <= alpha && is_turn)
////	{
////		
////	}
////
////}