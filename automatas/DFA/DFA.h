#ifndef DFA_H
#define DFA_H

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <utility> // Para std::pair
#include "../InterfaceFiniteAutomata.h"
#include <string>


using namespace std;

class DFA : public InterfaceFiniteAutomata {
private:
    set<int> k;                                     //Estados que hay en el automata
    set<int> alphabet;                              //el alfabeto
    map<pair<int,int>, int> transitions;            //transiciones de un estado a otro. Toma un estado y un elemento (pair)
    int q0;                                         //estado inicial
    set<int> f;                                     //estados finales

public:
    DFA();
    //geters
    set<int> getK();
    set<int> getAlphabet();
    map<pair<int,int>, int> getTransitions();
    int getInitialState();
    set<int> getFinalStates();
    //setters
    void setK(set<int> states);
    void setAlphabet(set<int> alphabet);
    void setTransitions(map<pair<int,int>, int> transitions);
    void setInitialState(int q);
    void setFinalState(set<int> final);

    //functions
    void addTransition(int q, int r, int destination);
    void addState(int state);
    void addFinalState(int state);
    void addNewElementAlphabet(int element);
    int getTransitionStates(pair<int, int> key);
    void readFile(string arch);
    void writeFile(string arch);
    map<pair<int,int>, set<int>> getTransitionsWrite();
    bool pertenece(string s);
    void menu();
    void print();

    DFA partition(DFA AFD1);
    bool equivalencia(set<set<int>> P, int state1, int state2);
    set<int> getParticionContainingStates(set<set<int>> P, int state);
};

#endif
