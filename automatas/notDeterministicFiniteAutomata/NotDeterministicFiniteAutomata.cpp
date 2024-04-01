#include "NotDeterministicFiniteAutomata.h"
using namespace std;

  NotDeterministicFiniteAutomata :: NotDeterministicFiniteAutomata() : k(), alphabet(), transitions(), q0(0), f() {
  }

  set<int> NotDeterministicFiniteAutomata :: getK() {
      return k;
  }

  set<int> NotDeterministicFiniteAutomata :: getAlphabet() {
      return alphabet;
  }

  map<pair<int,int>, set<int>> NotDeterministicFiniteAutomata :: getTransitions() {
    return transitions;
  }


  int NotDeterministicFiniteAutomata :: getInitialState() {
      return q0;
  }


  set<int> NotDeterministicFiniteAutomata :: getFinalStates() {
      return f;
  }

  void NotDeterministicFiniteAutomata :: setK(set<int> states) {
      this->k = states;
  }

  void NotDeterministicFiniteAutomata :: setAlphabet(set<int> alphabet) {
      this->alphabet = alphabet;
  }

  void NotDeterministicFiniteAutomata :: setTransitions(map<pair<int,int>, set<int>> transitions) {
      this->transitions = transitions;
  }

  void NotDeterministicFiniteAutomata :: setInitialState(int q0) {
      this->q0 = q0;
  }

  void NotDeterministicFiniteAutomata :: setFinalState(set<int> f) {
      this->f = f;
  }

  void NotDeterministicFiniteAutomata :: addTransition(int q, int r, int destination){
    if (k.find(q) != k.end() && k.find(q) != k.end()) {
      pair<int, int> path = {q, r};
      transitions[path].insert(destination);
    } //SINO EXCEPCION...
  }

  void NotDeterministicFiniteAutomata :: addState(int state){
    this->k.insert(state);
  }

  void NotDeterministicFiniteAutomata :: addFinalState(int state){
    this->f.insert(state);
  }

  void NotDeterministicFiniteAutomata :: addNewElementAlphabet(int element) {
    this->alphabet.insert(element);
  }

  set<int> NotDeterministicFiniteAutomata :: getTransitionStates(pair<int,int> key) {
    if (transitions.find(key) != transitions.end()) { //la transicion existe en el map?
        return transitions[key];
    } else {
        return {}; //sino existe devuelve conj vacio
    }
  }
