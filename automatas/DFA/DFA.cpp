#include "DFA.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;


  DFA :: DFA() : k(), alphabet(), transitions(), q0(0), f() {
  }
  //getters
  set<int> DFA :: getK() {
      return k;
  }

  set<int> DFA :: getAlphabet() {
      return alphabet;
  }

  map<pair<int,int>, int> DFA :: getTransitions() {
    return transitions;
  }


  int DFA :: getInitialState() {
      return q0;
  }


  set<int> DFA :: getFinalStates() {
      return f;
  }

  //setters
  void DFA :: setK(set<int> states) {
      this->k = states;
  }

  void DFA :: setAlphabet(set<int> alphabet) {
      this->alphabet = alphabet;
  }

  void DFA :: setTransitions(map<pair<int,int>, int> transitions) {
      this->transitions = transitions;
  }

  void DFA :: setInitialState(int q0) {
      this->q0 = q0;
  }

  void DFA :: setFinalState(set<int> f) {
      this->f = f;
  }
  //functions
  void DFA :: addTransition(int q, int r, int destination){
    if (k.find(q) != k.end() && k.find(q) != k.end()){
      pair<int, int> path = {q, r};
      transitions[path] = destination;
    } //SINO EXCEPCION...
  }

  void DFA :: addState(int state){
    this->k.insert(state);
  }

  void DFA :: addFinalState(int state){
    this->f.insert(state);
  }

  void DFA :: addNewElementAlphabet(int element) {
    this->alphabet.insert(element);
  }

  int DFA :: getTransitionStates(pair<int,int> key) {
    if (this->transitions.find(key) != this->transitions.end()) { //la transicion existe en el map?
        return transitions[key];
    } else {
        return 0; //sino existe devuelve conj vacio
    }
  }

  void DFA ::menu()
{
  while (true)
  {
    string nameFile;
    int option;
    cout << "Que Quieres Hacer?.\n";
    cout << "1- Mostrarlo por pantalla.\n";
    cout << "2- Escribirlo en un archivo.\n";
    cout << "3- Ver si la cadena es reconocida por el automata.\n";
    cout << "4- Aplicar minimizacion al automata.\n";
    cout << "Cualquier otro numero VOLVER.\n";
    cout << "Ingresa el numero: ";
    cin >> option;
    DFA AFD;
    if (option < 1 && option > 4 )
      break;

    switch (option)
    {
    case 1:
      print();
      break;
    case 2:
      cin.ignore();
      cout << "Ingrese el nombre del archivo (sin .dot) para escribir el automata: ";
      getline(cin, nameFile);
      //writeFile("../automataExamples/automataFD/" + nameFile + ".dot");
      break;
    case 3:
      cin.ignore();
      cout << "Ingrese la cadena que quiere reconocer: ";
      getline(cin, nameFile);
      if(pertenece(nameFile)) {
        cout << "La Cadena " << nameFile << " fue aceptada \n";
      } else {
        cout << "La Cadena " << nameFile << " NO fue aceptada \n";
      }
      break;
    case 4:
      //AFD = partition(*this);
      AFD.menu();
      break;
    default:

      break;
    }
  }
}


  void DFA :: print() {
    cout << "El Estado inicial es: " << q0 << std::endl;

    cout << "El alfabeto es: {";
    for (const int& element : alphabet) {
        cout << element << ",";
    }
    cout << "}" << endl;


    for(const auto& elem: f) {
        cout << "El/Los Estados Finales son: " << elem <<endl;
    }

    //copia del mapa real
    map<pair<int, int>, int> miMapa = transitions;

    // Verificación si el mapa esta vacio o no ........
    if (transitions.empty()) {
        cout << "No Existe Ninguna Transicion" << endl;
    } else {
        cout << "Las transiciones son: " << endl;
        for (const auto& pair : miMapa) {
            const auto& state = pair.first;
            const auto& stateFinal = pair.second;

            // Imprimir la clave
            cout << "State: {" << state.first << ", " << state.second << "}";

            // Imprimir el valor
            cout << " => " << stateFinal << endl;
        }
    }
}


bool DFA ::pertenece(string s)
{
  set<int> alphabet = this->getAlphabet();
  map<pair<int, int>, int> transitions = this->getTransitions();
  int q = this->getInitialState();
  bool result = true;

  for (size_t i = 0; i < s.length(); ++i)
  {
    char caracter = s[i];
    int element = caracter - '0';

    if (alphabet.find(element) != alphabet.end()) {
      int state = this->getTransitionStates({q, element});
      cout << "par: {" << q << element<< "} =>" << state << "\n";
      if (state == 0)
        return false;
      q = state;
    } else {
      return false;
    }
  }

  set<int> final_States = this->getFinalStates();
  if (final_States.find(q) == final_States.end())
    result = false;

  return result;
}



