#ifndef AFND_H
#define AFND_H

#include <vector>
#include <map>
#include <set>
#include <utility> // Para std::pair
#include "../InterfaceFiniteAutomata.h"
#include "../deterministicAutomata/DeterministicFiniteAutomata.h"
#include <string>

using namespace std;

class NotDeterministicFiniteAutomata : public InterfaceFiniteAutomata {
private:
    set<int> k;                                     //Estados que hay en el automata
    set<int> alphabet;                              //el alfabeto
    map<pair<int,int>, set<int>> transitions;       //transiciones de un estado a otro. Toma un estado y un elemento (pair)
    int q0;                                         //estado inicial
    set<int> f;                                     //estados finales

public:
    NotDeterministicFiniteAutomata();
    //geters
    set<int> getK();
    set<int> getAlphabet();
    map<pair<int,int>, set<int>> getTransitions();
    int getInitialState();
    set<int> getFinalStates();
    //setters
    void setK(set<int> states);
    void setAlphabet(set<int> alphabet);
    void setTransitions(map<pair<int,int>, set<int>> transitions);
    void setInitialState(int q);
    void setFinalState(set<int> final);

    //functions
    void addTransition(int q, int r, int destination);
    void addState(int state);
    void addFinalState(int state);
    void addNewElementAlphabet(int element);
    set<int> getTransitionStates(pair<int, int> key);
    void readArchivo(std::string archivo);

    DeterministicFiniteAutomata nfaToDfa();

private:
    set<int> lambdaClausure(set<int> state, map<pair<int, int>, set<int>> transitions);
    set<int> move(set<int> state, int element);
};

#endif
