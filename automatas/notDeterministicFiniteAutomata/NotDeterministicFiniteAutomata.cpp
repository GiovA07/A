#include "NotDeterministicFiniteAutomata.h"
#include "../deterministicAutomata/DeterministicFiniteAutomata.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

const int LAMBDA = 0;

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
    if (k.find(q) != k.end() && k.find(q) != k.end()){
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

  void NotDeterministicFiniteAutomata:: readArchivo(string arch) {

    ifstream archivo(arch);

    if(!archivo.is_open()) {
      cerr << "Error al abrir el archivo" << endl;
      return;
    }
    // recorrer todal las lineas
    string linea;

    //expresion regular
    regex patron0("^digraph\\{");
    // expresion regular para buscar el estado inicial
    regex patron1("inic->([0-9]+);");
    // expresion regular  para buscar las transisicones
    regex patron2("([0-9]+)->([0-9]+)\\s*\\[label=\"([^\"]*)\"\\];");
    // expresion regular para buscar estados finales
    regex patron3("([0-9]+)\\[shape=doublecircle\\]");
    //consumo la ultima linea
    regex patron4("}");
    //
    regex patron5("rankdir=LR;");
    //
    regex patron6("inic\\[shape=point\\];");


    while(getline(archivo, linea)) {
      if(!linea.empty()){

        if(regex_search(linea,patron0)){

        }else if(regex_search(linea,patron5)){

        }else if(regex_search(linea,patron6)){

        }
        else if(regex_search(linea,patron1)){
              smatch coincidencias;
              regex_search(linea, coincidencias, patron1);
              int valor = stoi(coincidencias[1]);
              this->addState(valor);
              this->setInitialState(valor);
        }else if(regex_search(linea,patron2)){
              smatch coincidencias;
              regex_search(linea, coincidencias, patron2);
              int inicio = stoi(coincidencias[1]);
              this->addState(inicio);
              int fin = stoi(coincidencias[2]);
              this->addState(fin);

              string estiquetas =(coincidencias[3]);
              vector<int> numeros;
              //me crae subcadenas utilizando como delimitador la coma "," ejemplo  "22,3" => "22","3"
              istringstream sublis(estiquetas);
              string subcad;
              //obtengo cada una de esas subcadenas separadas por coma
              while (getline(sublis, subcad, ',')) {
                int numero;
                //cambio el tipo de subcadena a entero
                istringstream(subcad) >> numero;
                numeros.push_back(numero);
              }

              for(int num : numeros){
                this->addTransition(inicio,fin,num);
              }

        }else if(regex_search(linea,patron3)){
              smatch coincidencias;
              regex_search(linea, coincidencias, patron3);
              int fin = stoi(coincidencias[1]);
              this->addFinalState(fin);
        }else if(regex_search(linea,patron4)){

        }else{
        std::cerr << "Error archivo incorrecto" << endl;
        return;
      }
    }

  }
    archivo.close();
  }



set<int> NotDeterministicFiniteAutomata :: lambdaClausure(set<int> state) {
    set<int> result;
    set<int> states_not_visited = state;
    set<int> states_visited;

    while(!states_not_visited.empty()) {
        int current_state = *states_not_visited.begin();
        states_not_visited.erase(current_state);
        states_visited.insert(current_state);

         set<int> transition = getTransitionStates({current_state, LAMBDA});

         for(int state : transition) {
            result.insert(state);
            if (states_visited.find(state) == states_visited.end()) {
                states_not_visited.insert(state);
            }
         }
    }
    return result;
}


set<int> NotDeterministicFiniteAutomata :: move(set<int> conjState, int element) {
    set<int> result;

    for (int state : conjState) {
        set<int> transition = getTransitionStates({state, element});
        if(!transition.empty()) {
            //inserta todo elemento de la transicion
            for(int s : transition) {
                result.insert(s);
            }
        }
    }
    return result;
}


DeterministicFiniteAutomata NotDeterministicFiniteAutomata :: ndafToDfa() {
    DeterministicFiniteAutomata dfa = *new DeterministicFiniteAutomata;

    //otorgandole el alfabeto
    dfa.setAlphabet(this->alphabet);

    //creando conj inicial
    set<int> initialState;
    initialState.insert(this->q0);
    set<int> auxSet= lambdaClausure(initialState);
    initialState.insert(auxSet.begin(),auxSet.end());
    dfa.setInitialState(initialState);

    //faltan visitar
    queue<set<int>> pendingStates;
    pendingStates.push(initialState);

    // ya visitados
    set<set<int>> visitedStates;
    visitedStates.insert(initialState);


    while (!pendingStates.empty()) {
        set<int> currentState = pendingStates.front();
        pendingStates.pop();

        for (int element : this->alphabet) {
            set<int> newState = move(currentState, element);
            newState = lambdaClausure(newState);

            //si el nuevo estado no es vacio significa que va haber una transicion.
            if(!newState.empty()) {
                dfa.addTransition(currentState, element, newState);

                //si el nuevo estado no fue visitado entonces agregarlo.
                if (visitedStates.find(newState) == visitedStates.end()) {
                        pendingStates.push(newState);
                        visitedStates.insert(newState);
                }
            }
        }
    }


    //setear los final state
    set<set<int>> finalStates;
    for (set<int> state : visitedStates) {
        for(int fStateNDA : this->f) {
            if(state.find(fStateNDA) != state.end()) {
                finalStates.insert(state);
            }
        }
    }

    dfa.setFinalState(finalStates);

    return dfa;
}
