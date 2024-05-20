#include "NDFA.h"


#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

const int LAMBDA = 0;
  //constructor
  NDFA :: NDFA() : k(), alphabet(), transitions(), q0(0), f() {
  }
  //getters
  set<int> NDFA :: getK() {
      return k;
  }

  set<int> NDFA :: getAlphabet() {
      return alphabet;
  }

  map<pair<int,int>, set<int>> NDFA :: getTransitions() {
    return transitions;
  }


  int NDFA :: getInitialState() {
      return q0;
  }


  set<int> NDFA :: getFinalStates() {
      return f;
  }

  //setters
  void NDFA :: setK(set<int> states) {
      this->k = states;
  }

  void NDFA :: setAlphabet(set<int> alphabet) {
      this->alphabet = alphabet;
  }

  void NDFA :: setTransitions(map<pair<int,int>, set<int>> transitions) {
      this->transitions = transitions;
  }

  void NDFA :: setInitialState(int q0) {
      this->q0 = q0;
  }

  void NDFA :: setFinalState(set<int> f) {
      this->f = f;
  }
  //functions
  void NDFA :: addTransition(int q, int r, int destination){
    if (k.find(q) != k.end() && k.find(q) != k.end()){
      pair<int, int> path = {q, r};
      transitions[path].insert(destination);
    } //SINO EXCEPCION...
  }

  void NDFA :: addState(int state){
    this->k.insert(state);
  }

  void NDFA :: addFinalState(int state){
    this->f.insert(state);
  }

  void NDFA :: addNewElementAlphabet(int element) {
    this->alphabet.insert(element);
  }

  set<int> NDFA :: getTransitionStates(pair<int,int> key) {
    if (this->transitions.find(key) != this->transitions.end()) { //la transicion existe en el map?
        return transitions[key];
    } else {
        return {}; //sino existe devuelve conj vacio
    }
  }

  void NDFA :: print() {
    cout << "El Estado inicial es: " << q0 << std::endl;

    cout << "El alfabeto es: {";
    for (const int& element : alphabet) {
        cout << element << ",";
    }
    cout << "}" << endl;


    for(const auto& elem: f) {
        cout << "El/Los Estados Finales son: " << elem <<endl;
    }

  // Copia del mapa original "transitions"
  map<pair<int, int>, set<int>> miMapa = transitions;
  if (transitions.empty()) {
        std::cout << "No Existe Ninguna Transicion" <<endl;
  } else {
      cout << "Las transiciones son: "<< endl;
      for (const auto& pair : miMapa) {
          const auto& state = pair.first;
          const auto& stateFinal = pair.second;

          // Imprimir la clave
          std::cout << "State: {" << state.first << "}" << " by: " << state.second;

          // Imprimir los valores
          std::cout << " => {";
          for (auto it = stateFinal.begin(); it != stateFinal.end(); ++it) {
              std::cout << *it;
              if (std::next(it) != stateFinal.end()) {
                  std::cout << ", ";
              }
          }
          std::cout << "}\n";
      }
  }
}

