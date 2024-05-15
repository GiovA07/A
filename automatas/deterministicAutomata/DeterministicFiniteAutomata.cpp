#include "DeterministicFiniteAutomata.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

DeterministicFiniteAutomata ::DeterministicFiniteAutomata() : k(), alphabet(), transitions(), q0(), f()
{
}

// Getters
set<set<int>> DeterministicFiniteAutomata::getK()
{
  return k;
}

set<int> DeterministicFiniteAutomata::getAlphabet()
{
  return alphabet;
}

map<pair<set<int>, int>, set<int>> DeterministicFiniteAutomata::getTransitions()
{
  return transitions;
}

set<int> DeterministicFiniteAutomata::getInitialState()
{
  return q0;
}

set<set<int>> DeterministicFiniteAutomata::getFinalStates()
{
  return f;
}

// Setters

void DeterministicFiniteAutomata ::setK(set<set<int>> k)
{
  this->k = k;
}

void DeterministicFiniteAutomata::setAlphabet(set<int> alphabet)
{
  this->alphabet = alphabet;
}

void DeterministicFiniteAutomata ::setTransitions(map<pair<set<int>, int>, set<int>> transitions)
{
  this->transitions = transitions;
}

void DeterministicFiniteAutomata::setInitialState(set<int> q0)
{
  this->q0 = q0;
}

void DeterministicFiniteAutomata::setFinalState(set<set<int>> finalStates)
{
  f = finalStates;
}

void DeterministicFiniteAutomata::addTransition(set<int> q, int r, set<int> destination)
{
  pair<set<int>, int> path = {q, r};
  auto it = transitions.find(path);
  if (it != transitions.end())
  {
    // La transición ya existe, actualizar el destino
    it->second = destination;
  }
  else
  {
    // La transición no existe, añadir una nueva
    transitions[path] = destination;
  }
}

void DeterministicFiniteAutomata::addState(set<int> state)
{
  this->k.insert(state);
}

void DeterministicFiniteAutomata::addFinalState(set<int> state)
{
  this->f.insert(state);
}

void DeterministicFiniteAutomata::addNewElementAlphabet(int element)
{
  this->alphabet.insert(element);
}

set<int> DeterministicFiniteAutomata ::getTransitionStates(pair<set<int>, int> key)
{
  if (transitions.find(key) != transitions.end())
  { // la transicion existe en el map?
    return transitions[key];
  }
  else
  {
    return {}; // sino existe devuelve conj vacio
  }
}

void DeterministicFiniteAutomata ::print()
{
  if (q0.empty())
  {
    std::cout << "El estado inicial es vacio." << std::endl;
  }
  else
  {
    for (const auto &conj : q0)
    {
      std::cout << "(" << conj << ",";
    }
    std::cout << ")" << std::endl;
  }

  cout << "El alfabeto es: {";
  for (const int &element : alphabet)
  {
    cout << element << ",";
  }
  cout << "}" << endl;

  cout << "Estados finales:" << endl;
  if (f.empty())
  {
    cout << "vacio xd" << endl;
  }
  for (const set<int> &finalState : f)
  {
    cout << "{";
    for (int state : finalState)
    {
      cout << state << ",";
    }
    cout << "}" << endl;
  }

  cout << "Las transiciones son: " << endl;
  map<pair<set<int>, int>, set<int>> miMapa = transitions;
  for (const auto &element : miMapa)
  {
    cout << "State: {";
    for (int num : element.first.first)
    {
      cout << num << " ";
    }
    cout << "}, by: " << element.first.second << " => {";
    for (int num : element.second)
    {
      cout << num << " ";
    }
    cout << "}" << endl;
  }
}

void DeterministicFiniteAutomata ::printEstados(set<set<set<int>>> aux)
{
  for (const set<set<int>> &finalState : aux)
  {
    cout << "{";
    for (set<int> state : finalState)
    {
      for (int elem : state)
      {
        cout << elem << ",";
      }
    }
    cout << "}" << endl;
  }
}

