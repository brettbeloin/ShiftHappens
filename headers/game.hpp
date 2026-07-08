#pragma once
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <unordered_map>

class Game {
    // public facing objects
  public:
    struct diffculty_changes {
        int min;
        int max;
    };

    std::unordered_map<int, std::string> signs = {
        {1, "<<"},
        {2, ">>"},
        {3,  "&"},
        {4,  "|"}
    };

    // public facing methods
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

    bool ValidateUserInput(std::string &string_user_input, int &user_input, const struct diffculty_changes);

    int  GetInitValue() const {
        return init_value;
    }
    int GetShiftValue() const {
        return shift_value;
    }
    int GetShiftedValue() const {
        return shifted_value;
    }
    int GetGuessValue() const {
        return guess_value;
    }

    int GetRandomInitValue() const {
        return random_init_value;
    }

    int GetRandomShiftValue() const {
        return random_shift_value;
    }

    int GetCorrectGuesses() const {
        return correct_guesses;
    }
    int GetWrongGuesses() const {
        return wrong_guesses;
    }

    float GetAccuracy() const {
        return accuracy;
    }

    int GetRoundNumber() const {
        return round_number;
    }

    void SetInitValue(int value) {
        init_value = value;
    }
    void SetShiftValue(int value) {
        shift_value = value;
    }
    void SetShiftedValue(int value) {
        shifted_value = value;
    }
    void SetGuessValue(int value) {
        guess_value = value;
    }

    void SetRandomInitValue(std::size_t max_value) {
        random_init_value = (rand() % max_value) + 1;
    }

    void SetRandomShiftValue(std::size_t max_value) {
        random_shift_value = (rand() % max_value) + 1;
    }

    void SetCorrectGuesses(int value) {
        correct_guesses = value;
    }

    void SetWrongGuesses(int value) {
        wrong_guesses = value;
    }

    void SetAccuracy() {
        if (wrong_guesses == 0) {
            accuracy = 100;
            return;
        }

        accuracy = (static_cast<float>(correct_guesses) / static_cast<float>(correct_guesses + wrong_guesses)) * 100;
    }

    void SetRoundNumber(int value) {
        round_number = value;
    }

    std::string ToString() {
        std::ostringstream ss;

        ss << "Wins: " << correct_guesses << " Losses " << wrong_guesses << " Accuracy " << accuracy << "%\n";

        return ss.str();
    }

  private:
    const std::string WHITESPACE = " \n\r\t\f\v";

    int               init_value;
    int               shift_value;
    int               shifted_value;
    int               guess_value;

    int               random_init_value;
    int               random_shift_value;

    int               correct_guesses = 0;
    int               wrong_guesses = 0;
    float             accuracy = 0;

    int               round_number = 1;

    int               GetUserInput();

    void              GetShiftValues(int init_value, int shift_value);
    void              DisplayBitValue(int init_value, int shift_value);

    bool              CheckGuess(int guess, int shifted_value);
    void              PlayField(int value_shift);
    void              RandomMode();
    bool              PlayAgain();
};
