#ifndef Struktury_HH
#define Struktury_HH 
#include <iostream>

class Wezel {
private:
	int nrMiasta; // numer Miasta jaki wezel reprezentuje
	int LB;  // lower band - najlepsze teoretyczne rozwiazanie jakie mozna osiagnac z tego wierzcholka
	bool rozwijac; // okresla czy warto jeszcze rozwijac galaz od tego wierzcholka
	Wezel * Rodzic; // wskaznik na wezel ponad tym wezlem w drzewie 
	Wezel** potomkowie; // tablica wskaznikow na potomkow tego wezla 
	int liczbaPotomkow; // liczba potomkow wezla 
public:
	Wezel();
	Wezel(int i, Wezel*rd);
	Wezel* zwrocPotomka(int nr);
	Wezel* zwrocRodzica();
	bool czyRozwijac();
	void nieRozwijac();
	int zwrocLiczbePotomkow();
	int zwrocNrMiasta();
	void stworzPotomkow(int lp);
	void stworzPotomka(int i, int j);
	void ustawLB(int lowerband);
	int zwrocLB();
	void ustawRozwijac(bool);
};

#endif
