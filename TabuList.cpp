#include "TabuList.hpp"

TabuList::TabuList(int dlTabuList, int dlKadencji)
{
	dlugoscTabuListy = dlTabuList;
	dlugoscKadencji = dlKadencji;
	tab = new ElementTabuList[dlugoscTabuListy];
	for (int i = 0; i < dlugoscTabuListy; i++) {
		tab[i].kadencja = 0;
	}
	aktualneMiejsceDowWstawienia = 0;
}

// Dodaje ruch do listy tabu
void TabuList::DodajElement(int miastoPoczatkowe, int miastoDocelowe)
{
	tab[aktualneMiejsceDowWstawienia].miastoPoczatkowe = miastoPoczatkowe;
	tab[aktualneMiejsceDowWstawienia].miastoDocelowe = miastoDocelowe;
	tab[aktualneMiejsceDowWstawienia].kadencja = dlugoscKadencji;
	aktualneMiejsceDowWstawienia++;
	if (aktualneMiejsceDowWstawienia >= dlugoscTabuListy) {
		aktualneMiejsceDowWstawienia = 0;
	}
}

// Wyszukuje podany ruch na liœcie tabu
bool TabuList::SzukajElement(int miastoPoczatkowe, int miastoDocelowe)
{
	for (int i = 0; i < dlugoscTabuListy; i++) {
		if (tab[i].kadencja > 0) {
			if ((tab[i].miastoPoczatkowe == miastoPoczatkowe && tab[i].miastoDocelowe == miastoDocelowe) ||
				(tab[i].miastoPoczatkowe == miastoDocelowe && tab[i].miastoDocelowe == miastoPoczatkowe)) {
				return true;
			}
		}
	}
	return false;
}

// Zmniejsz liczbê kadencji o 1
void TabuList::ZmniejszKadencje()
{
	for (int i = 0; i < dlugoscTabuListy; i++) {
		tab[i].kadencja--;
	}
}


