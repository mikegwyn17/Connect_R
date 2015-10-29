#include "AI.h"
#include <string>
#include <vector>
#include <set>
#include <limits>
#include <iostream>


// simple method used to make reading in int values from user easier
int read_int_m ()
{
	string input = "";
	getline(std::cin, input);
	int value = atoi(input.c_str());
	return value;
}

AI::state_space play_ai (AI* ai, AI::state_space& game_state)
{
	int ai_move = ai->minimax(game_state);
	try { 
		game_state = ai->play(game_state, ai_move, true); }
	catch (runtime_error&) { cout << "not a valid move" << endl; }
	cout << "AI played in " << ai_move << endl;
	cout << game_state.to_string() << endl;
	return game_state;
}

AI::state_space play_user (AI* ai, AI::state_space& game_state)
{
	cout << "choose column to play in " << endl;
	int user_move = read_int_m();
	game_state = ai->play(game_state, user_move, false);
	cout << game_state.to_string() << endl;
	return game_state;
}

int main (void)
{
	bool cont = true;
	unsigned count = 0;
	int player_move = 0;
	int number_of_columns = 0;
	int number_of_rows = 0;
	int r = 0;
	int added_row = 0;
	int added_column = 0;
	string input;

	// create the starting board
	vector<char> starting_board;

	std::cout << "Enter number of columns ";
	number_of_columns = read_int_m();
	std::cout << endl;

	std::cout << "Enter the number of rows ";
	number_of_rows = read_int_m();
	std::cout << endl;

	std::cout << "Enter the number required to win ";
	r = read_int_m();
	std::cout << endl;

	starting_board.resize((number_of_columns*number_of_rows), '-');
	AI::state_space game_state = AI::state_space(starting_board, r, number_of_columns, number_of_rows);
	AI* ai = new AI();
	//cout << game_state.to_string() << endl;

	cout << game_state.to_string() << endl;
	int game_value = ai->is_game_over(game_state);
	while (game_value == 0)
	{
		game_state = play_user(ai, game_state);
		game_state = play_ai(ai, game_state);
		game_value = ai->is_game_over(game_state);
	}
	if (game_value == 1)
		cout << "I won" << endl;\
	else if (game_value = -1)
		cout << "you won" << endl;
	else
	{
		cout << "Draw" << endl;
	}

	// because using System("pause") is apparently an awful thing
	std::cout << "Press ENTER to continue...";
  	std::cin.ignore( numeric_limits<streamsize>::max(), '\n' );
	return 1;
};