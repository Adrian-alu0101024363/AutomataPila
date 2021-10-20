#include "../headers/nfa.h"

using namespace std;

int main(int argc, char** argv) {
  const int kOne = 1;
  const int kTwo = 2;
  const int kThree = 3;
  if (argc != kThree) {
    // wip 
  } else {
    string input = argv[kOne];
    string output = argv[kTwo];
    nfa automata;
    automata.read(input);
    automata.show();
    string simbolo;
    //automata.test();
    cout << "Escribe: ";
    cin >> simbolo;
    automata.execute(simbolo);
  }
}