#include <mastermind/mastermind.hpp>

#include <boost/ut.hpp>

using namespace boost::ut;

int main() {
  Mastermind m = Mastermind();
  m.set_solution("abcd");
  expect(m.check_guess("aaaa") == "ynnn");
  expect(m.check_guess("bbbb") == "ynnn");
  expect(m.check_guess("cccc") == "ynnn");
  expect(m.check_guess("dddd") == "ynnn");
  expect(m.check_guess("dcba") == "wwww");
  expect(m.check_guess("bacd") == "yyww");
  expect(m.check_guess("eacd") == "yywn");
  expect(m.check_guess("eeee") == "nnnn");
  expect(m.check_guess("eeea") == "wnnn");

  m.set_solution("eaba");
  expect(m.check_guess("aaaa") == "yynn");
  expect(m.check_guess("bbbb") == "ynnn");
  expect(m.check_guess("eeee") == "ynnn");
  expect(m.check_guess("eabc") == "yyyn");
  expect(m.check_guess("abae") == "wwww");
  expect(m.check_guess("ffff") == "nnnn");
  expect(m.check_guess("aabe") == "yyww");
  expect(m.check_guess("afaf") == "wwnn");
  expect(m.check_guess("fafa") == "yynn");
}
