#include <iostream>
//#include "deterministicAutomata/DeterministicFiniteAutomata.cpp"
#include "notDeterministicFiniteAutomata/NotDeterministicFiniteAutomata.cpp"
#include "string"


int main() {

  string nameFile;
  int typeAutomata;
  while (true) {
        cout << "¿Que Automata Quiere Cargar? 1-No Deterministico 2-Deterministico: ";
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

            NotDeterministicFiniteAutomata ndfa;
            ndfa.readArchivo("../archivos_automatas/" + nameFile + ".dot");
            ndfa.menu();

        }else{

            DeterministicFiniteAutomata dfa;
            dfa.readFile("../archivos_automatas/" + nameFile + ".dot");
            dfa.menu();
        }
  }
  cout << "La ejecucion a terminado";
  return 0;
}
