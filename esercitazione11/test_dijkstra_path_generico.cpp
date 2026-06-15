#include <iostream>
#include <vector>
#include <cmath>
#include "undirected_graph.hpp"
#include "dijkstra_path.hpp"

int main() {
	//test su grafo lineare
	undirected_graph<int> G1;
	
	G1.add_edge(1,2);
	G1.add_edge(2,3);
	G1.add_edge(3,4);
	
	auto res1 = dijkstra_path(G1, 1, 4);
	double tol = 1e-12; //uso la tolleranza per confrontare double
	
	//controllo che le distanze calcolate siano giuste
	if (std::abs(res1.dist[1] - 0.0) > tol ) {
		std::cerr << "ERRORE: la distanza della sorgente da se stessa è errata\n";
		return EXIT_FAILURE;
	}
	if (std::abs(res1.dist[2] - 1.0) > tol ) {
		std::cerr << "ERRORE: la distanza del nodo 2 è errata\n";
		return EXIT_FAILURE;
	}
	if (std::abs(res1.dist[3] - 2.0) > tol ) {
		std::cerr << "ERRORE: la distanza del nodo 3 è errata\n";
		return EXIT_FAILURE;
	}
	if (std::abs(res1.dist[4] - 3.0) > tol ) {
		std::cerr << "ERRORE: la distanza del nodo 4 è errata\n";
		return EXIT_FAILURE;
	}
	//controllo che il cammino sia quello giusto
	auto path1 = get_shortest_path(G1, 1, 4);
	if (path1 != std::vector<int>{1,2,3,4}) {
		std::cerr << "ERRORE: cammino G1 non corretto\n";
		return EXIT_FAILURE;
	}
	
	
	//test su grafo con più cammini minimi
	undirected_graph<int> G2;
	G2.add_edge(1,2);
	G2.add_edge(1,3);
	G2.add_edge(3,4);
	G2.add_edge(4,5);
	G2.add_edge(2,5);
	//cerco il percorso minimo da 1 a 5 (mi deve restituire 1-2-5)
	auto path2 = get_shortest_path(G2, 1, 5);
	//controllo che gli estremi siano giusti
	if (path2[0] != 1 || path2[2] != 5) {
		std::cerr << "ERRORE: gli estremi del cammino sono errati\n";
		return EXIT_FAILURE;
	}
	//controllo la lunghezza del cammino
	if (path2.size() != 3) {
		std::cerr << "ERRORE: il cammino trovato non corrisponde a quello minimo\n";
		return EXIT_FAILURE;
	}
	//controllo che sia il cammino giusto 
	if (path2 != std::vector<int>{1,2,5}) {
		std::cerr << "ERRORE: il cammino G2 è errato\n";
		return EXIT_FAILURE;
	}
	
	//test su grafo con un nodo inesistente
	undirected_graph<int> G3;
	G3.add_edge(1,2);
	G3.add_edge(2,3);
	
	auto path3 = get_shortest_path(G3, 1, 5);
	if (!path3.empty()) {
		std::cerr << "ERRORE: il nodo 5 non esiste, il cammino dovrebbe essere vuoto\n";
		return EXIT_FAILURE;
	}
	
	//test nel caso in cui il nodo target sia irraggiungibile
	undirected_graph<int> G4;
	G4.add_edge(1,2);
	G4.add_edge(6,7);
	//verifico che la distanza tra 2 e 7 sia infinita
	auto res4 = dijkstra_path(G4, 2, 7);
	if (res4.dist[7] != std::numeric_limits<double>::infinity()) {
		std::cerr << "ERRORE: la distanza di un nodo non raggiungibile deve essere infinita\n";
		return EXIT_FAILURE;
	}
	//verifico che get_shortes_path restituisca un cammino vuoto
	auto path4 = get_shortest_path(G4, 2, 7);
		if (!path4.empty()) {
			std::cerr << "ERRORE: il cammino dovrebbe essere vuoto\n";
			return EXIT_FAILURE;
		}
			
	
	
	//test nel caso in cui sorgente == arrivo
	auto path5 = get_shortest_path(G1, 2, 2);
	if (path5.size() != 1 || path5[0] != 2) {
		std::cerr << "ERRORE: il caso s == t non è gestito correttamente\n";
		return EXIT_FAILURE;
	}
	std::cout << "Tutti i test sono stati superati con successo\n";
	return EXIT_SUCCESS;
}
	