//#ifndef _BOARD_TREE_H_
//#define _BOARD_TREE_H_
//
//#include "Board_2.h"
//#include <stack>
//
//class Board_Tree
//{
//	private: 
//	struct board_node
//	{
//		double utiliity; // used to store the value found by the heuristic 
//		Board_2 board; // stores the current board linked to the board node
//		vector<board_node*> children; // vector to store the children of the board node
//		void add(board_node* n) {children.push_back(n);} // method used to add children to the board node
//		int size() {return children.size();} // return the number of children for the board node
//	};
//	board_node* root; // root node used to store the start of the board tree
//
//	public:
//
//		Board_Tree();
//		
//		~Board_Tree();
//		
//		// method called by the helper method to run the minimax algorithm
//		Board_2 minimax (board_node* current, const int depth, int current_depth, bool is_turn, int alpha, int beta);
//		// method used to create the board tree
//		Board_2 minimax(Board_2 board);
//	};
//	#endif 