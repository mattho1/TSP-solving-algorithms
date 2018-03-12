#ifndef PK_HH
#define PK_HH


#include "Lista.hpp"
#include "Wezel.hpp"
#include "TabuList.hpp"
#include "Struktury.hpp"
#include "Populacja.hpp"
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

struct Ruch {
	int miastoPoczatkowe;
	int miastoDocelowe;
};

struct PunktyWCiagu {
	int pierwszy;
	int drugi;
};

class ProblemKomiwojazera {
private:

	int** miasta; // dane pobrane z pliku
	int liczbaMiast; // liczba Miast; wielkosc problemu komiwojazera
	int poczatek = 0; // numer miasta poczatkowego - z regu³y 0
	int UBglobal; // najlepsze do tej pry znalezione rozwiazanie
	int * najlepszeTeoretyczneRozwiazanie; // najlepsze wartosci krawedzi wychodzace z ka¿dego wierzcho³ka
	int * liczbaSasiadowWierzcholka; // liczba s¹siadów ka¿dego wierzcho³ka (przydatne przy grafie nie pe³nym)

	int * rozpatrywaneRozwiazanie;
	int licznikDoZdarzeniaKrytycznego;
	int dlugoscTabuList;
	int iloscIteracji = 1000;
	int dlKadencji = 100;
	int kryteriumLiczbyZamianWDywesyfikacji = 40;

	int licznikBlokad = 0;
	int licznikBlokad2 = 0;

	// metody do algorytmu podzia³u i ograniczeñ
	int obliczLB();
	int obliczLB(Wezel *);
	void obliczUB(int *, Wezel *);
	void obliczLiczbeSasiadow();
	int iloscWystapienPotomkow(Wezel *);
	int poziom(Wezel *);
	bool sprawdzCzyJuzByl(int i, Wezel *);

	// metody do algorytmu Tabu search
	int OcenaRuchu(int*, int*);
	Ruch WyborRuchu(TabuList*);
	int ObliczKosztPrzejscia(int*);
	void KopiujTablice(int*, int*);
	void NoweLosowaniePoczatkowegoRozwiazania();
	bool zdarzenieKrytyczne();
	bool KryteriumAspiracji(int*);
	void DokonajZamiany(int*, int, int);
	Ruch LosujRuch();
	void DokonajInwersji(int*, int, int);
	void DokonajWstawienia(int*, int, int);

public:

	ProblemKomiwojazera(int** Dane, int liczbaMiast, int poczatek);
	~ProblemKomiwojazera();

	Lista* algorytmPrzegladZupelny();
	Lista* algorytmZachlanny();
	void algorytmZach(int*);
	void algorytmPodzialuIOgraniczen(int*);
	void algorytmTabuSerach(int*);
	void algorytmGenetyczny(int*);
};

#endif
