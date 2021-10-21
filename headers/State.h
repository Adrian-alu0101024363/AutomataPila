
#include <string>

#include "../headers/Transition.h"

class State {
  private:

    //VARIABLES//
    bool acept_;    //Is an acept state or not
    int numtrans_;  //Number of transition for state
    string node_;    //State,node name identifier
    vector<Transition> trans_; //Transitions of this state
        
  public:
            
  ///////Methods///////////        
    State();
    State(const State& cp);
    State(bool acept, int numtrans, string node, vector<Transition> trans);
    ~State();
    bool getacept(void) const;
    int getnumtrans(void) const;
    string getnode(void) const;
    vector<Transition> gettrans() const;
    void settrans(Transition const& element);
    void setacept(bool ac);
    void setnumtrans(int num);
    void setnode(string name);
    bool operator <(State const& b) const;
    bool operator ==(State const& b) const;
    bool operator >(State const& b) const;
    State& operator =(const State& b);
    vector<Transition>::iterator begini();
    vector<Transition>::iterator endi();
};
