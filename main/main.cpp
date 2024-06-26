#include <iostream>

#include "../automatas/notDeterministicFiniteAutomata/NDFA.cpp"
#include "../automatas/auxDFA/AuxDFA.cpp"
#include "../automatas/DFA/DFA.cpp"
#include "string"
using namespace std;


int main() {
  string nameFile;
  int typeAutomata;

  while (true) {
        cout << "Que Automata Quiere Cargar? \n 1-No Deterministico \n 2-Deterministico \n Cualquier otro numero SALIR del PROGRAMA \n Ingresa el numero:  ";
        cin >> typeAutomata;

        if (typeAutomata != 1 && typeAutomata != 2) {
            break;
        }
        cin.ignore();
        cout << "Ingrese el nombre del archivo (sin .dot) que contiene el Automata (o presione Enter para salir): ";
        getline(cin, nameFile);
        if (nameFile.empty()) {
          break;
        }

        if (typeAutomata == 1) {

            NDFA ndfa;
            ndfa.readFile("../automataExamples/automataFND/" + nameFile + ".dot");
            ndfa.menu();

        }else{

            DFA dfa;
            dfa.readFile("../automataExamples/automataFD/" + nameFile + ".dot");
            dfa.menu();
        }
  }
  cout << "La ejecucion a terminado";
  return 0;
}
