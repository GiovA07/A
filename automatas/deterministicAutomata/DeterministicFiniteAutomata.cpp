#include "DeterministicFiniteAutomata.h"

DeterministicFiniteAutomata :: DeterministicFiniteAutomata() : k(), alphabet(), transitions(), q0(), f() {
}

// Getters
set<set<int>> DeterministicFiniteAutomata::getK() {
    return k;
}

set<int> DeterministicFiniteAutomata::getAlphabet() {
    return alphabet;
}

map<pair<set<int>, int>, set<int>> DeterministicFiniteAutomata::getTransitions() {
    return transitions;
}

  set<int> DeterministicFiniteAutomata:: getInitialState() {
    return q0;
  }


set<set<int>> DeterministicFiniteAutomata::getFinalStates() {
    return f;
}

// Setters

void DeterministicFiniteAutomata :: setK(set<set<int>> k) {
    this->k = k;
}


void DeterministicFiniteAutomata::setAlphabet(set<int> alphabet) {
    this->alphabet = alphabet;
}

void DeterministicFiniteAutomata :: setTransitions(map<pair<set<int>,int>, set<int>> transitions) {
    this->transitions = transitions;
}


void DeterministicFiniteAutomata::setInitialState(set<int> q0) {
    this->q0 = q0;
}

void DeterministicFiniteAutomata::setFinalState(set<set<int>> finalStates) {
    f = finalStates;
}


void DeterministicFiniteAutomata::addTransition(set<int> q, int r, set<int> destination) {
    pair<set<int>, int> path = {q, r};
    transitions[path] = destination;
}


void DeterministicFiniteAutomata::addState(set<int> state) {
    this->k.insert(state);
}

void DeterministicFiniteAutomata::addFinalState(set<int> state) {
    this->f.insert(state);
}

void DeterministicFiniteAutomata::addNewElementAlphabet(int element) {
    this->alphabet.insert(element);
}


set<int> DeterministicFiniteAutomata :: getTransitionStates(pair<set<int>, int> key) {
    if (transitions.find(key) != transitions.end()) { //la transicion existe en el map?
        return transitions[key];
    } else {
        return {}; //sino existe devuelve conj vacio
    }
}