void NDFA :: menu() {
    while(true) {
        string nameFile;
        int option;
        cout << "Que Quieres Hacer?\n";
        cout << "1- Mostrarlo por pantalla.\n";
        cout << "2- Escribirlo en un archivo.\n";
        cout << "3- Tranformarlo en Deterministico.\n";
        cout << "4- Unirlo a otro automata No Deterministico.\n";
        cout << "5- Concatenar con otro automata.\n";
        cout << "6- Aplicar Clausura Klenne al automata.\n";
        cout << "Cualquier otro numero VOLVER.\n";
        cout << "Ingresa el numero: ";
        cin >> option;
        if (option < 1 || option > 6) {
            break;
        }
        NDFA ndfa2;
        NDFA newNDFA;
        DFA newDFA;
        set<int> set;
        AuxDFA dfa;
        switch (option)
        {
        case 1:
            print();
            break;
        case 2:
            cin.ignore();
            cout << "Ingrese el nombre del archivo (sin .dot) para escribir el automata: ";
            getline(cin, nameFile);
            writeFile("../automataExamples/automataFND/" + nameFile + ".dot");
            break;
        case 3:
            dfa = ndafToDfa();
            newDFA = dfa.convert();
            newDFA.menu();
            break;
        case 4:
            cin.ignore();
            cout << "Ingrese el nombre del archivo (sin .dot) para unirlo al automata: ";
            getline(cin, nameFile);
            ndfa2.readFile("../automataExamples/automataFND/" + nameFile + ".dot");
            newNDFA = unionAFDWithAFD(*this, ndfa2);
            newNDFA.menu();
            break;
        case 5:
            cin.ignore();
            cout << "Ingrese el nombre del archivo (sin .dot) para concatenarlo: ";
            getline(cin, nameFile);
            ndfa2.readFile("../automataExamples/automataFND/" + nameFile + ".dot");
            newNDFA = concatAFND(*this, ndfa2);
            newNDFA.menu();
            break;
        case 6:
            newNDFA = clausuKlenneAFND(*this);
            newNDFA.menu();
            break;
        default:
            break;
        }

        if(option == 3 || option == 4 || option == 5) {
            break;
        }
    }
}


  void NDFA:: readFile(string arch) {

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

map<pair<int,int>, set<int>> NDFA:: getTransitionsWrite(){

  map<pair<int,int>, set<int>> res;
  for(const auto&clave : this->getTransitions()) {
    for(const auto& elem :clave.second){
      pair<int,int> path = {clave.first.first,elem};
      res[path].insert(clave.first.second);
    }
  }
  return res;
}


void NDFA:: writeFile(string arch) {
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



set<int> NDFA :: lambdaClausure(set<int> state) {
    set<int> result;
    set<int> states_not_visited = state;
    set<int> states_visited;

    while(!states_not_visited.empty()) {
        int current_state = *states_not_visited.begin();
        states_not_visited.erase(current_state);
        states_visited.insert(current_state);

        result.insert(current_state);

         set<int> transition = getTransitionStates({current_state, LAMBDA});

         for(int stateTrans : transition) {
            result.insert(stateTrans);
            if (states_visited.find(stateTrans) == states_visited.end()) {
                states_not_visited.insert(stateTrans);
            }
            result.insert(stateTrans);
         }
    }
    return result;
}


set<int> NDFA :: move(set<int> conjState, int element) {
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


AuxDFA NDFA :: ndafToDfa() {
    AuxDFA dfa;

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

    //set estados
    dfa.setK(visitedStates);

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

NDFA NDFA::unionAFDWithAFD(NDFA AFND1, NDFA AFND2) {
  NDFA AFNDresult;
  //Union States
  set<int> newK = unionSets(AFND1.getK(), AFND2.getK());
  int newInit = busqueda(newK)+1; //TODO: podemos ver que no exista en el K para que sea el nuevo init
  AFNDresult.setInitialState(newInit);
  newK.insert(newInit);
  AFNDresult.setK(newK);
  //Union Alphabet
  AFNDresult.setAlphabet(unionSets(AFND1.getAlphabet(), AFND2.getAlphabet()));
  //New transitions
  AFNDresult.setTransitions(unionTransitions(AFND1.getTransitions(), AFND2.getTransitions()));
  AFNDresult.addTransition(newInit, LAMBDA, AFND1.getInitialState());
  AFNDresult.addTransition(newInit, LAMBDA, AFND2.getInitialState());

  int newFinalState = newInit + 1;
  set<int> finalState;
  finalState.insert(newFinalState);
  AFNDresult.setFinalState(finalState);

  for (int state : AFND1.getFinalStates()) {
    AFNDresult.addTransition(state, LAMBDA, newFinalState);
  }
  for (int state : AFND2.getFinalStates()) {
    AFNDresult.addTransition(state, LAMBDA, newFinalState);
  }
  return AFNDresult;
}

NDFA NDFA::concatAFND(NDFA AFND1, NDFA AFND2) {
  NDFA AFNDresult;
  //Union States
  set<int> newK = unionSets(AFND1.getK(), AFND2.getK());
  AFNDresult.setInitialState(AFND1.getInitialState());
  AFNDresult.setK(newK);
  //Union Alphabet
  AFNDresult.setAlphabet(unionSets(AFND1.getAlphabet(), AFND2.getAlphabet()));
  //New transitions
  AFNDresult.setTransitions(unionTransitions(AFND1.getTransitions(), AFND2.getTransitions()));

  int intermedioState = busqueda(newK)+1;
  AFNDresult.addState(intermedioState);

  for (int state : AFND1.getFinalStates()) {
    AFNDresult.addTransition(state, LAMBDA, intermedioState);
  }

  //Del Intermedio Agrego una transicion a el inicial del 2do
  AFNDresult.addTransition(intermedioState, LAMBDA, AFND2.getInitialState());

  int newFinalState = intermedioState + 1;
  AFNDresult.addState(newFinalState);
  AFNDresult.addFinalState(newFinalState);

  for (int state : AFND2.getFinalStates()) {
    AFNDresult.addTransition(state, LAMBDA, newFinalState);
  }
  return AFNDresult;
}

NDFA NDFA::clausuKlenneAFND(NDFA AFND1) {
  NDFA AFNDresult = AFND1;
  //The new Initial state
  int newInit = busqueda(AFNDresult.getK())+1;
  AFNDresult.setInitialState(newInit);
  AFNDresult.addState(newInit);
  AFNDresult.addTransition(newInit, LAMBDA, AFND1.getInitialState());
  //The new final state
  int newFinalState = newInit+1;
  set<int> finalState;
  finalState.insert(newFinalState);
  AFNDresult.addState(newFinalState);
  AFNDresult.setFinalState(finalState);
  for (int state : AFND1.getFinalStates()) {
    AFNDresult.addTransition(state, LAMBDA, newFinalState);
  }
  AFNDresult.addTransition(newInit, LAMBDA,newFinalState);
  AFNDresult.addTransition(newFinalState, LAMBDA,newInit);
  return AFNDresult;
}

set<int> NDFA :: unionSets(set<int> a1, set<int> a2) {
    set<int> unionSet;
    for (int simbol : a1) {
        unionSet.insert(simbol);
    }
    for (int simbol : a2) {
        unionSet.insert(simbol);
    }
    return unionSet;
}

map<pair<int,int>, set<int>> NDFA:: unionTransitions(map<pair<int,int>, set<int>> trans1, map<pair<int,int>, set<int>> trans2) {
      std::map<std::pair<int, int>, std::set<int>> resultMap;

    for (const auto& pair : trans1) {
        const auto& key = pair.first;
        const auto& set1 = pair.second;
        resultMap[key] = set1;
    }

    for (const auto& pair : trans2) {
        const auto& key = pair.first;
        const auto& set2 = pair.second;

        if (resultMap.find(key) != resultMap.end()) {
            resultMap[key] = unionSets(resultMap[key], set2);
        } else {
            resultMap[key] = set2;
        }
    }

    return resultMap;
}

int NDFA ::busqueda(set<int> k){
  int res = 0;
  for(int elem : k) {
    if (res < elem) {
      res = elem;
    }
  }
  return res;
}

