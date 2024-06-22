#include "Graph.h"
#include "Menu.h"
#include "Simulation.h"


using namespace std;

int main() {
    srand(time(nullptr));
    int choice;
    while(true){
        cout << "Wybierz opcje:\n";
        cout << " 1. Menu\n";
        cout << " 2. Symulacja\n";
        cout << "-1. Koniec programu\n";
        cin >> choice;
        if(choice == 1){
            Menu::menu();
        }
        if(choice == 2){
            Simulation::simulation();
        }
        if(choice == -1){
            return 0;
        }
    }
}
