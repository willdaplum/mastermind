#include <string>

using std::string;

class Mastermind {
 public:
	Mastermind();
	
	Mastermind(string solution);

	void set_solution(string solution);

	string check_guess();
 private:
	string solution;
};
