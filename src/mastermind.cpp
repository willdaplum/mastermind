#include <algorithm>
#include <mastermind/mastermind.hpp>
#include <random>
#include <string>
#include <vector>

using std::string;

Mastermind::Mastermind() { new_solution(); };

Mastermind::Mastermind(string solution) : m_solution(solution) {
  m_solution_count = count_letter_instances(solution);
};

void Mastermind::new_solution() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(97,
                                                                 102);  // [a,f]
  string sequence = "";
  for (int i = 0; i < 4; ++i) {
    char random_letter = dist6(rng);
    sequence += random_letter;
  }
  m_solution = sequence;
  m_solution_count = count_letter_instances(sequence);
};

void Mastermind::set_solution(string sequence) {
  m_solution = sequence;
  m_solution_count = count_letter_instances(sequence);
};

string Mastermind::check_guess(string sequence) {
  string hint = "";
  vector<int> guess_count = count_letter_instances(sequence);
  vector<int> temp_solution_count = m_solution_count; // modified for calculating hint
  for (int i = 0; i < 4; ++i) {
    if (m_solution.at(i) == sequence.at(i)) {
      hint += 'y';
      guess_count.at(sequence.at(i) - 97)--;
      temp_solution_count.at(sequence.at(i) - 97)--;
    }
  }
  for (int i = 0; i < 6; ++i) {
    hint += string(std::min(temp_solution_count.at(i), guess_count.at(i)), 'w');
  }
  hint += string(4 - hint.length(), 'n');

  return hint;
};

vector<int> Mastermind::count_letter_instances(string sequence) {
  vector<int> count(6, 0);
  for (char c : sequence) {
    count.at(c - 97)++;
  }
  return count;
};
