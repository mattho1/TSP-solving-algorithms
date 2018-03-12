#include "Lista.hpp"

Lista::Lista() {
	rozmiar = 0;
	poczatek = NULL;
	koniec = NULL;
}

Lista::~Lista() {
	for (int i = 0; i < rozmiar; i++) {
		usun();
	}
}

// metoda sluzaca do wyswietlania listy elementow jako listy kolejnych miast 
// w problemie komiwoja¿era

void Lista::wyswietl() {
	int calkowityKoszt = 0;
	cout << endl << "Trasa = ";
	if (rozmiar != 0) {
		Element elemWyswietl;
		elemWyswietl = *poczatek;
		while (true) {
			cout << elemWyswietl.miasto;
			calkowityKoszt += elemWyswietl.kosztPodrozy;
			if (elemWyswietl.nastepny == NULL) {
				break;
			}
			cout << " - ";
			elemWyswietl = *elemWyswietl.nastepny;
		}
	}
	cout << endl << "Dlugosc trasy = " << calkowityKoszt << endl;
	cout << endl;
}

// metoda sluzy do dodawania kolejnych miast do listy
// miasto okreslane jest poprzez swoj numer i koszt podrozy do miasta z poprzedniego
// metoda dodaj dodaje miasto na koneic listy 

void Lista::dodaj(int miasto, int kosztPodrozy) {
	Element* elem;
	elem = new Element();
	elem->miasto = miasto;
	elem->kosztPodrozy = kosztPodrozy;
	elem->poprzedni = NULL;
	elem->nastepny = NULL;
	if (rozmiar == 0) {
		rozmiar++;
		poczatek = elem;
		koniec = elem;
	}
	else {
		rozmiar++;
		koniec->nastepny = elem;
		elem->poprzedni = koniec;
		koniec = elem;
	}
}

// metoda usun usuwa element z konca listy

bool Lista::usun() {
	if (rozmiar != 0) {
		if (rozmiar == 1) {
			rozmiar--;
			delete koniec;
			koniec = NULL;
			poczatek = NULL;
			return true;
		}
		rozmiar--;
		Element* tmp;
		koniec->poprzedni->nastepny = NULL;
		tmp = koniec->poprzedni;
		delete koniec;
		koniec = tmp;
		return true;
	}
	else {
		return false;
	}
}

