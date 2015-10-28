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
	cout << game_state.to_string() << endl;

	ai->play(game_state, 3, false);
	cout << ai->minimax(game_state) << endl;


	std::cout << "Press ENTER to continue...";
  	std::cin.ignore( numeric_limits<streamsize>::max(), '\n' );
	return 1;
};