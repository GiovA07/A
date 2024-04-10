#include <iostream>
//#include "deterministicAutomata/DeterministicFiniteAutomata.cpp"
#include "notDeterministicFiniteAutomata/NotDeterministicFiniteAutomata.cpp"
#include "string"


int main() {
    NotDeterministicFiniteAutomata automata;

    //automata.setInitialState(10);

    //cargo archivo que voi a leer
    automata.readArchivo("../archivos_automatas/automata.dot");


    // para ver si el estado inicial esta correcto
    std::cout << "Es :" << automata.getInitialState() << std::endl;

    cout << "El alfabeto es: {";
    for (const int& element : automata.getAlphabet()) {
        cout << element << ",";
    }
    cout << "}" << endl;


  auto estadosFinal = automata.getFinalStates();


  // para ver si se cargo bien el estado final
  for(const auto& elem: estadosFinal) {
    std::cout << "Estado final" << elem << std::endl;
  }



 // Obtener el mapa de transiciones
  auto mapaTransiciones = automata.getTransitions();

  // Verificar si el mapa está vacío
  if (mapaTransiciones.empty()) {
      std::cout << "El mapa de transiciones está vacío." << std::endl;
  } else {
      // Iterar sobre el mapa e imprimir cada par clave-valor
      for (const auto& par : mapaTransiciones) {
          // Imprimir la clave (un par)
          //for(const auto& est :par.first.second) {
            std::cout << "((" << par.first.first << ", " << par.first.second << ")";
          //}
          // Imprimir el conjunto de valores
          //std::cout << "Valores:";
          for (const auto& valor : par.second) {
              std::cout << " " << valor << ")";
          }
          std::cout << std::endl;
      }
  }

  //escribo el automata en un archivo
  automata.writeArchivo("../archivos_automatas/automataWrite2.dot");

    DeterministicFiniteAutomata aux = automata.ndafToDfa();
    std::cout << "------------ DETERMINISTICO ------------" << std::endl;
          if(aux.getInitialState().empty() ){

            std::cout << "El mapa de transiciones está vacío." << std::endl;

          }else {


          for (const auto& conj : aux.getInitialState()) {
            std::cout << "(" << conj << ",";
          }
        std::cout << ")" << std::endl;
        }





      cout << "El alfabeto es: {";
      for (const int& element : aux.getAlphabet()) {
          cout << element << ",";
      }
      cout << "}" << endl;

          // Mostrar estados finales
      cout << "Estados finales:" << endl;
      if(aux.getFinalStates().empty()) {
        cout << "vacio xd" << endl;
      }


      for (const set<int>& finalState : aux.getFinalStates()) {
          cout << "{";
          for (int state : finalState) {
              cout << state << ",";
          }
          cout << "}" << endl;
      }


        set<set<int>> estados = aux.getK();

        // Mostrar el contenido del conjunto de estados
        cout << "Estados que hay en el autómata:" << endl;
        for (const auto& estado : estados) {
            cout << "{";
            for (int valor : estado) {
                cout << valor << ", ";
            }
            cout << "}" << endl;
        }

    cout << "Las transiciones:" << endl;
    map<pair<set<int>, int>, set<int>> miMapa = aux.getTransitions();
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

    set<int> q = aux.getInitialState();
    q = aux.getTransitionStates({q, 7});


    cout << aux.pertenece("76666") << " Es el resultado de la cadena \n";
      return 0;
}
