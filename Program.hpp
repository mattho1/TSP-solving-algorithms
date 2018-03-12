#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "ProblemKomiwojazera.hpp"
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <ctime>
#include <random> 
#include <string>
#include <cmath>
#include <memory> 
#include <cstdio>
#include <conio.h>
using namespace std;

#include "rapidxml.hpp"
#include "rapidxml_print.hpp" 
using namespace rapidxml;
using namespace std;

class Program {
private:

	int** dane; // dane pobrane z pliku
	ProblemKomiwojazera* problemKomiwojazera;
	Lista* odwiedzoneMiasta; // rozwiazanie z algorytmu zachlannego i przegladu zupelnego
	int* rozwiazanie; // miasta stanowiace rozwiazanie problemu komiwojazera obliczone algorytmem podzialu i ograniczen
	int kosztPodrozy;
	bool czyodwiedzonemiasta; // flaga czy by³a tworzona lista odwiedzonych miast 
	int poczatek; // numer miasta poczatkowego - przewaznie 0
	int liczbaMiast;

	long long int read_QPC();

public:

	Program();
	~Program();

	void menu();
	bool pobierzDane(string nazwaPliku, int wybor);
	void wyswietlPK();
	bool generator(int wielkosc);
	void wyswietlRozwiazanie();
	void wyswietlDane();
};
#endif
