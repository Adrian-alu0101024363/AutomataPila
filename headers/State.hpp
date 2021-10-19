
  #include <string>

  #include "../headers/Transition.hpp"

  class State {
    private:

      //VARIABLES//
      bool acept_;    //Is an acept state or not
      int numtrans_;  //Number of transition for state
      string node_;    //State,node name identifier
      set<Transition> trans_; //Transitions of this state
        
    public:
            
    ///////Methods///////////        
      State();
      State(const State& cp);
      State(bool acept, int numtrans, string node, set<Transition> trans);
      ~State();
      bool getacept(void) const;
      int getnumtrans(void) const;
      string getnode(void) const;
      set<Transition> gettrans() const;
      void settrans(Transition const& element);
      void setacept(bool ac);
      void setnumtrans(int num);
      void setnode(string name);
      bool operator <(State const& b) const;
      bool operator ==(State const& b) const;
      bool operator >(State const& b) const;
      State& operator =(const State& b);
      set<Transition>::iterator begini();
      set<Transition>::iterator endi();
};
