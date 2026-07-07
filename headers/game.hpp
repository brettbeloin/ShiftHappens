#pragma once
#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>
#include <string>

class Game {
  public:
    void Start();

    /*
     * trim function and the WHITESPACE var comes from:
     * https://www.scaler.com/topics/removing-whitespace-from-a-string-in-cpp/
     */
    std::string ltrim(const std::string &s) {
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string rtrim(const std::string &s) {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string trim(const std::string &s) {
        return rtrim(ltrim(s));
    }

    bool         ValidateUserInput(std::string &string_user_input, std::uint8_t &user_input);

    std::uint8_t GetInitValue() const {
        return init_value;
    }
    std::uint8_t GetShiftValue() const {
        return shift_value;
    }
    std::uint8_t GetShiftedValue() const {
        return shifted_value;
    }
    std::uint8_t GetGuessValue() const {
        return guess_value;
    }

    std::uint8_t GetRandomInitValue() const {
        return random_init_value;
    }
    std::uint8_t GetRandomShiftValue() const {
        return random_shift_value;
    }

    std::uint8_t GetCorrectGuesses() const {
        return correct_guesses;
    }
    std::uint8_t GetWrongGuesses() const {
        return wrong_guesses;
    }

    float GetAccuracy() const {
        return accuracy;
    }

    std::uint8_t GetRoundNumber() const {
        return round_number;
    }

    void SetInitValue(std::uint8_t value) {
        init_value = value;
    }
    void SetShiftValue(std::uint8_t value) {
        shift_value = value;
    }
    void SetShiftedValue(std::uint8_t value) {
        shifted_value = value;
    }
    void SetGuessValue(std::uint8_t value) {
        guess_value = value;
    }

    void SetRandomInitValue() {
        srand(time(0));
        random_init_value = rand() % 101;
    }

    void SetRandomShiftValue() {
        srand(time(0));
        random_shift_value = rand() % 101;
    }

    void SetCorrectGuesses(std::uint8_t value) {
        correct_guesses = value;
    }

    void SetWrongGuesses(std::uint8_t value) {
        wrong_guesses = value;
    }

    void SetAccuracy() {
        if (wrong_guesses == 0) {
            accuracy = 100;
            return;
        }

        accuracy = (static_cast<float>(correct_guesses) / static_cast<float>(correct_guesses + wrong_guesses)) * 100;
    }

    void SetRoundNumber(std::uint8_t value) {
        round_number = value;
    }

    std::string ToString() {
        std::ostringstream ss;

        ss << "Wins: " << correct_guesses << " Losses " << wrong_guesses << " Accuracy " << accuracy << "%\n";

        return ss.str();
    }

  private:
    const std::string WHITESPACE = " \n\r\t\f\v";

    std::uint8_t      init_value;
    std::uint8_t      shift_value;
    std::uint8_t      shifted_value;
    std::uint8_t      guess_value;

    std::uint8_t      random_init_value;
    std::uint8_t      random_shift_value;

    std::uint8_t      correct_guesses = 0;
    std::uint8_t      wrong_guesses = 0;
    float             accuracy = 0;

    std::uint8_t      round_number = 1;

    std::uint8_t      GetUserInput();

    void              GetShiftValues(std::uint8_t init_value, std::uint8_t shift_value);
    void              DisplayBitValue(std::uint8_t init_value, std::uint8_t shift_value);

    bool              CheckGuess(std::uint8_t guess, std::uint8_t shifted_value);
    void              PlayField(std::uint8_t value_shift);
    bool              PlayAgain();
};
