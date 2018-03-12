#include "Wezel.hpp"

Wezel::Wezel() {
	rozwijac = true;
}
Wezel::Wezel(int i, Wezel*rd) {
	nrMiasta = i;
	Rodzic = rd;
	rozwijac = true;
}

// Metoda zwraca wskaznik na potomka o numerze w tablicy potomkow wezla podanym jako argument
Wezel* Wezel::zwrocPotomka(int nr) {
	return potomkowie[nr];
}

// Metoda zwraca wskaznik na rodzica wezla dla ktorego zostala wywolana metoda
Wezel* Wezel::zwrocRodzica() {
	return Rodzic;
}

// Metoda zwraca informacje czy wezel warto rozwijac
bool Wezel::czyRozwijac() {
	return rozwijac;
}

// Metoda ustawia wezel na niewarty rozwijania i usuwa jego potomkow
void Wezel::nieRozwijac() {
	rozwijac = false;
	for (int i = 0; i < liczbaPotomkow; i++) {
		delete potomkowie[i];
	}
	delete[] potomkowie;
	liczbaPotomkow = 0;
}

// Metoda zwraca liczbe potomkow wezla
int Wezel::zwrocLiczbePotomkow() {
	return liczbaPotomkow;
}

// Metoda zwraca numer miasta reprezentowanego przez wezel
int Wezel::zwrocNrMiasta() {
	return nrMiasta;
}

// Metoda tworzy tablice wskaznikow na potomkow o wielkosci podanej jako argument
void Wezel::stworzPotomkow(int lp) {
	if (lp > 0) {
		liczbaPotomkow = lp;
		potomkowie = new Wezel*[liczbaPotomkow];
	}
	else {
		liczbaPotomkow = 0;
		rozwijac = false;
	}

}

// Metoda tworzy potomka o podanym numerze
void Wezel::stworzPotomka(int i, int j) {
	potomkowie[j] = new Wezel(i, this);
}

// Metoda ustawia wartosc lower band
void Wezel::ustawLB(int lowerband) {
	LB = lowerband;
}

// Metoda zwraca wartosc lower band
int Wezel::zwrocLB() {
	return LB;
}

// Metoda ustawia pole rozwijac na wartosc podana jako argument
void Wezel::ustawRozwijac(bool rozw) {
	rozwijac = rozw;
}
