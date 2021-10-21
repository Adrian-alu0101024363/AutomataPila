
#include "../headers/State.h";

//Default constructor
State::State(void):
  acept_(0),
  numtrans_(0),
  node_("empty")//,
  //trans_()
{}
//Copy Constructor
State::State(const State& cp) {  
  *this = cp;
}
//Constructor with paramethers
State::State(bool acept, int numtrans, string node, vector<Transition> trans):
  acept_(acept),
  numtrans_(numtrans),
  node_(node),
  trans_(trans)
{}

//Destructor 
State::~State(void) {}

//Set a transition for the state
void State::settrans(Transition const& element) {
  trans_.push_back(element);
}
//Get if the state is a acept state or not
bool State::getacept(void) const {
  return acept_;
}
//Get the number of transition of the state
int State::getnumtrans(void) const {
  return numtrans_;
}
//Get the state name information
string State::getnode(void) const {
  return node_;
}
//Get the set of transition aka all the transition of the state
vector<Transition> State::gettrans() const {
  return trans_;
}
//Set a state as an acept state or not
void State::setacept(bool ac) {
  acept_ = ac;
}
//Set the number of transition that the state has
void State::setnumtrans(int num) {
  numtrans_ = num;
}
//Set the node information aka the name or keyword
void State::setnode(string name) {
  node_ = name;
}

//Iterator to the begining of the transition set
vector<Transition>::iterator State::begini(void) {
    
  return trans_.begin();
    
}
//Iterator to the end of the transition set
vector<Transition>::iterator State::endi(void) {
    
  return trans_.end();
    
}

//Operator overload

bool State::operator ==(State const& b) const {         
  return((getnode() == b.getnode())&&(getnumtrans() == b.getnumtrans())&&(getacept() == b.getacept())&&(gettrans()==b.gettrans()));
}
bool State::operator >(State const& b) const {
    
  string aux = getnode();
    
  string aux2 = b.getnode();
    
  return (aux > aux2);
    
}

State& State::operator =(const State& b) {
    
  this->acept_ = b.getacept();
    
  this->numtrans_ = b.getnumtrans();
    
  this->node_ = b.getnode();
    
  this->trans_ = b.gettrans();
    
  return *this;
    
}

bool State::operator <(State const& b) const {
    
  string aux = getnode();
    
  string aux2 = b.getnode();
    
  return (aux < aux2);
    
}
