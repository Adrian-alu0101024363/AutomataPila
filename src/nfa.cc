#include "../headers/nfa.h"

using namespace std;

void nfa::read(string inputfile) {
  string uncommented = "Unconmented";
  string cleaned = "Clean";
  uncomment(inputfile, uncommented);
  clean(uncommented, cleaned);
  ifstream file;
  file.open(cleaned);
  string line;
  if (file) {
    getline(file, line, '\n');
    ParseStates(line);
    getline(file, line);
    ParseAlfabeth(line);
    getline(file, line);
    ParseStack(line);
    getline(file, line);
    State initial;
    initial.setnode(line);
    assert(ValidState(initial));
    initialState_ = line;
    actualState_ = line;
    getline(file, line);
    assert(ValidStack(line));
    stackinitial_ = line;
    stack_.push(stackinitial_);
    getline(file, line);
    ParseAccept(line);
    ParseTrans(line, file);
  }
  file.close();
}

void nfa::uncomment(string inputfile, string outfile) {
  ifstream file;
  regex comment ("#+"); 
  file.open(inputfile);
  string line;
  ofstream output;
  output.open(outfile);
  if (file) {
    while(getline(file, line)) {
    if (regex_search(line, comment)) {
      std::size_t found = line.find_first_of("#");
      line.erase(line.begin() + found, line.end());
      output << line << endl;
    } else {
	    output << line << endl;
    }
      //cout << line << endl;
    }

  } else { 
    cout << "Couldn't open the file" << endl;
  }
  output.close();
  file.close();
}

void nfa::clean(string inputfile, string outfile) {
  ifstream file;
  file.open(inputfile);
  string line;
  ofstream output;
  output.open(outfile);
  while (getline(file, line)) {
    if (!line.empty()) {
      output << line << "\n";
    }
  }
}

