#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char *argv[]){
	if (argc <2) {
	cerr << "Errore: file non specificato\n";
	return 1;
	}

	for (int riga =1; riga < argc; riga ++){
	ifstream ifs(argv[riga]);
	if(ifs.is_open()) {
			for( int riga= 0; riga <= 2; riga++) {
					string location;
					double temp1;
					double temp2;
					double temp3;
					double temp4;
					double average;
					ifs >> location >> temp1 >> temp2 >> temp3 >> temp4;
					average = (temp1 + temp2 + temp3 + temp4) / 4;
					cout << location << "      " << average << "\n";
			}
			}
					
	
	else {
		cerr << "Errore : file " <<argv[riga] <<" not found\n";
		return 2;

	}}
	return 0;
	}