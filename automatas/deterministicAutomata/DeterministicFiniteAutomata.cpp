#include "DeterministicFiniteAutomata.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

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

void DeterministicFiniteAutomata :: print() {
    if(q0.empty() ){
        std::cout << "El estado inicial es vacio." << std::endl;

    }else {
        for (const auto& conj : q0) {
            std::cout << "(" << conj << ",";
        }
            std::cout << ")" << std::endl;
    }

    cout << "El alfabeto es: {";
     for (const int& element : alphabet) {
         cout << element << ",";
     }
    cout << "}" << endl;

    cout << "Estados finales:" << endl;
    if(f.empty()) {
      cout << "vacio xd" << endl;
    }
    for (const set<int>& finalState : f) {
        cout << "{";
        for (int state : finalState) {
            cout << state << ",";
        }
        cout << "}" << endl;
    }

    cout << "Las transiciones son: " << endl;
    map<pair<set<int>, int>, set<int>> miMapa = transitions;
    // Recorrer el mapa y mostrar cada elemento
    for (const auto& elemento : miMapa) {
        cout << "Clave: {";
        for (int num : elemento.first.first) {
            cout << num << " ";
        }
        cout << "}, " << elemento.first.second << " => {";
        for (int num : elemento.second) {
            cout << num << " ";
        }
        cout << "}" << endl;
    }
}

void DeterministicFiniteAutomata :: menu() {
    while(true) {
        string nameFile;
        int option;
        cout << "Que Quieres Hacer?.\n";
        cout << "1- Mostrarlo por pantalla.\n";
        cout << "2- Escribirlo en un archivo.\n";
        cout << "Cualquier otro numero SALIR.\n";
        cout << "Ingresa el numero: ";
        cin >> option;
        if (option != 1 && option != 2) {
            break;
        }

        switch (option)
        {
        case 1:
            print();
            break;
        case 2:
            cin.ignore();
            cout << "Ingrese el nombre del archivo (sin .dot) para escribir el automata: ";
            getline(cin, nameFile);
            writeFile("../archivos_automatas/" + nameFile + ".dot");
            break;
        default:
            break;
        }
    }
}


void DeterministicFiniteAutomata :: readFile(std::string arch) {

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
    regex patron1("inic->\"([^\"]*)\";");

    // expresion regular  para buscar las transisicones
    regex patron2("\"([^\"]*)\"->\"([^\"]*)\"\\s*\\[label=\"([^\"]*)\"\\];");
    // expresion regular para buscar estados finales
    regex patron3("\"([^\"]*)\"\\[shape=doublecircle\\]");
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
              string valor = (coincidencias[1]);
              vector<int> numeros = stringNum(valor);
              set<int> aux;
              for(int num : numeros) {
                aux.insert(num);
              }
              this->addState(aux);
              this->setInitialState(aux);
        }else if(regex_search(linea,patron2)){
              smatch coincidencias;
              regex_search(linea, coincidencias, patron2);
              string inicio =(coincidencias[1]);

              vector<int> numerosInic = stringNum(inicio);
              set<int> auxInic;
                for(int num : numerosInic) {
                auxInic.insert(num);
              }
              this->addState(auxInic);

              string fin =(coincidencias[2]);
              vector<int> numerosFin = stringNum(fin);
              set<int> auxFin;
                for(int num : numerosFin) {
                auxFin.insert(num);
              }
              this->addState(auxFin);

              string estiquetas =(coincidencias[3]);
              vector<int> numeros = stringNum(estiquetas);
              for(int num : numeros){
                if (num != 0)
                  this->addNewElementAlphabet(num);
                this->addTransition(auxInic,num,auxFin);
              }

        }else if(regex_search(linea,patron3)){
              smatch coincidencias;
              regex_search(linea, coincidencias, patron3);
              string fin = (coincidencias[1]);
              vector<int> numeros = stringNum(fin);
              set<int> auxFin;
              for(int num : numeros){
                auxFin.insert(num);
              }
              this->addFinalState(auxFin);

        }else if(regex_search(linea,patron4)){

        }else{
        std::cerr << "Error archivo incorrecto" << endl;
        return;
      }
    }

  }
    archivo.close();
}

vector<int> DeterministicFiniteAutomata :: stringNum(std::string cad) {
    vector<int> numeros;
    //me crae subcadenas utilizando como delimitador la coma "," ejemplo  "22,3" => "22","3"
    istringstream sublis(cad);
    string subcad;
    //obtengo cada una de esas subcadenas separadas por coma
    while (getline(sublis, subcad, ',')) {
      int numero;
      //cambio el tipo de subcadena a entero
      istringstream(subcad) >> numero;
      numeros.push_back(numero);
    }
    return numeros;
}

void DeterministicFiniteAutomata :: writeFile(std::string arch) {
  std::ofstream archivo(arch);
  if(!archivo.is_open()) {
    cerr << "Error al abrir el archivo" << endl;
  return;
  }
  archivo << "digraph{\n" << std::endl;
  archivo << "rankdir=LR;" << std::endl;
  archivo << "inic[shape=point];\n" << std::endl;
  archivo << "inic->\"";
  for(int num : this->getInitialState()) {
    if(num == *this->getInitialState().rbegin()){
      archivo << num;
      } else {
        archivo << num << ",";
      }
  }
  archivo << "\";\n"<< std::endl;

  map<pair<set<int>,set<int>>, set<int>> aux = getTransitionsWrite();

  for(const auto&clave : aux) {
  archivo << "\"";
    for(int numIni : clave.first.first) {
      if(numIni == *clave.first.first.rbegin()){
        archivo << numIni;
      } else {
        archivo << numIni << ",";
      }
    }
    archivo << "\"->\"" ;
    for(int numFin : clave.first.second) {
      if(numFin == *clave.first.second.rbegin()){
        archivo << numFin;
      } else {
        archivo << numFin << ",";
      }
    }
    archivo <<"\" [label=\"";
    for(int num : clave.second){
        if(num == *clave.second.rbegin()){
          archivo << num;
        } else {
           archivo << num << ",";
        }
    }
    archivo << "\"];" << std::endl;
    }

    archivo << "\n";
    for(const auto& num : this->getFinalStates()) {
    archivo << "\"";
     for(int numConj : num) {

      if(numConj == *num.rbegin()){
        archivo << numConj;
      } else {
        archivo << numConj << ",";
      }
     }
     archivo << "\"[shape=doublecircle];" << std::endl;
    }
    archivo << "}" << std::endl;

    archivo.close();

}

map<pair<set<int>,set<int>>, set<int>> DeterministicFiniteAutomata :: getTransitionsWrite(){
   map<pair<set<int>,set<int>>, set<int>> res;
   for(const auto&clave : this->getTransitions()) {
     for(const auto& elem :clave.second){
        pair<set<int>,set<int>> path = {clave.first.first,clave.second};
        res[path].insert(clave.first.second);
     }
   }
   return res;
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






