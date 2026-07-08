#include "game.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>

void Game::Start() {
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

            this->SetShiftedValue(this->GetInitValue() & this->GetShiftValue());
            DisplayBitValue(this->GetInitValue(), this->GetShiftValue());

            this->PlayField(this->GetShiftedValue());
            break;
        case 4:
            GetShiftValues(this->GetInitValue(), this->GetShiftValue());

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
            std::cout << this->ToString();
            // is_playing = false;
            return;
        default:
            std::cout << "Invalid selection. Exiting the game." << std::endl;
        }

        std::cout << std::endl;
    } while (PlayAgain());

    std::cout << "Thank you for playing the Bit Shift Game!" << std::endl;
    std::cout << this->ToString();
}

int Game::GetUserInput() {
    int               user_input;
    std::string       string_user_input;

    bool              valid_answer = false;
    const std::string menu = "Select Mode: \n"
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

        if (!ValidateUserInput(string_user_input, user_input, {1, 6})) {
            continue;
        }

        valid_answer = true;
    } while (!valid_answer);

    return user_input;
}

bool Game::ValidateUserInput(std::string &string_user_input, int &user_input,
                             Game::diffculty_changes diffculty_changes) {

    std::getline(std::cin, string_user_input);
    std::istringstream iss(trim(string_user_input));
    iss >> user_input;

    if (!iss.eof()) {
        std::cerr << "Bad Input. not EOF\n";
        return false;
    }

    if (iss.fail()) {
        iss.clear();
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Bad input. All inputs must be numeric and fit in the range\n";
        return false;
    }

    if (user_input < diffculty_changes.min || user_input > diffculty_changes.max) {
        return false;
    }

    return true;
}

void Game::GetShiftValues(int init_value, int shift_value) {
    std::string             foo;
    std::string             bar;
    bool                    valid_answer = false;
    Game::diffculty_changes diffculty_changes = {0, 255};

    do {
        std::cout << "Enter the initial value (integer): ";
        if (!ValidateUserInput(foo, init_value, diffculty_changes)) {
            continue;
        }
        SetInitValue(init_value);

        std::cout << "Enter the number of bits to shift (integer): ";
        if (!ValidateUserInput(bar, shift_value, diffculty_changes)) {
            continue;
        }

        SetShiftValue(shift_value);
        valid_answer = true;
    } while (!valid_answer);
}

void Game::PlayField(int shifted_value) {
    std::string foo;
    bool        valid_answer = false;

    do {
        std::cout << "Guess the shifted value: ";
        if (!ValidateUserInput(foo, this->guess_value, {0, 255})) {
            continue;
        }

        if (CheckGuess(this->GetGuessValue(), shifted_value)) {
            std::cout << "Congratulations! Your guess is correct." << std::endl;
            this->SetCorrectGuesses(this->GetCorrectGuesses() + 1);
        } else {
            std::cout << "Sorry, your guess is incorrect. The correct value is: " << this->GetShiftedValue()
                      << std::endl;
            this->SetWrongGuesses(this->GetWrongGuesses() + 1);
        }

        valid_answer = true;
    } while (!valid_answer);

    this->SetRoundNumber(this->GetRoundNumber() + 1);
}

bool Game::CheckGuess(const int guess, int shifted_value) {
    return guess == shifted_value;
}

void Game::DisplayBitValue(int init_value, int shift_value) {
    std::cout << init_value << std::endl;
    std::cout << "Binary view: " << std::bitset<8>(init_value) << std::endl;

    std::cout << shift_value << std::endl;
    std::cout << "Binary view: " << std::bitset<8>(shift_value) << std::endl;
}

bool Game::PlayAgain() {
    bool        is_valid = false;
    std::string foo;
    int         user_input;

    do {
        std::cout << "Do you want to play again? (1 for Yes, 0 for No): ";

        if (!ValidateUserInput(foo, user_input, {0, 1})) {
            continue;
        }

        is_valid = true;
    } while (!is_valid);

    return user_input == 1 ? true : false;
}
