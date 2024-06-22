#include "Simulation.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = filesystem;

void Simulation::simulation() {
    int x;
    int array[7];

    for (int i = 0; i < 7; i++) {
        cout << "Podaj rozmiar grafu " << i + 1 << endl;
        cin >> x;
        array[i] = x;
    }

    // Upewnienie się, że katalog 'Files' istnieje
    fs::create_directories(fs::current_path() / "Files");

    for (int x : array) {

        // Mst gestosc 25%
        for (int i = 0; i < 50; i++) {
            Graph graph(x, 0);
            Algorithm algorithm(graph);
            graph.generateGraph(0, 0.25, 100000);

            ofstream file;
            // Prim list
            string filename = fs::current_path().string() + "//Files" + "//" + "pL25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.primList() << endl;
            file.close();

            // Prim matrix
            filename = fs::current_path().string() + "//Files" + "//" + "pM25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.matrixPrim() << endl;
            file.close();

            // Krusk list
            filename = fs::current_path().string() + "//Files" + "//" + "kL25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.kruskList() << endl;
            file.close();

            // Krusk matrix
            filename = fs::current_path().string() + "//Files" + "//" + "kM25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.matrixKrusk() << endl;
            file.close();
        }

        // Mst gestosc 50%
        for (int i = 0; i < 50; i++) {
            Graph graph(x, 0);
            Algorithm algorithm(graph);
            graph.generateGraph(0, 0.5, 100000);

            ofstream file;
            // Prim list
            string filename = fs::current_path().string() + "//Files" + "//" + "pL50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.primList() << endl;
            file.close();

            // Prim matrix
            filename = fs::current_path().string() + "//Files" + "//" + "pM50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.matrixPrim() << endl;
            file.close();

            // Krusk list
            filename = fs::current_path().string() + "//Files" + "//" + "kL50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.kruskList() << endl;
            file.close();

            // Krusk matrix
            filename = fs::current_path().string() + "//Files" + "//" + "kM50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.matrixKrusk() << endl;
            file.close();
        }

        // Mst gestosc 99%
        for (int i = 0; i < 50; i++) {
            Graph graph(x, 0);
            Algorithm algorithm(graph);
            graph.generateGraph99(0, 100000);

            ofstream file;
            // Prim list
            string filename = fs::current_path().string() + "//Files" + "//" + "pL99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.primList() << endl;
            file.close();

            // Prim matrix
            filename = fs::current_path().string() + "//Files" + "//" + "pM99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.matrixPrim() << endl;
            file.close();

            // Krusk list
            filename = fs::current_path().string() + "//Files" + "//" + "kL99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.kruskList() << endl;
            file.close();

            // Krusk matrix
            filename = fs::current_path().string() + "//Files" + "//" + "kM99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.matrixKrusk() << endl;
            file.close();
        }

        // Najkrotsza sciezka gestosc 25%
        for (int i = 0; i < 50; i++) {
            Graph graph(x, 1);
            Algorithm algorithm(graph);
            graph.generateGraph(1, 0.25, 100000);

            int start, end;
            while (true) {
                start = rand() % x;
                end = rand() % x;
                if (start != end) {
                    break;
                }
            }

            ofstream file;
            // Dijkstra list
            string filename = fs::current_path().string() + "//Files" + "//" + "dL25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.dijkstraList(start, end) << endl;
            file.close();

            // Dijkstra matrix
            filename = fs::current_path().string() + "//Files" + "//" + "dM25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.dijkstraMatrix(start, end) << endl;
            file.close();

            // B-Ford list
            filename = fs::current_path().string() + "//Files" + "//" + "bfL25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.bellmanFordList(start, end) << endl;
            file.close();

            // B-Ford matrix
            filename = fs::current_path().string() + "//Files" + "//" + "bfM25.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.bellmanFordMatrix(start, end) << endl;
            file.close();
        }

        // Najkrotsza sciezka gestosc 50%
        for (int i = 0; i < 50; i++) {
            Graph graph(x, 1);
            Algorithm algorithm(graph);
            graph.generateGraph(1, 0.5, 100000);

            int start, end;
            while (true) {
                start = rand() % x;
                end = rand() % x;
                if (start != end) {
                    break;
                }
            }

            ofstream file;
            // Dijkstra list
            string filename = fs::current_path().string() + "//Files" + "//" + "dL50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.dijkstraList(start, end) << endl;
            file.close();

            // Dijkstra matrix
            filename = fs::current_path().string() + "//Files" + "//" + "dM50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.dijkstraMatrix(start, end) << endl;
            file.close();

            // B-Ford list
            filename = fs::current_path().string() + "//Files" + "//" + "bfL50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.bellmanFordList(start, end) << endl;
            file.close();

            // B-Ford matrix
            filename = fs::current_path().string() + "//Files" + "//" + "bfM50.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.bellmanFordMatrix(start, end) << endl;
            file.close();
        }

        // Najkrotsza sciezka gestosc 99%
        for (int i = 0; i < 50; i++) {
            Graph graph(x, 1);
            Algorithm algorithm(graph);
            graph.generateGraph99(1, 100000);

            int start, end;
            while (true) {
                start = rand() % x;
                end = rand() % x;
                if (start != end) {
                    break;
                }
            }

            ofstream file;
            // Dijkstra list
            string filename = fs::current_path().string() + "//Files" + "//" + "dL99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.dijkstraList(start, end) << endl;
            file.close();

            // Dijkstra matrix
            filename = fs::current_path().string() + "//Files" + "//" + "dM99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.dijkstraMatrix(start, end) << endl;
            file.close();

            // B-Ford list
            filename = fs::current_path().string() + "//Files" + "//" + "bfL99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.bellmanFordList(start, end) << endl;
            file.close();

            // B-Ford matrix
            filename = fs::current_path().string() + "//Files" + "//" + "bfM99.txt";
            file.open(filename, ios_base::app);
            if (!file.is_open()) {
                cerr << "Nie udało się otworzyć pliku: " << filename << endl;
            }
            file << algorithm.bellmanFordMatrix(start, end) << endl;
            file.close();
        }
    }
}
