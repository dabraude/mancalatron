/**********************************************************************
Represents the board to std::cout
Takes the board array as input
***********************************************************************/
void print_board(std::vector<int> board) {

  std::cout << "\n\n\n\t("
    << board[13] << ")\t("
    << board[12] << ")\t("
    << board[11] << ")\t("
    << board[10] << ")\t("
    << board[9] << ")\t("
    << board[8] << ")\t"
    << "\n (" << board[0] << ")\t\t\t\t\t\t\t(" << board[7] << ")\n\t("
    << board[1] << ")\t("
    << board[2] << ")\t("
    << board[3] << ")\t("
    << board[4] << ")\t("
    << board[5] << ")\t("
    << board[6] << ")\t";

  // Well numbering for the user
  std::cout << "\n\n\t 1\t 2\t 3\t 4\t 5\t 6";

    //return(0);
}



int check_for_finish(std::vector<int> board) {

    int total = 0;        // Counts the stones in player_zero's wells

    // Add up player_zero's stones
    for (int i = 1; i < 7; ++i) {
      total += board[i];
    }

    // If there are no stones in the player's wells, add the rest to opponent's mancala.
    if (total == 0) {

      for (int i = 8; i < 14; ++i) {
        board[0] += board[i];
        board[i] = 0;
      }

      print_board(board);

      std::cout << "\n\nGAME OVER!\n";

      return (1);   // Signal that the game is over

    }
``

  return (0);   // Signal that the game is not over
}




/**********************************************************************
This handles board updating (from player_zero perspective only).
The player 'picks' up the stones in well, then redistributes them.
Opponent's mancala is skipped.
***********************************************************************/
std::vector<int> do_human_move(std::vector<int> board) {

  int well;     // Well selected by player

  std::cout << "\n\n\n";
  std::cout << "Enter well selection: ";
  std::cin >> well;

  // Test for valid well choice, then update board
  if ((well >= 1) && (well <= 6) && board[well] > 0) {

    // // Add this move to the move history
    // history.push_back(well);
    //
    // // Print the move history for diagnosis
    // std::cout << "\n\nHistory: ";
    // for(int i = 0; i < history.size(); ++i) {
    //   std::cout << history[i] << ", ";
    // }
    // std::cout << "\n";

    // Make the desired move
    int stones_to_distribute = board[well];     // Stones 'picked up' by the user
    int current_well;     // The well into which user 'drops' a stone

    board[well] = 0;

    current_well = well;

    // Redistribute stones
    while (stones_to_distribute > 0) {
      ++current_well;
      if (current_well == 14) current_well = 0;

      // Ensure opponent's mancala is skipped
      if (current_well != 0) {
        ++board[current_well];
        --stones_to_distribute;
      }
    }


    // This needlessly repetitive block deals with capture. Landing in an empty well is understood as the current_well containing 1 stone.
    // A better programmer would put this into a swtich statement. If you find a better programmer, let me know.

    if ((current_well == 1) && (board[current_well] == 1) && (board[13] != 0)) {
      board[1] = 0;
      board[7] = board[7] + board[13] + 1;
      board[13] = 0;
    }

    if ((current_well == 2) && (board[current_well] == 1) && (board[12] != 0)) {
      board[2] = 0;
      board[7] = board[7] + board[12] + 1;
      board[12] = 0;
    }

    if ((current_well == 3) && (board[current_well] == 1) && (board[11] != 0)) {
      board[3] = 0;
      board[7] = board[7] + board[11] + 1;
      board[11] = 0;
    }

    if ((current_well == 4) && (board[current_well] == 1) && (board[10] != 0)) {
      board[4] = 0;
      board[7] = board[7] + board[10] + 1;
      board[10] = 0;
    }


    if ((current_well == 5) && (board[current_well] == 1) && (board[9] != 0)) {
      board[5] = 0;
      board[7] = board[7] + board[9] + 1;
      board[9] = 0;
    }

    if ((current_well == 6) && (board[current_well] == 1) && (board[8] != 0)) {
      board[6] = 0;
      board[7] = board[7] + board[8] + 1;
      board[8] = 0;
    }

    if (current_well == 7) {
      std::cout << "DOUBLE MOVE";
    }

    // Decide if the game is finished
    //if (check_for_finish(board)) playing = false;


  } else {
    std::cout << "\nInvalid well choice. Ignoring.\n"
  }




  return(board);

}




// Flips the board around so the same update_board function can be used whoever is playing.
std::vector<int> flip_board(std::vector<int> board) {
  std::vector<int> new_board = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // Temporary empty board

  // Fill with old board's stones, with index rotated
  for (int i = 0; i < 14; ++i) {
    new_board[i] = board[(i + 7) % 14];
  }

  return(new_board);
}
