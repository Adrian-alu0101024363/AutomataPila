#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <assert.h>
#include "../headers/State.hpp"

using namespace std;

class nfa {
  private:
    int NumberNodes_; //Number of states of the dfa
    int NumberTransitions_; //Number of transitions of the dfa
    string initialState_; //The initial state of the dfa
    int alfabetsize_; //The size of the alfabet of the dfa
    int NumberAcept_; //Number of acept states of the dfa            
    set<State> States_; //Set of states within the dfa
    set<string> Alfabet_; //Set of characther of the alfabet that read the dfa
    string stackinitial_;
    set<string> stack_symbols_;
    stack<string> stack_;  
    string actualState_;
    bool acceptedInput_;
    string input_;
    int end_;
    bool trace_;
  public:
    void read(string inputfile);
    void show();
    vector<Transition> getMoves(State actual, string symbol, stack<string> extract);
    void execute(string chain);
    void executeFile(string filename);
    void executeStep(State actualState, string input, string real, stack<string> stepStack, int move);
    void setTrace(bool trace) {trace_ = trace;}
  private:
    void uncomment(string inputfile, string outfile);
    void clean(string inputfile, string outfile);
    bool checkEnd(string input, int move);
    vector<string> splitString(string str, string delimiter = " ");
    void ParseStates(string line);
    bool ValidState(State check);
    void ParseAlfabeth(string line);
    void ParseStack(string line);
    bool ValidStack(string check);
    void ParseAccept(string line);
    void ParseTrans(string line, ifstream& file);
    void Trace(State actualState, string input, string real, stack<string> stepStack, int move);
};
