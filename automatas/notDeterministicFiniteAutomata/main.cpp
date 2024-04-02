#include <iostream>
#include "NotDeterministicFiniteAutomata.h"
#include "NotDeterministicFiniteAutomata.cpp"
#include "string"

int main() {
    NotDeterministicFiniteAutomata automata;
    //automata.setInitialState(10);

    //cargo archivo que voi a leer
    automata.readArchivo("../../archivos_automatas/automata.dot");


    // para ver si el estado inicial esta correcto
    std::cout << "Estado inicia :" << automata.getInitialState() << std::endl;
    



  auto estadosFinal = automata.getFinalStates();


  // para ver si se cargo bien el estado final
  for(const auto& elem: estadosFinal) {
    std::cout << "Estado final :" << elem << std::endl;
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
          std::cout << "((" << par.first.first << ", " << par.first.second << ")";

          // Imprimir el conjunto de valores
          //std::cout << "Valores:";
          for (const auto& valor : par.second) {
              std::cout << " " << valor << ")";
          }
          std::cout << std::endl;
      }
  }

      return 0;
}
