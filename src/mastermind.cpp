#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <mastermind/mastermind.hpp>

using std::string;

Mastermind::Mastermind() {
  new_solution();
};

Mastermind::Mastermind(string solution)
 : m_solution(solution) {
  m_solution_count = count_letter_instances(solution);
};

void Mastermind::new_solution() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(97, 102); // [a,f]
  string sequence = "";
  for(int i = 0; i < 4; ++i)
    sequence += (char) dist6(rng);
  m_solution = sequence;
};

void Mastermind::set_solution(string sequence) {
  m_solution = sequence;
};

string Mastermind::check_guess(string sequence) {
  string hint = "";
  vector<int> guess_count = count_letter_instances(sequence);
  for(int i = 0; i < 4; ++i) {
    if(m_solution[i] == sequence[i]) {
      hint += 'y';
      guess_count[m_solution[i] - 97]--;
    }
  }
  for(int i = 0; i < 6; ++i) {
    hint += string(std::min(m_solution_count[i],guess_count[i]), 'w');    
  }
  hint += string(4 - hint.length(), 'n');

  return hint;
};

vector<int> Mastermind::count_letter_instances(string sequence) {
  vector<int> count(6, 0);
  for(char c : sequence) {
    count[c - 97]++;
  }
};
