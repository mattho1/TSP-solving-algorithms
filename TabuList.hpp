#ifndef TabuList_HH
#define TabuList_HH 
#include <iostream>

struct ElementTabuList {
	int miastoPoczatkowe;
	int miastoDocelowe;
	int kadencja;
};

class TabuList {
private:
	ElementTabuList* tab;
	int dlugoscTabuListy;
	int dlugoscKadencji;
	int aktualneMiejsceDowWstawienia;
public:
	TabuList(int, int);
	void DodajElement(int miastoPoczatkowe, int miastoDocelowe);
	bool SzukajElement(int miastoPoczatkowe, int miastoDocelowe);
	void ZmniejszKadencje();
};

#endif