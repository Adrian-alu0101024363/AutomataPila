
  #include "../headers/Transition.hpp"

  using namespace std;

 //Default constructor
  Transition::Transition():
    simbol_(),
    nextnode_("None")
  {}
  //Copy constructor
  Transition::Transition(const Transition& cp) {
    // simbolo_(cp.getsimb()),
    // nododestino_(cp.getdestino())
    *this = cp;
  }
  //Constructor with paremethers
  Transition::Transition(string simbol, string extract, string nextnode, vector<string> insert):
    simbol_(simbol),
    nextnode_(nextnode),
    extract_(extract),
    insert_(insert)
  {}

  //Getter and setter of class atributes
  string Transition::getsimb() const {
    return simbol_;
  }

  string Transition::getdestination() const {
    return nextnode_;
  }
  string Transition::getExtract() const {
    return extract_;
  }
  vector<string> Transition::getInsert() const {
    return insert_;
  }
  void Transition::setsimb(string element) {
    simbol_ = element;
  }

  void Transition::setdestination(string destination) {
    nextnode_ = destination;
  }
  void Transition::setExtract(string extract) {
    extract_ = extract;
  }
  void Transition::setInsert(vector<string> insert) {
    insert_ = insert;
  }
  //Operators overload 

  bool Transition::operator<(Transition const& b) const {
    string aux = getsimb(); 
    string aux2 = b.getsimb(); 
    if(aux == aux2) {
      return (getdestination() < b.getdestination());
    } else {
      return (aux < aux2);
    }
    
  }

  bool Transition::operator==(Transition const& b) const {
    string aux = getsimb();
    string aux2 = b.getsimb();
    string aux3 = getdestination();
    string aux4 = b.getdestination();
    return ( (aux3 == aux4) && (aux == aux2) );
  }

  bool Transition::operator>(Transition const& b) const {
    string aux = getsimb();
    string aux2 = b.getsimb();
    return (aux > aux2);  
  }

  Transition& Transition::operator=(const Transition& b) {
    this->simbol_ = b.getsimb();
    this->nextnode_ = b.getdestination();
    this->extract_ = b.getExtract();
    this->insert_ = b.getInsert();
    return *this;  
  }