void DeterministicFiniteAutomata ::menu()
{
  while (true)
  {
    string nameFile;
    int option;
    cout << "Que Quieres Hacer?.\n";
    cout << "1- Mostrarlo por pantalla.\n";
    cout << "2- Escribirlo en un archivo.\n";
    cout << "3- Imprimir particiosn.\n";
    cout << "Cualquier otro numero VOLVER.\n";
    cout << "Ingresa el numero: ";
    cin >> option;
    set<set<set<int>>> aux;
    if (option != 1 && option != 2 && option != 3)
    {
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
      writeFile("../automataExamples/automataFD/" + nameFile + ".dot");
      break;
    case 3:
      aux = partition(*this);
    default:
      break;
    }
  }
}

void DeterministicFiniteAutomata ::readFile(std::string arch)
{

  ifstream archivo(arch);

  if (!archivo.is_open())
  {
    cerr << "Error al abrir el archivo" << endl;
    return;
  }
  // recorrer todal las lineas
  string linea;

  // expresion regular
  regex patron0("^digraph\\{");
  // expresion regular para buscar el estado inicial
  regex patron1("inic->\"([^\"]*)\";");

  // expresion regular  para buscar las transisicones
  regex patron2("\"([^\"]*)\"->\"([^\"]*)\"\\s*\\[label=\"([^\"]*)\"\\];");
  // expresion regular para buscar estados finales
  regex patron3("\"([^\"]*)\"\\[shape=doublecircle\\]");
  // consumo la ultima linea
  regex patron4("}");
  //
  regex patron5("rankdir=LR;");
  //
  regex patron6("inic\\[shape=point\\];");

  while (getline(archivo, linea))
  {
    if (!linea.empty())
    {

      if (regex_search(linea, patron0))
      {
      }
      else if (regex_search(linea, patron5))
      {
      }
      else if (regex_search(linea, patron6))
      {
      }
      else if (regex_search(linea, patron1))
      {
        smatch coincidencias;
        regex_search(linea, coincidencias, patron1);
        string valor = (coincidencias[1]);
        vector<int> numeros = stringNum(valor);
        set<int> aux;
        for (int num : numeros)
        {
          aux.insert(num);
        }
        this->addState(aux);
        this->setInitialState(aux);
      }
      else if (regex_search(linea, patron2))
      {
        smatch coincidencias;
        regex_search(linea, coincidencias, patron2);
        string inicio = (coincidencias[1]);

        vector<int> numerosInic = stringNum(inicio);
        set<int> auxInic;
        for (int num : numerosInic)
        {
          auxInic.insert(num);
        }
        this->addState(auxInic);

        string fin = (coincidencias[2]);
        vector<int> numerosFin = stringNum(fin);
        set<int> auxFin;
        for (int num : numerosFin)
        {
          auxFin.insert(num);
        }
        this->addState(auxFin);

        string estiquetas = (coincidencias[3]);
        vector<int> numeros = stringNum(estiquetas);
        for (int num : numeros)
        {
          if (num != 0)
            this->addNewElementAlphabet(num);
          this->addTransition(auxInic, num, auxFin);
        }
      }
      else if (regex_search(linea, patron3))
      {
        smatch coincidencias;
        regex_search(linea, coincidencias, patron3);
        string fin = (coincidencias[1]);
        vector<int> numeros = stringNum(fin);
        set<int> auxFin;
        for (int num : numeros)
        {
          auxFin.insert(num);
        }
        this->addFinalState(auxFin);
      }
      else if (regex_search(linea, patron4))
      {
      }
      else
      {
        std::cerr << "Error archivo incorrecto" << endl;
        return;
      }
    }
  }
  archivo.close();
}

vector<int> DeterministicFiniteAutomata ::stringNum(std::string cad)
{
  vector<int> numeros;
  // me crae subcadenas utilizando como delimitador la coma "," ejemplo  "22,3" => "22","3"
  istringstream sublis(cad);
  string subcad;
  // obtengo cada una de esas subcadenas separadas por coma
  while (getline(sublis, subcad, ','))
  {
    int numero;
    // cambio el tipo de subcadena a entero
    istringstream(subcad) >> numero;
    numeros.push_back(numero);
  }
  return numeros;
}

