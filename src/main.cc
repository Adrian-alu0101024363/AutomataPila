#include "../headers/nfa.h"

using namespace std;

int main(int argc, char** argv) {
  const int kOne = 1;
  const int kTwo = 2;
  if (argc != kTwo) {
    cout << "Invalid format";
  } else {
    string input = argv[kOne];
    nfa automata;
    automata.read(input);
    automata.show();
    string simbolo;
    string filename;
    int option;
    do {
      cout << "1- Type chain" << endl;
      cout << "2- Get from file" << endl;
      cout << "3- Enable/Disable trace" << endl;
      cout << "0- Exit " << endl;
      cin >> option;
      if (option == kOne) {
        cout << "Type the chain: ";
        cin >> simbolo;
        automata.execute(simbolo);
      } else if (option == kTwo) {
        cout << "Type the file name" << endl;
        cin >> filename;
        automata.executeFile(filename);
      } else if (option == 3) {
        cout << "1 Enable, 0 Disable";
        bool trace;
        cin >> trace;
        automata.setTrace(trace);
      } else if (option == 0) {
        cout << "Closing program" << endl;
      } else {
        cout << "Non valid option" << endl;
      }
    } while (option != 0);
  }
}