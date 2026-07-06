#pragma once
#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>
#include <string>

class Game {
public:
  Game() = default;

  Game(int correct_guesses, int wrong_guesses, float accuracy, int round_number)
      : correct_guesses(correct_guesses), wrong_guesses(wrong_guesses),
        accuracy(accuracy), round_number(round_number) {}

  void Start();

  int GetInitValue() const { return init_value; }
  int GetShiftValue() const { return shift_value; }
  int GetShiftedValue() const { return shifted_value; }
  int GetGuessValue() const { return guess_value; }

  int GetRandomInitValue() const { return random_init_value; }
  int GetRandomShiftValue() const { return random_shift_value; }

  int GetCorrectGuesses() const { return correct_guesses; }
  int GetWrongGuesses() const { return wrong_guesses; }
  float GetAccuracy() const { return accuracy; }

  int GetRoundNumber() const { return round_number; }

  void SetInitValue(int value) { init_value = value; }
  void SetShiftValue(int value) { shift_value = value; }
  void SetShiftedValue(int value) { shifted_value = value; }
  void SetGuessValue(int value) { guess_value = value; }

  void SetRandomInitValue() {
    srand(time(0));
    random_init_value = rand() % 101;
  }

  void SetRandomShiftValue() {
    srand(time(0));
    random_shift_value = rand() % 101;
  }

  void SetCorrectGuesses(int value) { correct_guesses = value; }
  void SetWrongGuesses(int value) { wrong_guesses = value; }
  void SetAccuracy() {
    if (wrong_guesses == 0) {
      accuracy = 100;
      return;
    }

    accuracy = (static_cast<float>(correct_guesses) /
                static_cast<float>(wrong_guesses)) *
               100;
  }

  void SetRoundNumber(int value) { round_number = value; }

  std::string ToString() {
    std::ostringstream ss;

    ss << "Wins: " << correct_guesses << " Losses " << wrong_guesses
       << " Accuracy " << accuracy << "%\n";

    return ss.str();
  }

private:
  int init_value;
  int shift_value;
  int shifted_value;
  int guess_value;

  int random_init_value;
  int random_shift_value;

  int correct_guesses = 0;
  int wrong_guesses = 0;
  float accuracy = 0;

  int round_number = 1;

  int GetUserInput();

  void GetShiftValues(int init_value, int shift_value);
  void DisplayBitValue(uint8_t init_value, uint8_t shift_value);

  bool CheckGuess(int guess, int shifted_value);
  void PlayField(int value_shift);
  bool PlayAgain();
};
