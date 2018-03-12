#ifndef POPULACJA_HH
#define POPULACJA_HH


#include "Lista.hpp"
#include "Wezel.hpp"
#include "TabuList.hpp"
#include "Struktury.hpp"
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <ctime>
#include <random> 
#include <string>
#include <cmath>
#include <algorithm> 
#include <queue>
#include <conio.h>
#define nieskonczonosc 50000000

using namespace std;

struct Zamiana {
	int z;
	int d;
};
struct Potomkowie {
	int* pierwszeDziecko;
	int* drugieDziecko;
};
class Populacja {
private:

	int** miasta; // dane pobrane z pliku
	int liczbaMiast; // liczba Miast; wielkosc problemu komiwojazera
	int** osobniki;
	int* przystowosawnieOsobnikow;	// przystosowanie osobników w œrodowisku
	int numerNajlepszegoOsobnika;	// Numer w populacji najlepszego osobnika
	int numerNajgorszegoOsobnika;	// Numer w populacji najgorszego osobnika
	int** tablicaOsobnikowDoKrzyzowania;	// Tablica numerów rodziców w populacji

	// parametry populacji
	float prawdopodobienstwoMutacji = 0.2f;
	float prawdopodobienstwoKrzyzowania = 0.9f;
	int wielkoscTurnieju = 2;
	int wielkoscPopulacji;	// ustalona na 1,5 liczbyMiast

	void WyliczPierwszeRozwiazania();
	int OcenaPrzystosowania(int * osobnik);
	void KopiujTablice(int * zmieniana, int * wartosci);
	void DokonajWstawienia(int * rozwiazanie);
	void DokonajInwersji(int * rozwiazanie);
	void DokonajZamiany(int * rozwiazanie);
	bool CzyKrzyzowanie();
	void KrzyzowanieOX(Potomkowie& potomkowie, int * pierwszyRodzic, int * drugiRodzic);
	bool CzyMutacja();
	void Mutacja(int * osobnik);
	
	int ZnajdzNajgorszegoOsobnika();
	void DodajNowegoOsobnikaDoPopulacji(int * nowyOsobnik);
	bool SprawdzCzyMoznaWstawic(int poczatek, int koniec, int * tablica, int wartoscSprawdzana);
	Zamiana LosujMiejsca();
	void pomocniczeWyswietlanieOsobnika(int * testowaTablica);

public:
	void TestoweWyswietlenieCalejPopulacji();

	Populacja(int** Dane, int liczbaMiast);
	~Populacja();
	void GenerujPopulacjePoczatkowa();
	void Krzyzowanie();
	void SeleckcjaTurniejowa();
	void ObliczPrzystosowanieOsobnikow();
	void ZwrocNajlepszegoOsobnika(int * rozwiazanie);
	float SredniePrzystosowaniePopulacji();
};

#endif