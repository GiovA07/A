#ifndef AuxDFA_H
#define AuxDFA_H

#include <vector>
#include <map>
#include <set>
#include <utility> // Para std::pair
#include <string>
#include "../DFA/DFA.h"

using namespace std;

class AuxDFA {
private:
    set<set<int>> k;                                     //Estados que hay en el automata
    set<int> alphabet;                              //el alfabeto
    map<pair<set<int>,int>, set<int>> transitions;       //transiciones de un estado a otro. Toma un estado y un elemento (pair)
    set<int> q0;                                         //estado inicial
    set<set<int>> f;                                     //estados finales

public:
    AuxDFA();
    //geters
    set<set<int>> getK();
    set<int> getAlphabet();
    map<pair<set<int>,int>, set<int>> getTransitions();
    set<int> getInitialState();
    set<set<int>>getFinalStates();

    //setters
    void setK(set<set<int>> states);
    void setAlphabet(set<int> alphabet);
    void setTransitions(map<pair<set<int>,int>, set<int>> transitions);
    void setInitialState(set<int> q0);
    void setFinalState(set<set<int>> final);

    //functions
    void addTransition(set<int> q, int r, set<int> destination);
    void addState(set<int> state);
    void addFinalState(set<int> state);
    void addNewElementAlphabet(int element);
    set<int> getTransitionStates(pair<set<int>, int> key);

    void readFile(std::string arch);
    void writeFile(std::string arch);
    void print();
    void menu();
    bool pertenece(string s);
    AuxDFA minimzation(AuxDFA AFD1);
    AuxDFA partition(AuxDFA AFD1);
    void printEstados(set<set<set<int>>> aux);

    DFA convert();
private:
    bool perteneceConjunto(set<int> conj1, set<int> conj2);
    vector<int> stringNum(std::string cad);
    map<pair<set<int>,set<int>>, set<int>> getTransitionsWrite();
    bool equivalencia(set<set<set<int>>> P, set<int> estado1, set<int> estado2);
    set<set<int>> getParticionContainingStates(const set<set<set<int>>>& P, const set<int>& estados);

};

#endif
