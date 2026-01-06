#include <string>
#include <vector>

using std::string;
using std::vector;

class Mastermind {
 public:
  Mastermind();

  Mastermind(string solution);

  void new_solution();

  void set_solution(string sequence);

  string check_guess(string sequence);

 private:
  vector<int> count_letter_instances(string sequence);

  string m_solution;

  vector<int> m_solution_count;
};
