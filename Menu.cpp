#include "Menu.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

void Menu::menu() {
    int choice, type;
    string filename;
    Graph graph(0, 0, 0);
    Algorithm algorithm(graph);

    while (true) {
        cout << "Wybierz jedna z podanych opcji:\n";
        cout << " 1. Algorytm MST\n";
        cout << " 2. Algorytm najkrotszej sciezki\n";
        cout << "-1. Wroc do wyboru trybu\n";
        cin >> type;
        switch (type) {
            case 1:
                while (true) {
                    cout << "Wybierz jedna z podanych opcji:\n";
                    cout << "1. Wczytaj dane z pliku\n";
                    cout << "2. Wygeneruj graf losowo\n";
                    cout << "3. Wyswietl graf listowo i macierzowo na ekranie\n";
                    cout << "4. Rozwiaz algorytmem Prima listowo\n";
                    cout << "5. Rozwiaz algorytmem Prima macierzowo\n";
                    cout << "6. Rozwiaz algorytmem Kruskala listowo\n";
                    cout << "7. Rozwiaz algorytmem Kruskala macierzowo\n";
                    cout << "8. Wybor algorytmu\n";

                    cin >> choice;
                    switch (choice) {
                        case 1:
                        {
                            cout << "Podaj nazwe pliku:" << endl;
                            cin >> filename;
                            string filepath = fs::current_path().string() + "/Files/" + filename;
                            try {
                                ifstream file(filepath);
                                if (!file.is_open()) {
                                    cerr << "Nie mozna otworzyc pliku " << filepath << endl;
                                    throw runtime_error("Nie mozna otworzyc pliku");
                                }
                                string firstLine;
                                int n1, m, position = 0;
                                getline(file, firstLine);
                                istringstream iss(firstLine);
                                iss >> n1 >> m;
                                graph = Graph(n1, m, 0);
                                graph.initializeList();
                                graph.initializeMatrix();

                                string line;
                                while (getline(file, line)) {
                                    int v1, v2, weight;
                                    istringstream iss2(line);
                                    iss2 >> v1 >> v2 >> weight;
                                    graph.addMatrix(v1, v2, position, weight);
                                    graph.addList(v1, v2, weight);
                                    graph.edges.addEdge(position, v1, v2);
                                    position++;
                                }
                                file.close();

                            } catch (const runtime_error& e) {
                                cerr << "Wystapil blad: " << e.what() << endl;
                            }
                        }
                            break;
                        case 2:
                            int density, n;
                            cout << "Podaj ilosc wierzcholkow:\n";
                            cin >> n;
                            while (true) {
                                cout << "Wybierz gestosc grafu\n";
                                cout << "1. Gestosc 25%\n";
                                cout << "2. Gestosc 50%\n";
                                cout << "3. Gestosc 99%\n";
                                cin >> density;
                                if (density == 1 || density == 2 || density == 3) {
                                    break;
                                }
                            }
                            if (density == 1) {
                                graph = Graph(n, 0);
                                graph.initializeList();
                                graph.initializeMatrix();
                                graph.generateGraph(0, 0.25, 999);
                            } else if (density == 2) {
                                graph = Graph(n, 0);
                                graph.initializeList();
                                graph.initializeMatrix();
                                graph.generateGraph(0, 0.5, 999);
                            } else {
                                graph = Graph(n, 0);
                                graph.initializeList();
                                graph.initializeMatrix();
                                graph.generateGraph99(0, 999);
                            }
                            break;
                        case 3:
                            graph.displayList();
                            graph.displayMatrix();
                            break;
                        case 4:
                            cout << algorithm.primList() << " ms\n";
                            break;
                        case 5:
                            cout << algorithm.matrixPrim() << " ms\n";
                            break;
                        case 6:
                            cout << algorithm.kruskList() << " ms\n";
                            break;
                        case 7:
                            cout << algorithm.matrixKrusk() << " ms\n";
                            break;
                        case 8:
                            break;
                        default:
                            cout << "Podano zly numer.\n";
                            break;
                    }
                    if (choice == 8)
                        break;
                }
                break;
            case 2:
                while (true) {
                    cout << "Wybierz jedna z podanych opcji:\n";
                    cout << "1. Wczytaj dane z pliku\n";
                    cout << "2. Wygeneruj graf losowo\n";
                    cout << "3. Wyswietl graf listowo i macierzowo na ekranie\n";
                    cout << "4. Rozwiaz algorytmem Dijkstry listowo\n";
                    cout << "5. Rozwiaz algorytmem Dijkstry macierzowo\n";
                    cout << "6. Rozwiaz algorytmem Bellmana-Forda listowo\n";
                    cout << "7. Rozwiaz algorytmem Bellmana-Forda macierzowo\n";
                    cout << "8. Wybor algorytmu\n";

                    cin >> choice;
                    switch (choice) {
                        case 1:
                        {
                            cout << "Podaj nazwe pliku:" << endl;
                            cin >> filename;
                            string filepath = fs::current_path().string() + "/Files/" + filename;
                            try {
                                ifstream file(filepath);
                                if (!file.is_open()) {
                                    cerr << "Nie mozna otworzyc pliku " << filepath << endl;
                                    throw runtime_error("Nie mozna otworzyc pliku");
                                }
                                string firstLine;
                                int n1, m, position = 0;
                                getline(file, firstLine);
                                istringstream iss(firstLine);
                                iss >> n1 >> m;
                                graph = Graph(n1, m, 1);
                                graph.initializeList();
                                graph.initializeMatrix();

                                string line;
                                while (getline(file, line)) {
                                    int v1, v2, weight;
                                    istringstream iss2(line);
                                    iss2 >> v1 >> v2 >> weight;
                                    graph.addMatrix(v1, v2, position, weight);
                                    graph.addList(v1, v2, weight);
                                    graph.edges.addEdge(position, v1, v2);
                                    position++;
                                }
                                file.close();

                            } catch (const runtime_error& e) {
                                cerr << "Wystapil blad: " << e.what() << endl;
                            }
                        }
                            break;
                        case 2:
                            int density, n;
                            cout << "Podaj ilosc wierzcholkow:\n";
                            cin >> n;
                            while (true) {
                                cout << "Wybierz gestosc grafu\n";
                                cout << "1. Gestosc 25%\n";
                                cout << "2. Gestosc 50%\n";
                                cout << "3. Gestosc 99%\n";
                                cin >> density;
                                if (density == 1 || density == 2 || density == 3) {
                                    break;
                                }
                            }
                            if (density == 1) {
                                graph = Graph(n, 1);
                                graph.initializeList();
                                graph.initializeMatrix();
                                graph.generateGraph(1, 0.25, 999);
                            } else if (density == 2) {
                                graph = Graph(n, 1);
                                graph.initializeList();
                                graph.initializeMatrix();
                                graph.generateGraph(1, 0.5, 999);
                            } else {
                                graph = Graph(n, 1);
                                graph.initializeList();
                                graph.initializeMatrix();
                                graph.generateGraph99(1, 999);
                            }
                            break;
                        case 3:
                            graph.displayList();
                            graph.displayMatrix();
                            break;
                        case 4:
                            int start, end;
                            while (true) {
                                cout << "Podaj wierzcholek startowy:";
                                cin >> start;
                                if (start < 0 || start > n - 1) {
                                    cout << "Wierzcholek startowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                cout << "Podaj wierzcholek koncowy: ";
                                cin >> end;
                                if (end < 0 || end > n - 1) {
                                    cout << "Wierzcholek koncowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                break;
                            }

                            cout << algorithm.dijkstraList(start, end) << " ms\n";
                            break;
                        case 5:
                            while (true) {
                                cout << "Podaj wierzcholek startowy:";
                                cin >> start;
                                if (start < 0 || start > n - 1) {
                                    cout << "Wierzcholek startowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                cout << "Podaj wierzcholek koncowy: ";
                                cin >> end;
                                if (end < 0 || end > n - 1) {
                                    cout << "Wierzcholek koncowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                break;
                            }
                            cout << algorithm.dijkstraMatrix(start, end) << " ms\n";
                            break;
                        case 6:
                            while (true) {
                                cout << "Podaj wierzcholek startowy:";
                                cin >> start;
                                if (start < 0 || start > n - 1) {
                                    cout << "Wierzcholek startowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                cout << "Podaj wierzcholek koncowy: ";
                                cin >> end;
                                if (end < 0 || end > n - 1) {
                                    cout << "Wierzcholek koncowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                break;
                            }
                            cout << algorithm.bellmanFordList(start, end) << " ms\n";
                            break;
                        case 7:
                            while (true) {
                                cout << "Podaj wierzcholek startowy:";
                                cin >> start;
                                if (start < 0 || start > n - 1) {
                                    cout << "Wierzcholek startowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                cout << "Podaj wierzcholek koncowy: ";
                                cin >> end;
                                if (end < 0 || end > n - 1) {
                                    cout << "Wierzcholek koncowy musi znajdowac sie w przedziale od 0 do " << n << endl;
                                    continue;
                                }
                                break;
                            }
                            cout << algorithm.bellmanFordMatrix(start, end) << " ms\n";
                            break;
                        case 8:
                            break;
                        default:
                            cout << "Podano zly numer.\n";
                            break;
                    }
                    if (choice == 8)
                        break;
                }
                break;
            case -1:
                return;
            default:
                cout << "Podano zly numer\n";
                break;
        }
    }
}
