
  #pragma once //For applying libraries just once
  #include <iostream> 
  #include <fstream> 
  #include <vector> 
  #include <string> 
  #include <algorithm> 
  #include <iterator>
  #include <set>

  using namespace std; 

  class Transition {
    private:
 
      ////VARIABLES////   
      string simbol_; //The char of the transition
      string nextnode_; //The destination node to transit to
      string extract_;
      vector<string> insert_;
        
    public:
    
    ///////////Methods/////////
        
      Transition();
        
      Transition(const Transition& cp);
        
      Transition(string simbol, string extract, string nextnode, vector<string> insert);
        
      string getsimb() const;
        
      string getdestination() const;

      string getExtract() const;
        
      vector<string> getInsert() const; 

      void setsimb(string element);
        
      void setdestination(string destination);

      void setExtract(string extract);

      void setInsert(vector<string> insert);
        
      bool operator<(Transition const& b) const;
        
      bool operator==(Transition const& b) const;
        
      bool operator>(Transition const& b) const;
        
      Transition& operator=(Transition const& b);      

  };
