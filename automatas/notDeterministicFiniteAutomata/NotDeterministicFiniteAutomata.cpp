#include "NotDeterministicFiniteAutomata.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

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

  void NotDeterministicFiniteAutomata:: readArchivo(std::string arch) {
    
    std::ifstream archivo(arch);

    if(!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo" << std::endl;
      return;
    }
    // recorrer todal las lineas
    std::string linea;
    
    //expresion regular
    std::regex patron0("^digraph\\{");
    // expresion regular para buscar el estado inicial
    std::regex patron1("inic->([0-9]+);"); 
    // expresion regular  para buscar las transisicones
    std::regex patron2("([0-9]+)->([0-9]+)\\s*\\[label=\"([^\"]*)\"\\];");
    // expresion regular para buscar estados finales
    std::regex patron3("([0-9]+)\\[shape=doublecircle\\]");
    //consumo la ultima linea
    std::regex patron4("}");
    //
    std::regex patron5("rankdir=LR;");
    //
    std::regex patron6("inic\\[shape=point\\];");

    
    while(std::getline(archivo, linea)) {
      if(!linea.empty()){        
        
        if(std::regex_search(linea,patron0)){

        }else if(std::regex_search(linea,patron5)){

        }else if(std::regex_search(linea,patron6)){

        }
        else if(std::regex_search(linea,patron1)){
              std::smatch coincidencias;
              std::regex_search(linea, coincidencias, patron1);
              int valor = std::stoi(coincidencias[1]);
              this->addState(valor);
              this->setInitialState(valor);
        }else if(std::regex_search(linea,patron2)){
              std::smatch coincidencias;
              std::regex_search(linea, coincidencias, patron2);
              int inicio = std::stoi(coincidencias[1]);
              this->addState(inicio);
              int fin = std::stoi(coincidencias[2]);
              this->addState(fin);
              int valor = std::stoi(coincidencias[3]);
              this->addTransition(inicio,fin,valor);
        }else if(std::regex_search(linea,patron3)){
              std::smatch coincidencias;
              std::regex_search(linea, coincidencias, patron3);
              int fin = std::stoi(coincidencias[1]);
              this->addFinalState(fin);
        }else if(std::regex_search(linea,patron4)){
              
        }else{ 
        std::cerr << "Error archivo incorrecto" << endl;
        return;
      }
    }

  }
    archivo.close();
  }
