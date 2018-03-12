#ifndef LISTA_HH
#define LISTA_HH

#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Element {
	int miasto;
	int kosztPodrozy;
	Element * nastepny;
	Element * poprzedni;
};

class Lista {
private:

	Element* poczatek;
	Element* koniec;
	int rozmiar;

public:

	Lista();
	~Lista();

	void wyswietl();
	void dodaj(int miasto, int kosztPodrozy);
	bool usun();
};

#endif
