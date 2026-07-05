#include "game.hpp"
#include <bitset>
#include <iostream>
#include <ostream>

int Game::GetUserInput() {
  int user_input;
  bool valid_answer = false;
  std::string menu = "Select Mode: \n"
                     "1. Shift Left\n"
                     "2. Shift Right\n"
                     "3. AND Shift (0 - 255)\n"
                     "4. OR Shift (0 - 255)\n"
                     "5. Random mode (Not Implamented)\n"
                     "6. Quit";

  do {
    std::cout << menu << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> user_input;

    if (user_input < 1 || user_input > 6) {
      continue;
    }

    valid_answer = true;
  } while (!valid_answer);

  return user_input;
}

void Game::GetShiftValues(int init_value, int shift_value) {
  std::cout << "Enter the initial value (integer): ";
  std::cin >> init_value;
  SetInitValue(init_value);

  std::cout << "Enter the number of bits to shift (integer): ";
  std::cin >> shift_value;
  SetShiftValue(shift_value);
}

bool Game::CheckGuess(int guess, int shifted_value) {
  return guess == shifted_value;
}

void Game::Start(Game game) {
  bool is_playing = true;

  std::cout << "Welcome to the Bit Shift Game!\n";
  std::cout << "Round: " << game.GetRoundNumber() << "\n";
  std::cout << game.ToString() << std::endl;

  do {
    switch (GetUserInput()) {
    case 1:
      GetShiftValues(game.GetInitValue(), game.GetShiftValue());
      game.SetShiftedValue(game.GetInitValue() << game.GetShiftValue());

      game.PlayField(game.GetShiftedValue(), game);
      break;
    case 2:
      GetShiftValues(game.GetInitValue(), game.GetShiftValue());
      game.SetShiftedValue(game.GetInitValue() >> game.GetShiftValue());

      game.PlayField(game.GetShiftedValue(), game);
      break;
    case 3:
      GetShiftValues(game.GetInitValue(), game.GetShiftValue());

      if ((game.GetInitValue() < 0 || game.GetInitValue() > 255) &&
          (game.GetShiftValue() < 0 || game.GetShiftValue() > 255)) {
        GetShiftValues(game.GetInitValue(), game.GetShiftValue());
      }

      game.SetShiftedValue(game.GetInitValue() & game.GetShiftValue());
      DisplayBitValue(game.GetInitValue(), game.GetShiftValue());

      game.PlayField(game.GetShiftedValue(), game);
      break;
    case 4:
      GetShiftValues(game.GetInitValue(), game.GetShiftValue());

      if ((game.GetInitValue() < 0 || game.GetInitValue() > 255) &&
          (game.GetShiftValue() < 0 || game.GetShiftValue() > 255)) {
        GetShiftValues(game.GetInitValue(), game.GetShiftValue());
      }

      game.SetShiftedValue(game.GetInitValue() | game.GetShiftValue());
      DisplayBitValue(game.GetInitValue(), game.GetShiftValue());

      game.PlayField(game.GetShiftedValue(), game);
      break;
    case 5:
      std::cout << "The Random game is not Implemented yet" << std::endl;
      continue;
      // game.PlayField(shifted_value, game);
      // break;
    case 6:
      std::cout << "Exiting the game. Goodbye!" << std::endl;
      is_playing = false;
      break;
    default:
      std::cout << "Invalid selection. Exiting the game." << std::endl;
    }

    std::cout << std::endl;
  } while (is_playing);

  std::cout << "Thank you for playing the Bit Shift Game!" << std::endl;
  std::cout << game.ToString();
}

void Game::DisplayBitValue(uint8_t init_value, uint8_t shift_value) {
  std::cout << init_value << std::endl;
  std::cout << "Binary view: " << std::bitset<8>(init_value) << std::endl;

  std::cout << shift_value << std::endl;
  std::cout << "Binary view: " << std::bitset<8>(shift_value) << std::endl;
}

void Game::PlayField(int shifted_value, Game game) {
  std::cout << "Guess the shifted value: ";
  std::cin >> guess_value;
  game.SetGuessValue(guess_value);

  if (CheckGuess(game.GetGuessValue(), shifted_value)) {
    std::cout << "Congratulations! Your guess is correct." << std::endl;
    game.SetCorrectGuesses(game.GetCorrectGuesses() + 1);
  } else {
    std::cout << "Sorry, your guess is incorrect. The correct value is: "
              << game.GetShiftedValue() << std::endl;
    game.SetWrongGuesses(game.GetWrongGuesses() + 1);
  }

  game.SetRoundNumber(game.GetRoundNumber() + 1);
  game.SetAccuracy();

  if (PlayAgain()) {
    Start(Game(game.GetCorrectGuesses(), game.GetWrongGuesses(),
               game.GetAccuracy(), game.GetRoundNumber()));
    return;
  }
}

bool Game::PlayAgain() {
  bool is_playing;
  std::cout << "Do you want to play again? (1 for Yes, 0 for No): ";
  std::cin >> is_playing;

  return is_playing;
}
