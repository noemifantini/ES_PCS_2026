#include <iostream>
#include "grafi_netlist.hpp"
#include "netlist.hpp"
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include <string>
#include <vector>

int main() {
	//test della funzione leggi_circuito:
    //estraggo una netlist con read_file, uso netlist_prova.txt
	//V1 30.0 1 4 
	//V2 40.0 3 5
    //R1 4.0  4 2
    //R2 10.0 1 2
    //R3 30.0 1 3
    //R4 10.0 3 2
    //R5 4.0 2 5
	
	const char* argv1[] = {"test1", "netlist_prova.txt"};
	/*nel file netlist_prova.txt ci sono degli spazi bianchi e delle righe saltate*/
    int argc1 = std::size(argv1);
    auto result1 = read_file(argc1, argv1);
    if(!result1.has_value()) {
		std::cerr << "ERRORE: lettura del file fallita\n";
		return EXIT_FAILURE;
	}
	//leggo il circuito
	circuito C = *result1;
	//controllo che il grafo non sia vuoto
	auto archi_C = C.G.all_edges();
	auto nodi_C = C.G.all_nodes();
	
	if (nodi_C.empty()) {
		std::cerr << "ERRORE: Il grafo generato non contiene nodi\n" ;
		return EXIT_FAILURE;
	}
	if (archi_C.empty()) {
        std::cerr << "ERRORE: Il grafo generato non contiene archi\n" ;
		return EXIT_FAILURE;
	}
	
	//controllo che le resistenze e i generatori siano stati collocati opportunamente
	if (C.R.size() != 5) {
		std::cerr << "ERRORE: Le resistenze non sono state smistate correttamente\n";
		return EXIT_FAILURE;
	}
	if (C.V.size() != 2) {
		std::cerr << "ERRORE: I generatori non sono stati smistati correttamente\n";
		return EXIT_FAILURE;
	}
	
	//controllo che i segni siano stati assegnati correttamente agli archi: +1 se n1<n2, -1 altrimenti
	for (const auto& nl : C.R) {
		//controllo resistenze
		undirected_edge<int> e(nl.nodo1(), nl.nodo2());
		int segno_giusto;
		if (nl.nodo1() < nl.nodo2()) {
			segno_giusto = 1;
		}
		else {
			segno_giusto = -1; 
		}
		
		if (C.segno.find(e) == C.segno.end()) {//il segno non è stato trovato
			std::cerr << "ERRORE: non è stato assegnato un segno all'arco associato al componente " << nl.nome() << "\n";
			return EXIT_FAILURE; 
		}
		if (C.segno[e] != segno_giusto) {//il segno non è quello che dovrebbe essere
			std::cerr << "ERRORE: il segno dell'arco associato al componente " << nl.nome() << " non è corretto\n";
			return EXIT_FAILURE; 
		}
	}
	for (const auto& [e, valore] : C.V) {
		//controllo generatori
		int segno_giusto;
		if (e.from() < e.to()) {
			segno_giusto = 1;
		}
		else {
			segno_giusto = -1; 
		}
		
		if (C.segno.find(e) == C.segno.end()) {//il segno non è stato trovato
			std::cerr << "ERRORE: non è stato assegnato un segno all'arco " << e << "\n";
			return EXIT_FAILURE; 
		}
		if (C.segno.at(e) != segno_giusto) {//il segno non è quello che dovrebbe essere
			std::cerr << "ERRORE: il segno dell'arco " << e << " non è corretto\n";
			return EXIT_FAILURE; 
		}
	}
	//controllo che l'indicizzazione sia corretta
	/*for (size_t i = 0; i < archi_C.size(); ++i) {
		if (C.indice.find(archi_C[i]) == C.indice.end() || //l'indice non è stato trovato
	        C.indice[archi_C[i]] != static_cast<int>(i)) {//l'indice non è quello giusto
			    std::cerr << "ERRORE: l'indicizzazione degli archi non è corretta\n";
			    return EXIT_FAILURE;
			}
	}*/
	//test con argc <2
	const char* argv2[] = {"test2"};
	int argc2 = std::size(argv2); //1
	auto res2 = read_file(argc2, argv2);
	if (res2.has_value()){
		std::cerr <<"ERRORE: lettura di un file con argc < 2\n";
		return EXIT_FAILURE;
	}
	//test con argc>2
	const char* argv3[] = {"test3", "netlist_prova.txt", "netlist_esempio.txt"};
	int argc3 = std::size(argv3); //3
	auto result3 = read_file(argc3, argv3);
	if (result3.has_value()) {
		std::cerr << "ERRORE: legge un file quando argc > 2\n";
		return EXIT_FAILURE;
	}
	// test con file inesistente
	const char* argv4[] = {"test4", "netlistttttt.txt"};
	int argc4 = std::size(argv4); //2
	auto result4 = read_file(argc4, argv4);
	if (result4.has_value()) {
		std::cerr << "ERRORE: legge un file che non esiste\n";
		return EXIT_FAILURE;
	}
	//test no double
	const char* argv5[] = {"test5", "test_no_double.txt"};
	int argc5 = std::size(argv5);
	auto result5 = read_file(argc5, argv5);
	if (!result5.has_value()) {
		std::cerr << "ERRORE: il file dovrebbe essere letto\n";
		return EXIT_FAILURE;
	}
	circuito C5 = *result5;
	if (!C5.R.empty()) {
		std::cerr << "ERRORE: non ci dovrebbero essere resistenze\n";
		return EXIT_FAILURE;
	}
	if (C5.V.size() != 1) {
		std::cerr << "ERRORE: dovrebbe esserci un solo generatore\n";
		return EXIT_FAILURE;
	}
	undirected_edge<int> e5(2,3);
	auto it5 = C5.V.find(e5);
	double tol = 1e-12;
	if (it5 == C5.V.end() || std::abs(it5->second - 0.9)> tol) {
		std::cerr << "ERRORE: il generatore letto non è corretto\n";
		return EXIT_FAILURE;
	}
	//test errore V
	const char* argv6[] = {"test6", "test_errore_v.txt"};
	int argc6 = std::size(argv6);
	auto result6 = read_file(argc6, argv6);
	if (!result6.has_value()) {
		std::cerr << "ERRORE: il file dovrebbe essere letto\n";
		return EXIT_FAILURE;
	}
	circuito C6 = *result6;
	if (C6.R.size() != 1) {
		std::cerr << "ERRORE: dovrebbe esserci una sola resistenza\n";
		return EXIT_FAILURE;
	}
	if (!C6.V.empty()) {
		std::cerr << "ERRORE: non ci dovrebbero essere generatori\n";
		return EXIT_FAILURE;
	}
	if (C6.R[0] != netlist("R1", 100.0, 0, 1)) {
		std::cerr << "ERRORE: la resistenza letta non è corretta\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}