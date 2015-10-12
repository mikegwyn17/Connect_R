#ifndef _Board_TREE_H_
#define _BOARD_TREE_H_

#include "Board_2.h"

class Board_Tree
{
	private: 
	struct board_node
	{
		double utiliity; // used to store the value found by the heuristic 
		Board_2 board;
		vector<board_node*> children;
		void add(board_node* n) {children.push_back(n);}
		int size() {return children.size();}
	};
	board_node* root;

	public:

		Board_Tree();
		
		~Board_Tree();

		// parse method
		void build(Board_2 board);
	};
	#endif 