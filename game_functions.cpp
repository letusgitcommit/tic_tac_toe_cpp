#include <iostream>
#include <string>
#include <vector>


void overwrite_input(int number_of_lines) {
  for (int i = 0; i < number_of_lines; i++) {
    std::cout << "\033[2K";
    std::cout << "\033[1A";
  }
}


void display_board(std::vector<std::vector <int>> game_state) {
  //state should be a two-dimensional 3x3 vector
  std::cout << "      1   2   3 \n";
  std::cout << "      -   -   - \n";
  for (int i = 0; i < game_state.size(); i++) {
    std::cout << "  " << i + 1 << " | ";
    for (int j = 0; j < game_state[i].size(); j++) {
      std::cout << game_state[i][j] << " | ";
    }
    std::cout << "\n      -   -   - \n";
  }
  std::cout << "\n\n";

}


void display_opening() {
  overwrite_input(1000);
  std::cout << "\n";
  std::cout << "Welcome to my tic tac toe game!\n";
  std::cout << "Let's get started!\n\n";

  std::cout << "Player 1 will be represented as a '1' and Player 2 will be represented as a '2'. Unfilled squares will be represented with a '0'\n\n";
}


bool validate_col_or_row(std::string input) {
  if (input == "1" || input == "2" || input == "3") {
    return true;
  }
  else {
    //clears the wrong input line.
    std::cout << "\033[1A" << "\033[2K";
    return false;
  }
}


bool validate_empty_square(std::vector <std::vector <int>> game_state, int row, int column) {
  if (game_state[row][column] == 0) {
    return true;
  }
  else {
    return false;
  }
}

bool check_check_vector(std::vector <int> check_vector) {
  //we only check the first three elements
  if (check_vector[0] != 0 && check_vector[0] == check_vector[1] && check_vector[1] == check_vector[2]) {
    return true;
  }
  else {
    return false;
  }
}

bool check_win_con(std::vector <std::vector <int>> game_state) {
  std::vector<int> vert = {0, 0, 0};
  std::vector<int> hori = {0, 0, 0};
  std::vector<int> diag1 = {0, 0, 0};
  std::vector<int> diag2 = {0, 0, 0};

  for (int i = 0; i < 3; i++) {
    diag1[i] = game_state[i][i];
    diag2[i] = game_state[2-i][i];

    for (int j = 0; j < 3; j++) {
      hori[j] = game_state[i][j];
      vert[j] = game_state[j][i];
    }
    if (check_check_vector(hori)) {
      return true;
    }
    if (check_check_vector(vert)) {
      return true;
    }
  }

  if (check_check_vector(diag1)) {
    return true;
  }
  if (check_check_vector(diag2)) {
    return true;
  }

  return false;
}


std::string get_player_input(int player_number, std::string col_or_row) {
  std::string input = "";
  while(!validate_col_or_row(input)) {
    std::cout << "Player " << player_number << ", please input the " << col_or_row << " you would like to mark, 1, 2, or 3: ";
    std::getline(std::cin, input);
  }
  return input;
}


std::vector <std::vector <int>> player_turn(std::vector<std::vector <int>> game_state, int player_number) {

  std::string column = "";
  std::string row = "";


  column = get_player_input(player_number, "column");

  row = get_player_input(player_number, "row");

  int column_idx = stoi(column) - 1;
  int row_idx = stoi(row) - 1;

  if (!validate_empty_square(game_state, row_idx, column_idx)) {
    std::cout << "Sorry, that square is not empty.\n\n";
    return player_turn(game_state, player_number);
  }

  game_state[row_idx][column_idx] = player_number;

  return game_state;

}


int game_loop() {
  std::vector<std::vector <int>> state = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  for (int i = 0; i < 9; i++) {
    display_opening();
    display_board(state);
    state = player_turn(state, i % 2 + 1);
    if (check_win_con(state)) {
      overwrite_input(100);
      std::cout << "\n\n\n\n\n";
      display_board(state);
      return i % 2 + 1;
    }
    overwrite_input(100);
  }
  std::cout << "\n\n\n\n\n";
  display_board(state);
  return 0;
}

void declare_winner(int player_num) {
  std::cout << "\n\n\n\n\n";
  if (player_num == 0) {
    std::cout << "The game ended in a tie!\n";
  }
  else {
    std::cout << "Player " << player_num << " has claimed victory!\n";
  }
}
