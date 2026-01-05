#include <mastermind/mastermind.hpp>

#include <boost/ut.hpp>

using my_fibonacci::fibonacci_sequence;
using namespace boost::ut;

int main() {
  Mastermind m = Mastermind();
  m.set_solution("abcd");
  should("guessing with solution abcd") = [] {
    expect(mastermind.check_solution("aaaa") == "ynnn");
    expect(mastermind.check_solution("bbbb") == "ynnn");
    expect(mastermind.check_solution("cccc") == "ynnn");
    expect(mastermind.check_solution("dddd") == "ynnn");
    expect(mastermind.check_solution("dcba") == "wwww");
    expect(mastermind.check_solution("bacd") == "yyww");
    expect(mastermind.check_solution("eacd") == "yywn");
    expect(mastermind.check_solution("eeee") == "nnnn");
    expect(mastermind.check_solution("eeea") == "wnnn");
  };

  m.set_solution("eaba");
  should("guessing with solution eaba") = [] {
    expect(mastermind.check_solution("aaaa") == "yynn");
    expect(mastermind.check_solution("bbbb") == "ynnn");
    expect(mastermind.check_solution("eeee") == "ynnn");
    expect(mastermind.check_solution("eabc") == "yyyn");
    expect(mastermind.check_solution("abae") == "wwww");
    expect(mastermind.check_solution("ffff") == "nnnn");
    expect(mastermind.check_solution("aabe") == "yyww");
    expect(mastermind.check_solution("afaf") == "wwnn");
    expect(mastermind.check_solution("fafa") == "yynn");
  };
}