vector<string> nfa::splitString(string str, string delimiter) {
    int start = 0;
    int end = str.find(delimiter);
    vector<string> strings;
    while (end != -1) {
        strings.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    strings.push_back(str.substr(start, end - start));
    return strings;
}

vector<Transition> nfa::getMoves(State actual, string symbol, stack<string> extract) {
  vector<Transition> transition = actual.gettrans();
  vector<Transition> allowed;
  string actual_symbol;
  string top;
  string actual_top = extract.top();
  for (int i = 0; i < transition.size(); i++) {
    actual_symbol = transition[i].getsimb();
    top = transition[i].getExtract();
    if (actual_symbol == symbol || actual_symbol == ".") {
      if (actual_top == top) {
        Transition tran = transition[i];
        allowed.push_back(tran);
      }
    }
  }
  return allowed;
}

void nfa::executeFile(string filename) {
  ifstream file;
  file.open(filename,ios::in);
  string line;
  while (getline(file,line)) {
    execute(line);
  }
}

void nfa::execute(string chain) {
  State initial;
  input_ = chain;
  end_ = chain.length();
  acceptedInput_ = false;
  string input;
  input.push_back(chain[0]);
  for (auto i : States_) {
    if (i.getnode() == initialState_) {
      initial = i;
    }
  }
  executeStep(initial, input, chain, stack_, 1);
  if (acceptedInput_) {
    cout << endl << "Chain is accepted!" << endl;
  } else {
    cout << endl << "Chain not valid" << endl;
  }
}

void nfa::executeStep(State actualState, string input, string real, stack<string> stepStack, int move) {
  if (!acceptedInput_) {
    if (real.empty()) {
      if (actualState.getacept()) {
        acceptedInput_ = true;
      }
    }
    string actual_input;
    if (real.empty()) {
      actual_input = ".";
    } else {
      actual_input.push_back(real[0]);
    }
    if (trace_) {
      Trace(actualState, actual_input, real, stepStack, move);
    }
    vector<Transition> allowedTrans = getMoves(actualState, actual_input, stepStack);
    if (allowedTrans.size() > 0) {
    for (int i = 0; i < allowedTrans.size(); i++) {
      string input_string = "";
      stack<string> tempstack = stepStack;
      string tempinput = real;
      State tempstate = actualState;
      string dot = ".";
      if (allowedTrans[i].getsimb() != dot) {
        if (!tempinput.empty()) {
          tempinput.erase(0, 1);
        }
        input_string.push_back(real[0]);
        move++;
      } else {
        input_string = ".";
      }
      string nextstate_string = allowedTrans[i].getdestination();
      if (trace_) cout << endl << "Next state: " << nextstate_string;
      State nextstate;
      for (auto i : States_) {
        if (i.getnode() == nextstate_string) {
          nextstate = i;
        }
      }
      tempstack.pop();
      vector<string> nextsymbols = allowedTrans[i].getInsert();
      for (int i = nextsymbols.size() - 1; i >= 0; i--) {
        if (nextsymbols[i] != ".") {
          tempstack.push(nextsymbols[i]);
        }
      }
      executeStep(nextstate, input_string, tempinput, tempstack, move);
    }
    } else {
      
    }
  } else {
    
  }
}
bool nfa::checkEnd(string input, int move) {
  return move > end_ ? 1 : 0;
}

void nfa::show() {
    cout << "Size alfabeto: " << alfabetsize_ << endl;
    cout << "Simbolos del alfabeto: ";
    for (set<string>::iterator s = Alfabet_.begin(); s!= Alfabet_.end(); s++) {
      cout << *s << " , ";
    }
    cout << endl << "Simbolos del alfabeto pila: ";
    for (set<string>::iterator s = stack_symbols_.begin(); s!= stack_symbols_.end(); s++) {
      cout << *s << " , ";
    }
    cout << endl << "Pila inicial: " << stackinitial_;
    cout << endl << "Estado inicial: " << initialState_ << endl;
    cout << "Nodos son: " << NumberNodes_ << endl;
    cout << "Numero aceptados: " << NumberAcept_ << endl;
    cout << "Estados:" << endl;
    for (set<State>::iterator i = States_.begin(); i != States_.end(); i++) {
      State aux(*i);
      string temp = aux.getnode();
      vector<Transition> walk = aux.gettrans();
      bool acept = aux.getacept();
      cout << temp << "  Es aceptado?: " << acept << endl;
      cout << "Transiciones " ;
      for (vector<Transition>::iterator t = walk.begin(); t != walk.end(); t++) {
        Transition tran(*t);
        string tra = tran.getsimb();
        string suginode = tran.getdestination();
        string extra = tran.getExtract();
        cout << "con simbolo: " << tra << " hacia -> " << suginode;
        cout << " extrae: "<< extra << " inserta: ";
        for (int i = 0; i < tran.getInsert().size(); i++) {
          cout << tran.getInsert()[i] << "\t";
        }
        cout << endl;
      }
      cout << endl;
    }
}

void nfa::Trace(State actualState, string input, string real, stack<string> stepStack, int move) {
    cout << endl << "Move: " << move << endl;
    cout << "Current State: " << actualState.getnode() << endl;
    cout << "Input: " << input << " Chain: " << real << endl;
    stack<string> checking = stepStack;
    cout << "En pila: ";
    while (!checking.empty()) {
      cout << checking.top() << "\t";
      checking.pop();
    }
}

bool nfa::ValidState(State check) {
  return States_.find(check) != States_.end();
}

void nfa::ParseStates(string line) {
  string nodeaux;
  vector<string> strings;
  NumberNodes_ = strings.size();
  strings = splitString(line);
  for (int i = 0; i < strings.size(); i++) {
  State aux;
  nodeaux = strings[i];
  aux.setnode(nodeaux);
  States_.insert(aux);
  }
}

void nfa::ParseAlfabeth(string line) {
  string nodeaux;
  vector<string> strings;
  strings = splitString(line);
  alfabetsize_ = strings.size();
  for (int i = 0; i < strings.size(); i++) {
    Alfabet_.insert(strings[i]);
  }
}

void nfa::ParseStack(string line) {
  string nodeaux;
  vector<string> strings;
  strings = splitString(line);
  strings = splitString(line);
  for (int i = 0; i < strings.size(); i++) {
    stack_symbols_.insert(strings[i]);
  }
}

bool nfa::ValidStack(string check) {
  return stack_symbols_.find(check) != stack_symbols_.end();
}

void nfa::ParseAccept(string line) {
  string nodeaux;
  vector<string> strings;
  strings = splitString(line);
  NumberAcept_ = strings.size();
  for (int i = 0; i < strings.size(); i++) {
    nodeaux = strings[i];
    State aux2;
    aux2.setnode(nodeaux);
    assert(ValidState(aux2));
    auto pos = States_.find(aux2);
    States_.erase(pos);
    aux2.setacept(1);
    States_.insert(aux2);
   }
}

void nfa::ParseTrans(string line, ifstream& file) {
  vector<string> strings; 
  string nodeaux,destinationnode,originnode;
  string simbolaux, extractaux;  
  while (getline(file, line)) {
    strings = splitString(line);
    originnode = strings[0];
    simbolaux = strings[1];
    extractaux = strings[2];
    destinationnode = strings[3];
    Transition aux3;
    State comparenode;
    comparenode.setnode(originnode);
    assert(ValidState(comparenode));
    aux3.setsimb(simbolaux);
    State destinationaux;
    destinationaux.setnode(destinationnode);
    assert(ValidState(destinationaux));
    aux3.setdestination(destinationnode);
    assert(ValidStack(extractaux));
    aux3.setExtract(extractaux);
    vector<string> insertaux;
    for (int i = 4; i < strings.size(); i++) {
      if (strings[i] != ".") assert(ValidStack(strings[i]));
      insertaux.push_back(strings[i]);
    }
    aux3.setInsert(insertaux);
    set<State>::iterator it = States_.begin();
    while (it != States_.end()) {
      State temp(*it);
      if (temp.getnode() == comparenode.getnode()) {
        vector<Transition> walk = temp.gettrans();
        for (vector<Transition>::iterator t = walk.begin(); t != walk.end(); t++) {
          Transition tranaux(*t);
          comparenode.settrans(tranaux);
        }
        if (temp.getacept()) {
          comparenode.setacept(1);
          comparenode.settrans(aux3);
        } else {
          comparenode.settrans(aux3);
        }
      }
      it++;
      }
      auto position = States_.find(comparenode);
      States_.erase(position);
      States_.insert(comparenode);
    }
}