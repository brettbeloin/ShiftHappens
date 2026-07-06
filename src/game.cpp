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

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr
          << "Bad input. All inputs must be numaric and fit in the range\n";
      continue;
    }

    if (user_input < 1 || user_input > 6) {
      std::cerr << "Bad input. Input must be between: 1 and 6\n";
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

void Game::Start() {
  // bool is_playing = true;

  std::cout << "Welcome to the Bit Shift Game!\n";
  std::cout << "Round: " << this->GetRoundNumber() << "\n";
  std::cout << this->ToString() << std::endl;

  do {
    switch (GetUserInput()) {
    case 1:
      GetShiftValues(this->GetInitValue(), this->GetShiftValue());
      this->SetShiftedValue(this->GetInitValue() << this->GetShiftValue());

      this->PlayField(this->GetShiftedValue());
      break;
    case 2:
      GetShiftValues(this->GetInitValue(), this->GetShiftValue());
      this->SetShiftedValue(this->GetInitValue() >> this->GetShiftValue());

      this->PlayField(this->GetShiftedValue());
      break;
    case 3:
      GetShiftValues(this->GetInitValue(), this->GetShiftValue());

      if ((this->GetInitValue() < 0 || this->GetInitValue() > 255) &&
          (this->GetShiftValue() < 0 || this->GetShiftValue() > 255)) {
        GetShiftValues(this->GetInitValue(), this->GetShiftValue());
      }

      this->SetShiftedValue(this->GetInitValue() & this->GetShiftValue());
      DisplayBitValue(this->GetInitValue(), this->GetShiftValue());

      this->PlayField(this->GetShiftedValue());
      break;
    case 4:
      GetShiftValues(this->GetInitValue(), this->GetShiftValue());

      if ((this->GetInitValue() < 0 || this->GetInitValue() > 255) &&
          (this->GetShiftValue() < 0 || this->GetShiftValue() > 255)) {
        GetShiftValues(this->GetInitValue(), this->GetShiftValue());
      }

      this->SetShiftedValue(this->GetInitValue() | this->GetShiftValue());
      DisplayBitValue(this->GetInitValue(), this->GetShiftValue());

      this->PlayField(this->GetShiftedValue());
      break;
    case 5:
      std::cout << "The Random game is not Implemented yet" << std::endl;
      continue;
      // this->.PlayField(shifted_value, this->);
      // break;
    case 6:
      std::cout << "Exiting the game. Goodbye!" << std::endl;
      // is_playing = false;
      return;
    default:
      std::cout << "Invalid selection. Exiting the this->." << std::endl;
    }

    std::cout << std::endl;
  } while (PlayAgain());

  std::cout << "Thank you for playing the Bit Shift Game!" << std::endl;
  std::cout << this->ToString();
}

void Game::DisplayBitValue(uint8_t init_value, uint8_t shift_value) {
  std::cout << init_value << std::endl;
  std::cout << "Binary view: " << std::bitset<8>(init_value) << std::endl;

  std::cout << shift_value << std::endl;
  std::cout << "Binary view: " << std::bitset<8>(shift_value) << std::endl;
}

void Game::PlayField(int shifted_value) {
  std::cout << "Guess the shifted value: ";
  std::cin >> guess_value;
  this->SetGuessValue(guess_value);

  if (CheckGuess(this->GetGuessValue(), shifted_value)) {
    std::cout << "Congratulations! Your guess is correct." << std::endl;
    this->SetCorrectGuesses(this->GetCorrectGuesses() + 1);
  } else {
    std::cout << "Sorry, your guess is incorrect. The correct value is: "
              << this->GetShiftedValue() << std::endl;
    this->SetWrongGuesses(this->GetWrongGuesses() + 1);
  }

  this->SetRoundNumber(this->GetRoundNumber() + 1);
  this->SetAccuracy();

  // if (PlayAgain()) {
  //   Start();
  // }
}

bool Game::PlayAgain() {
  bool is_playing;
  std::cout << "Do you want to play again? (1 for Yes, 0 for No): ";
  std::cin >> is_playing;

  return is_playing;
}
