#ifndef _CONNECT_R_AI_
#define _CONNECT_R_AI_
#include "Board_2.h"

using namespace std;

class Connect_R_AI
{
	private:
		Board_2* board;
		int max_depth;
		int move; // the location for the minimax to play
		int min_value;
		int max_value;

	public:
		Connect_R_AI ();
		Connect_R_AI (Board_2* b){board = b;}
		~Connect_R_AI();
		int Connect_R_AI::get_AI_move () const {return move;}
		double Minimax (int depth, bool is_turn, int alpha, int beta);

};
#endif 