void DeterministicFiniteAutomata ::writeFile(std::string arch)
{
  std::ofstream archivo(arch);
  if (!archivo.is_open())
  {
    cerr << "Error al abrir el archivo" << endl;
    return;
  }
  archivo << "digraph{\n"
          << std::endl;
  archivo << "rankdir=LR;" << std::endl;
  archivo << "inic[shape=point];\n"
          << std::endl;
  archivo << "inic->\"";
  for (int num : this->getInitialState())
  {
    if (num == *this->getInitialState().rbegin())
    {
      archivo << num;
    }
    else
    {
      archivo << num << ",";
    }
  }
  archivo << "\";\n"
          << std::endl;

  map<pair<set<int>, set<int>>, set<int>> aux = getTransitionsWrite();

  for (const auto &clave : aux)
  {
    archivo << "\"";
    for (int numIni : clave.first.first)
    {
      if (numIni == *clave.first.first.rbegin())
      {
        archivo << numIni;
      }
      else
      {
        archivo << numIni << ",";
      }
    }
    archivo << "\"->\"";
    for (int numFin : clave.first.second)
    {
      if (numFin == *clave.first.second.rbegin())
      {
        archivo << numFin;
      }
      else
      {
        archivo << numFin << ",";
      }
    }
    archivo << "\" [label=\"";
    for (int num : clave.second)
    {
      if (num == *clave.second.rbegin())
      {
        archivo << num;
      }
      else
      {
        archivo << num << ",";
      }
    }
    archivo << "\"];" << std::endl;
  }

  archivo << "\n";
  for (const auto &num : this->getFinalStates())
  {
    archivo << "\"";
    for (int numConj : num)
    {

      if (numConj == *num.rbegin())
      {
        archivo << numConj;
      }
      else
      {
        archivo << numConj << ",";
      }
    }
    archivo << "\"[shape=doublecircle];" << std::endl;
  }
  archivo << "}" << std::endl;

  archivo.close();
}

map<pair<set<int>, set<int>>, set<int>> DeterministicFiniteAutomata ::getTransitionsWrite()
{
  map<pair<set<int>, set<int>>, set<int>> res;
  for (const auto &clave : this->getTransitions())
  {
    for (const auto &elem : clave.second)
    {
      pair<set<int>, set<int>> path = {clave.first.first, clave.second};
      res[path].insert(clave.first.second);
    }
  }
  return res;
}

//testWriteFile
set<set<set<int>>> DeterministicFiniteAutomata ::partition(DeterministicFiniteAutomata AFD1){
  // llevo la particion de estados inales y no finales
  DeterministicFiniteAutomata resultado;
  set<set<set<int>>> P, Pprisma;
  set<set<int>> X, Xprisma;
  set<set<int>> auxiliar;

  bool cambioPartition;
  P.insert(AFD1.getFinalStates());
  for (set<int> elem : AFD1.getK()) {
    bool aux = false; 
    // recorro los posibles conjuntos finales
    for(set<int> conj : AFD1.getFinalStates()) {      
     aux = aux || perteneceConjunto(elem, conj);
    }      
    if(!aux) {
      auxiliar.insert(elem);
    }
  }
  // inserto elementos que no son finales
  P.insert(auxiliar);
  /*for (set<set<int>> finalState : P){
    cout << "conj:" << endl;
    for (set<int> state : finalState){
      cout << "SubConjunto" << endl;
      for (int elem : state){
        cout << elem << endl;
      }
    }
  }*/
  //Pprisma.clear();
  cambioPartition = false;

  while (!cambioPartition)
  {
    Pprisma = P;

    for (set<set<int>> X : P) {
      for (set<int> e : X) {
        // si no lo encuentro
        // lo borro para simular marcacion
        //X.erase(e);

       /* bool valor = false;
        for(set<int> xprim : Xprisma) {  
          if (perteneceConjunto(e,xprim)) {
            valor = valor || true;
          }
        }
        // si encuntra que pertenece valor = true
        // yo solo li inseto si valo = false
        if(!valor) {
          Xprisma.insert(e);
        }
        */
        for (set<int> Eprisma : X) {
          //e != Eprisma &&
          if (e != Eprisma && equivalencia(e, Eprisma)) {
            //guardo conjuntos equivalenes en xprisma
            Xprisma.insert(e);
          }
        }

        //NO VA 
        //X = conjunto anterior {a,e,f}
        //Xprisma = {e,f}
      //  set<set<int>> aux3;
      //  for (set<int> elem : X) {
      //    bool aux = false; 
      //    // recorro los posibles conjuntos finales
      //    for(set<int> conj : Xprisma) {      
      //      aux = aux || perteneceConjunto(elem, conj);
      //    }      
      //    if(!aux) {
      //      aux3.insert(elem);
      //    }
      //  }
        
        if (X != Xprisma) {
          
          Pprisma.insert(Xprisma);
          Xprisma.clear();
        }
      }
    }

    if (P != Pprisma) {
      P = Pprisma;
    }
    else
    {
      cambioPartition = true;
    }
  }
  for (set<set<int>> finalState : P){
    for (set<int> state : finalState){
      cout << "conj:" << endl;
      for (int elem : state){
        cout << elem << endl;
      }
    }
  }

}

