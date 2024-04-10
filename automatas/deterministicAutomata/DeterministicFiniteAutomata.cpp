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
    auto it = transitions.find(path);
    if (it != transitions.end()) {
        // La transición ya existe, actualizar el destino
        it->second = destination;
    } else {
        // La transición no existe, añadir una nueva
        transitions[path] = destination;
    }
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


void DeterministicFiniteAutomata :: readFile(std::string arch) {

}

void DeterministicFiniteAutomata :: writeFile(std::string arch) {

}




bool DeterministicFiniteAutomata :: pertenece(string s) {
    set<int> alphabet = this->getAlphabet();

    map<pair<set<int>,int>, set<int>> transitions = this->getTransitions();
    set<int> q = this->getInitialState();
    bool result = true;


    for (size_t i = 0; i < s.length(); ++i) {
        char caracter = s[i];
        int element = caracter - '0';

        if(alphabet.find(element) != alphabet.end()) {
            set<int> conjTransition = this->getTransitionStates({q,element});
            if(conjTransition.empty())
                return false;
            q.clear();
            for (int state : conjTransition) {
                q.insert(state); // Insertar cada estado de transition en q
            }

        } else {
            return false;
        }
    }

    set<set<int>> final_States = this->getFinalStates();
    if(final_States.find(q) == final_States.end())
        result = false;

    return result;
}






