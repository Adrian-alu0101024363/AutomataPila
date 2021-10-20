#include "../headers/nfa.h"

using namespace std;

void nfa::read(string inputfile) {
  string uncommented = "Unconmented";
  string cleaned = "Clean";
  uncomment(inputfile, uncommented);
  clean(uncommented, cleaned);
  string nodeaux,destinationnode,originnode;
  string simbolaux, extractaux;     
  bool aceptaux;
  ifstream file;
  file.open(cleaned);
  string line;
  if (file) {
    getline(file, line, '\n');
    vector<string> strings;
    strings = splitString(line);
    NumberNodes_ = strings.size();
    for (int i = 0; i < strings.size(); i++) {
      State aux;
      nodeaux = strings[i];
      aux.setnode(nodeaux);
      States_.insert(aux);
    }
    getline(file, line);
    strings = splitString(line);
    alfabetsize_ = strings.size();
    for (int i = 0; i < strings.size(); i++) {
      Alfabet_.insert(strings[i]);
    }
    getline(file, line);
    strings = splitString(line);
    for (int i = 0; i < strings.size(); i++) {
      stack_symbols_.insert(strings[i]);
    }
    getline(file, line);
    initialState_ = line;
    actualState_ = line;
    getline(file, line);
    stackinitial_ = line;
    stack_.push(stackinitial_);
    getline(file, line);
    strings = splitString(line);
    NumberAcept_ = strings.size();
    for (int i = 0; i < strings.size(); i++) {
      nodeaux = strings[i];
      State aux2;
      aux2.setnode(nodeaux);
      auto pos = States_.find(aux2);
      States_.erase(pos);
      aux2.setacept(1);
      States_.insert(aux2);
    }
    while (getline(file, line)) {
      strings = splitString(line);
      originnode = strings[0];
      simbolaux = strings[1];
      extractaux = strings[2];
      destinationnode = strings[3];
      Transition aux3;
      State comparenode;
      comparenode.setnode(originnode);
      aux3.setsimb(simbolaux);
      aux3.setdestination(destinationnode);
      aux3.setExtract(extractaux);
      vector<string> insertaux;
      for (int i = 4; i < strings.size(); i++) {
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
    //cout << actual_symbol[0] << "\t" << symbol[0];
    if (actual_symbol == symbol || actual_symbol == ".") {
      if (actual_top == top) {
        Transition tran = transition[i];
        allowed.push_back(tran);
      }
    }
  }
  return allowed;
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
  cout << endl << "Chain is: " << acceptedInput_;
}
void nfa::executeStep(State actualState, string input, string real, stack<string> stepStack, int move) {
  if (!acceptedInput_) {
    if (real.empty()) {
      if (actualState.getacept()) {
        cout << "Acepto";
        acceptedInput_ = true;
      }
    }
    cout << "Move: " << move << endl;
    string kuso;
    if (real.empty()) {
      kuso = ".";
    } else {
      kuso.push_back(real[0]);
    }
    cout << "Estado actual " << actualState.getnode() << endl;
    cout << "Input " << kuso << "real " << real << endl;
    vector<Transition> allowedTrans = getMoves(actualState, kuso, stepStack);
    cout << "Size: " << allowedTrans.size() << endl;
    if (allowedTrans.size() > 0) {
    for (int i = 0; i < allowedTrans.size(); i++) {
      string input_string = "";
      stack<string> tempstack = stepStack;
      string tempinput = real;
      State tempstate = actualState;
      string dot = ".";
      //cout << allowedTrans[i].getsimb();
      if (allowedTrans[i].getsimb() != dot) {
        //int pos = real.find_first_of(allowedTrans[i].getsimb());
        if (!tempinput.empty()) {
          tempinput.erase(0, 1);
        }
        input_string.push_back(real[0]);
        move++;
      } else {
        input_string = ".";
      }
      //cout << "Move: " << move << endl;
      //cout << "Temp " << input_string << "real " << tempinput << endl;
      string nextstate_string = allowedTrans[i].getdestination();
      cout << "Siguiente:  " << nextstate_string << endl;
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
      stack<string> checking = tempstack;
      cout << "En pila: ";
      while (!checking.empty()) {
        cout << checking.top() << "\t";
        checking.pop();
      }
      cout << endl;
      //cout << "aceptado?: " << nextstate.getacept() << endl;
      //acceptedInput_ = nextstate.getacept();
      executeStep(nextstate, input_string, tempinput, tempstack, move);
    }
    } else {
      cout << "kuso mitai" << endl;
    }
  } else {
    cout << "llego final";
  }
}
bool nfa::checkEnd(string input, int move) {
  return move > end_ ? 1 : 0;
  /*char compare = input[move];
  if (input_.back() == compare) {
    return true;
  } else {
    return false;
  }*/
}
void nfa::test() {
  //set<State>::iterator i = States_.begin();
  for (auto iter : States_) {
    State aux(iter);
    string temp = aux.getnode();
    stack<string> stackaux;
    stackaux.push("S");
    vector<Transition> tran = getMoves(aux, "0", stackaux);
    if (!tran.empty()) {
      for (int i = 0; i < tran.size(); i++) {
        cout << tran[i].getdestination();
      }
    }
  }

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
