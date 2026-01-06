# Mastermind CLI

A simple way to play mastermind on the command line.  
The computer will choose a 4 letter solution constisting of the letters [a, b, c, d, e, f]  
Submit 4 letter guesses to receive a clue: y for a letter in the correct spot, w for a letter in the wrong spot, and n for a miss.  

## Example
With solution abcd:  
```sh
Enter Guess:
aaaa
Hint: ynnn
Enter Guess:
bacd
Hint: yyww
Enter Guess:
abcd
Hint: yyyy (you win)
```

## Usage

### Install and run
```sh
cmake -S . -B build
cmake --build build
./build/mastermind_cli
```

### To play with a preset solution:  
```sh
./build/mastermind_cli --solution abcd
```

### Done playing?

Guess exit, and the program will terminate.

```sh
Enter guess:
exit
```

