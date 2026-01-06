#include <mastermind/mastermind.hpp>

#include <argparse/argparse.hpp>

#include <iostream>

bool check_input(string sequence) {
  if (sequence.length() != 4) return false;
  for (char c : sequence) {
    if (c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f')
      return false;
  }
  return true;
}

int main(int argc, char** argv) {
  argparse::ArgumentParser program("mastermind");
  program.add_description(
      "Play mastemind from the command line! 4 letter guesses/solution using "
      "letters abcdef");
  program.add_argument("-s", "--solution")
      .help("Sets solution to user choice")
      .default_value("");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  Mastermind m;
  std::string user_solution = program.get<std::string>("-s");

  if (user_solution == "")
    m = Mastermind();
  else if (check_input(user_solution))
    m = Mastermind(user_solution);
  else {
    std::cout << "Malformatted solution. must be 4 letters, and only contain "
                 "abcdef\n";
  }

  while (true) {
    string guess = "";
    std::cout << "Enter guess:\n";
    std::cin >> guess;
    if (check_input(guess)) {
      std::cout << m.check_guess(guess) << "\n";
    } else if (guess == "exit") {
      break;
    } else {
      std::cout
          << "Invalid format: must be 4 letters and only contain abcdef\n";
    }
  }

  return 0;
}
