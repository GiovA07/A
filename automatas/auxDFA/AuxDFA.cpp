#include "AuxDFA.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

AuxDFA ::AuxDFA() : k(), alphabet(), transitions(), q0(), f()
{
}

// Getters
set<set<int>> AuxDFA::getK()
{
  return k;
}

set<int> AuxDFA::getAlphabet()
{
  return alphabet;
}

map<pair<set<int>, int>, set<int>> AuxDFA::getTransitions()
{
  return transitions;
}

set<int> AuxDFA::getInitialState()
{
  return q0;
}

set<set<int>> AuxDFA::getFinalStates()
{
  return f;
}

// Setters

void AuxDFA ::setK(set<set<int>> k)
{
  this->k = k;
}

void AuxDFA::setAlphabet(set<int> alphabet)
{
  this->alphabet = alphabet;
}

void AuxDFA ::setTransitions(map<pair<set<int>, int>, set<int>> transitions)
{
  this->transitions = transitions;
}

void AuxDFA::setInitialState(set<int> q0)
{
  this->q0 = q0;
}

void AuxDFA::setFinalState(set<set<int>> finalStates)
{
  f = finalStates;
}

void AuxDFA::addTransition(set<int> q, int r, set<int> destination)
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

void AuxDFA::addState(set<int> state)
{
  this->k.insert(state);
}

void AuxDFA::addFinalState(set<int> state)
{
  this->f.insert(state);
}

void AuxDFA::addNewElementAlphabet(int element)
{
  this->alphabet.insert(element);
}

set<int> AuxDFA ::getTransitionStates(pair<set<int>, int> key)
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

void AuxDFA ::print()
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

void AuxDFA ::printEstados(set<set<set<int>>> aux)
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

void AuxDFA ::menu()
{
  while (true)
  {
    string nameFile;
    int option;
    cout << "Que Quieres Hacer?.\n";
    cout << "1- Mostrarlo por pantalla.\n";
    cout << "2- Escribirlo en un archivo.\n";
    cout << "3- Aplicar minimizacion al automata.\n";
    cout << "Cualquier otro numero VOLVER.\n";
    cout << "Ingresa el numero: ";
    cin >> option;
    AuxDFA AFD;
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
      AFD = partition(*this);
      AFD.menu();
    default:
      break;
    }
  }
}

void AuxDFA ::readFile(std::string arch)
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

vector<int> AuxDFA ::stringNum(std::string cad)
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

void AuxDFA ::writeFile(std::string arch)
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

