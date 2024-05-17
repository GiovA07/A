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
      writeFile("../automataExamples/automataFD/" + nameFile + ".dot");
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

  void DFA :: readFile(string arch) {
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
                if (num != 0)
                  this->addNewElementAlphabet(num);
                this->addTransition(inicio,num,fin);
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

  void DFA :: writeFile(string arch) {
  std::ofstream archivo(arch);
  if(!archivo.is_open()) {
    cerr << "Error al abrir el archivo" << endl;
  return;
  }
  archivo << "digraph{\n" << std::endl;
  archivo << "rankdir=LR;" << std::endl;
  archivo << "inic[shape=point];\n" << std::endl;
  archivo << "inic->" << this->getInitialState()<< ";\n"<< std::endl;
  map<pair<int,int>, set<int>> res = this->getTransitionsWrite();

  for(const auto&clave : res) {
    archivo << clave.first.first << "->" << clave.first.second <<" [label=\"";
    for(const auto& elem : clave.second) {
      if(elem == *clave.second.rbegin()){
      archivo << elem;
      } else {
        archivo << elem << ", ";
      }

    }
    archivo << "\"];" << std::endl;

  }

  for(const auto& num : this->getFinalStates()) {
    archivo << "\n" << num << "[shape=doublecircle];" << std::endl;
  }
  archivo << "}" << std::endl;

  archivo.close();

}


map<pair<int,int>, set<int>> DFA ::getTransitionsWrite(){
  map<pair<int,int>, set<int>> res;
  for(const auto&clave : this->getTransitions()) {
      pair<int,int> path = {clave.first.first,clave.second};
      res[path].insert(clave.first.second);
  }
  return res;
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



