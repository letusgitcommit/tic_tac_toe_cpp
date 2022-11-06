#include "game_functions.h"

int main() {
  int winner;

  winner = game_loop();

  declare_winner(winner);

  return 0;
}