map<pair<set<int>, set<int>>, set<int>> AuxDFA ::getTransitionsWrite()
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
AuxDFA AuxDFA ::partition(AuxDFA AFD1){
  // llevo la particion de estados inales y no finales
  AuxDFA resultado;
  set<set<set<int>>> P, Pprisma;
  set<set<int>> X, Xprisma;
  set<set<int>> auxiliar;

  bool cambioPartition;
  //Division entre estados finales y estados no finales.
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
  P.insert(auxiliar);

  //comienza la particion de las clases de eq
  cambioPartition = false;
  while (!cambioPartition) {
    //Pprisma = P;
    for (set<set<int>> X : P) {
      for (set<int> e : X) {
        Xprisma.insert(e);
        for (set<int> Eprisma : X) {
          if (e != Eprisma && (Xprisma.find(Eprisma) == Xprisma.end()) && equivalencia(P,e, Eprisma)) { //si no son iguales y Eprisma no pertenece al conjunto de los marcados y sus transiciones paran en la misma clase de eq
            Xprisma.insert(Eprisma);
          }
        }
        Pprisma.insert(Xprisma);
        Xprisma.clear();
      }
    }
      if (P != Pprisma) {
        P = Pprisma;
        Pprisma.clear();
      } else {
        cambioPartition = true;
      }
  }
  set<set<int>> Pauxilia;
  for(set<set<int>> el : P) {
    Pauxilia.insert(*el.begin());
  }
  for(set<int> el : Pauxilia) {
    resultado.addState(el);
  }

  /*for (set<int> state : resultado.getK()){
    cout << "Conjuntos" << endl;
    for (int elem : state){
      cout << elem << endl;
    }
  }*/

  for(set<int> el : Pauxilia) {
    if(perteneceConjunto(el,AFD1.getInitialState())) {
      resultado.setInitialState(el);
    }
  }

  /*cout << "Estado inicial"<< endl;
  for(int el : resultado.getInitialState()) {
    cout << el << ",";
  }
  cout << endl;
*/

  for(set<int> el1 : Pauxilia) {
      for(set<int> finallly : AFD1.getFinalStates()){
        if(perteneceConjunto(el1,finallly)) {
         resultado.addFinalState(el1);
        }
    }
  }

  /*cout << "Estados Finales"<< endl;
  for(set<int> el : resultado.getFinalStates()) {
    cout << "congFinal"<< endl;
    for (int finn : el) {
      cout << finn << ",";
    }
    cout << endl;
  }*/

  // agarro los estados de mi Particion de estados
  for (set<int> conjuntoEstado : Pauxilia) {
    for (int simbolo : AFD1.getAlphabet()) {
      // Obtenengo los alcanzables de mi nuvos estados
      set<int> proxEstado = AFD1.getTransitionStates({conjuntoEstado, simbolo});

      // Verificar si los estados alcanzables están en algún conjunto de Pauxilia
      for (set<set<int>> estadoDestino : P) {
        for(set<int> ef : estadoDestino) {
          if ((perteneceConjunto(proxEstado,ef))) {
              // Agregar la transición al autómata resultado
              resultado.addTransition(conjuntoEstado, simbolo, *estadoDestino.begin());
          }
        }
      }
    }
  }

  /*cout << "Las transiciones son: " << endl;
  map<pair<set<int>, int>, set<int>> miMapa = resultado.getTransitions();
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
*/

/*
for (set<set<int>> finalState : P){
    cout << "conj:" << endl;
    for (set<int> state : finalState){
      cout << "SubConjunto" << endl;
      for (int elem : state){
        cout << elem << endl;
      }
    }
  }*/
  return resultado;
}

// retoorna false si no pertenece al conjunto;
bool AuxDFA ::perteneceConjunto(set<int> conj1, set<int> conj2) {
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


bool AuxDFA ::equivalencia(set<set<set<int>>> P, set<int> estado1, set<int> estado2) {
  for (int simbolo : this->getAlphabet()) {
    set<int> proxEstado1 = this->getTransitionStates({estado1, simbolo});
    set<int> proxEstado2 = this->getTransitionStates({estado2, simbolo});
    set<set<int>> particion = getParticionContainingStates(P, proxEstado1);

    if (particion.find(proxEstado2) != particion.end()) {
      return false;
    }
  }
  return true;
}

set<set<int>> AuxDFA:: getParticionContainingStates(const set<set<set<int>>>& P, const set<int>& estados){
    for (const auto& particion : P) {
        if (particion.find(estados) != particion.end()) {
            return particion;
        }
    }
    return {};
}
/*
AuxDFA AuxDFA ::minimzation(AuxDFA AFD1)
{
  AuxDFA resultMinimized;
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
*/
bool AuxDFA ::pertenece(string s)
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


DFA AuxDFA::convert() {
    DFA newDFA;
    map<set<int>, int> stateMapping;
    int stateId = 1;
    set<int> newStates;

    for (const auto& state : k) {
        stateMapping[state] = stateId;
        newStates.insert(stateId);
        stateId++;
    }

    newDFA.setK(newStates);

    // Set new alphabet
    newDFA.setAlphabet(alphabet);

    // Set new transitions
    map<pair<int, int>, int> newTransitions;
    for (const auto& trans : transitions) {
        const pair<set<int>, int>& key = trans.first;
        const set<int>& value = trans.second;
        int newSrcState = stateMapping[key.first];
        newTransitions[{newSrcState, key.second}] = stateMapping[value];
    }
    newDFA.setTransitions(newTransitions);

    newDFA.setInitialState(stateMapping[q0]);

    set<int> newFinalStates;
    for (const auto& finalState : f) {
        newFinalStates.insert(stateMapping[finalState]);
    }
    newDFA.setFinalState(newFinalStates);

    return newDFA;
}


