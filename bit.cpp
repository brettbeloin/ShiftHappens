#include <iostream>

int GetUserInput() {
  int user_input;

  do {
    std::cout << "Select Mode: " << std::endl;
    std::cout << "1. Shift Left" << std::endl;
    std::cout << "2. Shift Right" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> user_input;
  } while (user_input < 1 || user_input > 3);

  return user_input;
}

void GetShiftValues(int &init_value, int &shift_value) {
  std::cout << "Enter the initial value (integer): ";
  std::cin >> init_value;

  std::cout << "Enter the number of bits to shift (integer): ";
  std::cin >> shift_value;
}

bool CheckGuess(int guess, int shifted_value) { return guess == shifted_value; }

int main() {
  int init_value, shift_value, shifted_value, guess_value;
  bool is_playing = true;

  std::cout << "Welcome to the Bit Shift Game!\n";

  do {
    switch (GetUserInput()) {
    case 1:
      GetShiftValues(init_value, shift_value);
      shifted_value = init_value << shift_value;
      break;
    case 2:
      GetShiftValues(init_value, shift_value);
      shifted_value = init_value >> shift_value;
      break;
    case 3:
      std::cout << "Exiting the game. Goodbye!" << std::endl;
      // is_playing = false;
      // break;
      return 0;
    default:
      std::cout << "Invalid selection. Exiting the game." << std::endl;
      return 0;
    }

    std::cout << "Guess the shifted value: ";
    std::cin >> guess_value;

    if (CheckGuess(guess_value, shifted_value)) {
      std::cout << "Congratulations! Your guess is correct." << std::endl;
    } else {
      std::cout << "Sorry, your guess is incorrect. The correct value is: "
                << shifted_value << std::endl;
    }

    std::cout << "Do you want to play again? (1 for Yes, 0 for No): ";
    std::cin >> is_playing;

    std::cout << std::endl;
  } while (is_playing);

  std::cout << "Thank you for playing the Bit Shift Game!" << std::endl;
  return 0;
}
