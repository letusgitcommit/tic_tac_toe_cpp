#include <iostream>
#include <string>
#include <vector>

void overwrite_input(int number_of_lines);

void display_board(std::vector <std::vector <int>> game_state);

void display_opening();

bool validate_col_or_row(std::string input);

bool validate_empty_square(std::vector <std::vector <int>> game_state, int row, int column);

bool check_check_vector(std::vector <int> check_vector);

bool check_win_con(std::vector <std::vector <int>> game_state);

std::string get_player_input(int player_number, std::string col_or_row);

std::vector <std::vector <int>> player_turn(std::vector <std::vector <int>> game_state, int player_number);

int game_loop();

void declare_winner(int player_num);