// retoorna false si no pertenece al conjunto;
bool DeterministicFiniteAutomata ::perteneceConjunto(set<int> conj1, set<int> conj2) {
  bool res = false;
  if(conj1.size() == conj2.size()) {
    res = true;
    for(int num : conj1) {
        if (conj2.find(num) != conj2.end()) {
          res = res && true;
        } else {
          res = res && false;
        }
    }
  }
  return res;
}


bool DeterministicFiniteAutomata ::equivalencia(set<int> estado1, set<int> estado2)
{
  for (int simbolo : this->getAlphabet())
  {
    set<int> proxEstado1 = this->getTransitionStates({estado1, simbolo});
    set<int> proxEstado2 = this->getTransitionStates({estado2, simbolo});
    if (proxEstado1 != proxEstado2)
    {
      return false;
    }
  }
  return true;
}

DeterministicFiniteAutomata DeterministicFiniteAutomata ::minimzation(DeterministicFiniteAutomata AFD1)
{
  DeterministicFiniteAutomata resultMinimized;
  set<set<set<int>>> partiAFD1 = partition(AFD1);
  set<set<int>> minimiStates;
  set<int> minimiq0;
  set<set<int>> minimif; // estados finales

  map<pair<set<int>, int>, set<int>> minimitransitions;

  // cambio los valores de los nuevos estados
  // set<int> newState = {1};
  /*  for (set<set<int>> parti : partiAFD1) {
      minimiStates.insert(*parti.begin());

      if(parti.count(AFD1.getInitialState())) {
        auto it = parti.begin();
        minimiq0.insert(static_cast<int>(*));
        break;
      }

      if(AFD1.getFinalStates().find(*parti.begin()) != AFD1.getFinalStates().end()) {
        minimif.insert(*parti.begin());
      }

      set<int> newState = *parti.begin();
          for (int symbol : AFD1.getAlphabet()) {
              std::set<int> nextStates;
              for (set<int> state : parti) {
                  set<int> nextState = partiAFD1.getTransitionStates({state, symbol});
                  if (nextState != -1) {
                      nextStates.insert(*partiAFD1.find(nextState)->begin());
                  }
              }
              if (!nextStates.empty()) {
                  minimitransitions[{newState, symbol}] = *nextStates.begin();
              }
          }
    }
  */

  resultMinimized.setAlphabet(AFD1.getAlphabet());

  for (set<set<int>> par : partiAFD1)
  {
    minimiStates.insert(*par.begin());
  }

  resultMinimized.setK(minimiStates);

  for (set<set<int>> par : partiAFD1)
  {
    if (AFD1.getFinalStates().find(*par.begin()) != AFD1.getFinalStates().end())
    {
      minimif.insert(*par.begin());
    }
  }
  resultMinimized.setFinalState(minimif);

  for (set<set<int>> par : partiAFD1)
  {
    for (int simbolo : resultMinimized.getAlphabet())
    {
    }
  }
  resultMinimized.setInitialState(minimiq0);
}

bool DeterministicFiniteAutomata ::pertenece(string s)
{
  set<int> alphabet = this->getAlphabet();

  map<pair<set<int>, int>, set<int>> transitions = this->getTransitions();
  set<int> q = this->getInitialState();
  bool result = true;

  for (size_t i = 0; i < s.length(); ++i)
  {
    char caracter = s[i];
    int element = caracter - '0';

    if (alphabet.find(element) != alphabet.end())
    {
      set<int> conjTransition = this->getTransitionStates({q, element});
      if (conjTransition.empty())
        return false;
      q.clear();
      for (int state : conjTransition)
      {
        q.insert(state); // Insertar cada estado de transition en q
      }
    }
    else
    {
      return false;
    }
  }

  set<set<int>> final_States = this->getFinalStates();
  if (final_States.find(q) == final_States.end())
    result = false;

  return result;
}
