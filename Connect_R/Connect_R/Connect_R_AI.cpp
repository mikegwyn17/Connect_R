#include "Connect_R_AI.h"

Connect_R_AI::Connect_R_AI()
{
	max_depth = 9;
	move = -1; 
	min_value = numeric_limits<int>::min();
	max_value = numeric_limits<int>::max();
}

Connect_R_AI::~Connect_R_AI()
{
	// TODO implement destrcutor
	cout << "destructor" << endl;
}

double Connect_R_AI::Minimax (int depth, bool is_turn, int alpha, int beta)
{
	int max_score = max_value;
	int min_score = min_value;
	if (depth == max_depth)
		return board->check_board(is_turn, 'x');
	for (int i = 0; i < board->get_columns(); i++)
	{
		int current_score = 0;
		if (!(board->play(i,'x'))) // don't enumerat the unplayable board states
			continue;

		if (is_turn)
		{
			board->play(i,'x');
			current_score = Minimax(depth+1, false, alpha, beta);

			if (depth == 0 && current_score > max_score)
				move = i;
			else if (depth == 0 && current_score == max_value)
				break; // winning move was found
			
			max_score = max(current_score, max_score);
			alpha = max(current_score, alpha);
		}
		else
		{
			board->play(i,'o');
			current_score = Minimax(depth+1, true, alpha, beta);

			min_score = min(current_score, min_score);
			beta = min(current_score, beta);
			is_turn = true;
		}
		if (current_score == min_value || current_score == max_value)
			break;
	}

	if (is_turn)
		return max_score;
	else
		return min_score;
}