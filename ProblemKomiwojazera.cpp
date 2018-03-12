#include "ProblemKomiwojazera.hpp"


// metoda rozwiazuje problem komiwojazera z wykorzystaniem algorytmu przegladu zupelnego
// zwraca wskaznik na liste bedaca rozwiazaniem problemu komiwojazera

Lista* ProblemKomiwojazera::algorytmPrzegladZupelny() {
	Lista* odwiedzoneMiasta;
	int min, rozpatrywanyKosztPrzejscia;
	int* miastaOdwiedzane;
	int* miastaDoPrzejscia;
	miastaOdwiedzane = new int[liczbaMiast - 1];
	miastaDoPrzejscia = new int[liczbaMiast - 1];

	for (int i = 0, n = 0; i < liczbaMiast; i++) {
		if (i != poczatek) {
			miastaOdwiedzane[n] = i;
			miastaDoPrzejscia[n] = i;
			n++;
		}
	}

	min = nieskonczonosc;

	if (liczbaMiast > 1) {
		do {
			rozpatrywanyKosztPrzejscia = 0;
			rozpatrywanyKosztPrzejscia += miasta[poczatek][miastaOdwiedzane[0]];
			for (int i = 1; i < liczbaMiast - 1; i++) {
				rozpatrywanyKosztPrzejscia += miasta[miastaOdwiedzane[i - 1]][miastaOdwiedzane[i]];
			}
			rozpatrywanyKosztPrzejscia += miasta[miastaOdwiedzane[liczbaMiast - 2]][poczatek];

			if (rozpatrywanyKosztPrzejscia < min) {
				for (int i = 0; i < liczbaMiast - 1; i++) {
					miastaDoPrzejscia[i] = miastaOdwiedzane[i];
				}
				min = rozpatrywanyKosztPrzejscia;
			}
		} while (next_permutation(miastaOdwiedzane, miastaOdwiedzane + (liczbaMiast - 1)));
	}


	odwiedzoneMiasta = new Lista();
	odwiedzoneMiasta->dodaj(poczatek, 0);
	odwiedzoneMiasta->dodaj(miastaDoPrzejscia[0], miasta[poczatek][miastaDoPrzejscia[0]]);
	for (int i = 1; i < liczbaMiast - 1; i++) {
		odwiedzoneMiasta->dodaj(miastaDoPrzejscia[i], miasta[miastaDoPrzejscia[i - 1]][miastaDoPrzejscia[i]]);
	}
	odwiedzoneMiasta->dodaj(poczatek, miasta[miastaDoPrzejscia[liczbaMiast - 2]][poczatek]);

	delete[]miastaOdwiedzane;
	delete[]miastaDoPrzejscia;

	return odwiedzoneMiasta;
}

// Metoda rozwiazujaca problem komiwoja¿era za pomoca podzialu i ograniczen
// Wynik dzialania algorytmu zostaje zapisany w tablicy podanej jako argument (miastaWRozw)

void ProblemKomiwojazera::algorytmPodzialuIOgraniczen(int * miastaWRozw)
{
	if (liczbaMiast > 2) {
		UBglobal = nieskonczonosc;
		obliczLiczbeSasiadow();
		Wezel* korzen = new Wezel(poczatek, nullptr);
		Wezel* tmp;
		int min = 0;
		int minWartosc = nieskonczonosc;
		int liczbaPotomkow;
		bool dalej;
		korzen->stworzPotomkow(liczbaSasiadowWierzcholka[poczatek]);
		korzen->ustawLB(obliczLB());
		for (int i = 1, j = 0; i < liczbaMiast; i++) {
			if (miasta[poczatek][i] != 0) {
				korzen->stworzPotomka(i, j);
				korzen->zwrocPotomka(j)->ustawLB(obliczLB(korzen->zwrocPotomka(j)));
				if (miasta[poczatek][i] < minWartosc) {
					minWartosc = miasta[poczatek][i];
					min = j;
				}
				j++;
			}
		}
		tmp = korzen->zwrocPotomka(min);
		dalej = true;
		while (korzen->czyRozwijac()) {
			if (tmp->zwrocLB() >= UBglobal) {
				tmp->ustawRozwijac(false);
			}
			if (tmp->czyRozwijac()) {
				liczbaPotomkow = liczbaSasiadowWierzcholka[tmp->zwrocNrMiasta()] - iloscWystapienPotomkow(tmp);
				tmp->stworzPotomkow(liczbaPotomkow);
				if (tmp->zwrocLiczbePotomkow() > 0) {
					min = 0;
					for (int i = 1, j = 0; i < liczbaMiast; i++) {
						if (sprawdzCzyJuzByl(i, tmp)) {
							if (miasta[tmp->zwrocNrMiasta()][i] != 0) {
								tmp->stworzPotomka(i, j);
								tmp->zwrocPotomka(j)->ustawLB(obliczLB(tmp->zwrocPotomka(j)));
								if (tmp->zwrocPotomka(j)->zwrocLB() < tmp->zwrocPotomka(min)->zwrocLB()) {
									min = j;
								}
								j++;
							}
						}
					}
					if (liczbaPotomkow > 2 || (poziom(tmp) < (liczbaMiast - 2))) {
						tmp = tmp->zwrocPotomka(min);
					}
					else {
						obliczUB(miastaWRozw, tmp);
						tmp->nieRozwijac();
					}
				}
				else {
					tmp->ustawRozwijac(false);
				}
			}
			else {
				tmp = tmp->zwrocRodzica();
				dalej = false;
				min = 0;
				minWartosc = nieskonczonosc;
				for (int i = 0; i < tmp->zwrocLiczbePotomkow(); i++) {
					if (miasta[tmp->zwrocNrMiasta()][tmp->zwrocPotomka(i)->zwrocNrMiasta()] < minWartosc
						&& miasta[tmp->zwrocNrMiasta()][tmp->zwrocPotomka(i)->zwrocNrMiasta()] != 0
						&& tmp->zwrocPotomka(i)->czyRozwijac()) {
						dalej = true;
						min = i;
						minWartosc = miasta[tmp->zwrocNrMiasta()][tmp->zwrocPotomka(i)->zwrocNrMiasta()];
					}
				}
				if (dalej) {
					tmp = tmp->zwrocPotomka(min);
				}
				else {
					tmp->nieRozwijac();
				}
			}
		}
		delete[]liczbaSasiadowWierzcholka;
		delete[]najlepszeTeoretyczneRozwiazanie;
		delete korzen;
	}
	else {
		if (liczbaMiast > 0) {
			miastaWRozw[0] = poczatek;
			if (liczbaMiast > 1) {
				miastaWRozw[1] = 1;
				miastaWRozw[2] = poczatek;
			}
			else {
				miastaWRozw[1] = poczatek;
			}
		}
	}
}

// Metoda liczy lower band 
// Jako wynik zwraca obliczony lower band
// Tworzy i uzupelnia tablice najlepszeTeoretyczneRozwiazanie 
// przechowujaca wartosci najtanszych krawedzi wychodzacych z kazdego wierzcholka

int ProblemKomiwojazera::obliczLB()
{
	int LB = 0, min;
	najlepszeTeoretyczneRozwiazanie = new int[liczbaMiast];

	for (int i = 0; i < liczbaMiast; i++) {
		min = nieskonczonosc;
		for (int j = 0; j < liczbaMiast; j++) {
			if (min > miasta[i][j] && miasta[i][j] != 0) {
				min = miasta[i][j];
			}
		}
		najlepszeTeoretyczneRozwiazanie[i] = min;
		LB += min;
	}
	return LB;
}

// Metoda oblicza lower band dla wierzcholka podanego jako argument
// Metoda zwraca obliczony lower band 

int ProblemKomiwojazera::obliczLB(Wezel * wezelStartowy) {
	return wezelStartowy->zwrocRodzica()->zwrocLB() + (miasta[wezelStartowy->zwrocRodzica()->zwrocNrMiasta()][wezelStartowy->zwrocNrMiasta()] - najlepszeTeoretyczneRozwiazanie[wezelStartowy->zwrocRodzica()->zwrocNrMiasta()]);
}

// Metoda oblicza UB dla wiercholka podanego jako argument
// Jezeli obliczony UB lepszy od dotychczasowego zapisuje rozwiazanie do 
// tablicy rozwiazanie podanej jako argument

void ProblemKomiwojazera::obliczUB(int * rozwiazanie, Wezel * wezelStartowy)
{
	int UB = 0;
	int przedostatni, wczesniejszy;
	Wezel * tmpWezel;
	if (miasta[wezelStartowy->zwrocNrMiasta()][poczatek] != 0) {

		przedostatni = wezelStartowy->zwrocPotomka(0)->zwrocNrMiasta();

		if (miasta[wezelStartowy->zwrocNrMiasta()][przedostatni] != 0) {

			UB += (miasta[wezelStartowy->zwrocNrMiasta()][przedostatni] - najlepszeTeoretyczneRozwiazanie[wezelStartowy->zwrocNrMiasta()]);
			UB += (miasta[przedostatni][poczatek] - najlepszeTeoretyczneRozwiazanie[przedostatni]);
			tmpWezel = wezelStartowy;
			UB += wezelStartowy->zwrocLB();
			if (UB < UBglobal) {
				UBglobal = UB;
				rozwiazanie[liczbaMiast] = poczatek;
				rozwiazanie[liczbaMiast - 1] = przedostatni;
				rozwiazanie[liczbaMiast - 2] = wezelStartowy->zwrocNrMiasta();
				for (int i = liczbaMiast - 3; i >= 0; i--) {
					wczesniejszy = tmpWezel->zwrocRodzica()->zwrocNrMiasta();
					UB += miasta[wczesniejszy][tmpWezel->zwrocNrMiasta()];
					rozwiazanie[i] = wczesniejszy;
					tmpWezel = tmpWezel->zwrocRodzica();
				}
			}
		}
	}
}

// Metoda oblicza liczbe sasiadow dla kazdego wierzcholka
// Liczbe sasiadow dla kazdego wierzcholka zapisuje w tablicy liczbaSasiadowWierzcholka

void ProblemKomiwojazera::obliczLiczbeSasiadow()
{
	liczbaSasiadowWierzcholka = new int[liczbaMiast];
	for (int i = 0; i < liczbaMiast; i++) {
		liczbaSasiadowWierzcholka[i] = 0;
		for (int j = 0; j < liczbaMiast; j++) {
			if (miasta[i][j] != 0) {
				liczbaSasiadowWierzcholka[i] += 1;
			}
		}
	}
}

// Metoda oblicza ile wierzcholkow do ktorych mozna przejsc z wierzcholka podanego 
// jako argument metody zostalo juz wykorzystanych wczesniej w drzewie

int ProblemKomiwojazera::iloscWystapienPotomkow(Wezel * wezelStartowy) {
	int liczbaPoziomow = 0;
	int miastoWyjsciowe = wezelStartowy->zwrocNrMiasta();
	Wezel * tmp;
	tmp = wezelStartowy;
	while (tmp->zwrocRodzica() != nullptr) {
		tmp = tmp->zwrocRodzica();
		if (miasta[miastoWyjsciowe][tmp->zwrocNrMiasta()] != 0) {
			liczbaPoziomow++;
		}
	}
	return liczbaPoziomow;
}

// Metoda sprawdza czy wierzcholek o podanym jako argument numerze 
// wystepuje powyzej danego (jako drugi argument) wierzcholka w drzewie 

bool ProblemKomiwojazera::sprawdzCzyJuzByl(int i, Wezel * wezelStartowy) {
	Wezel * tmp;
	tmp = wezelStartowy;
	while (tmp->zwrocRodzica() != nullptr) {
		if (i == tmp->zwrocNrMiasta()) {
			return false;
		}
		tmp = tmp->zwrocRodzica();
	}
	return true;
}

// Metoda oblicza ktorym wiercholkiem w rozwiazaniu jest podany jako argument wierzcholek

int ProblemKomiwojazera::poziom(Wezel * wezelStartowy) {
	int liczbaPoziomow = 0;
	Wezel * tmp;
	tmp = wezelStartowy;
	while (tmp->zwrocRodzica() != nullptr) {
		tmp = tmp->zwrocRodzica();
		liczbaPoziomow++;
	}
	return liczbaPoziomow;
}

ProblemKomiwojazera::ProblemKomiwojazera(int** Dane, int liczbaMiast, int poczatek) {
	//srand(time(NULL));
	this->liczbaMiast = liczbaMiast;
	this->poczatek = poczatek;
	this->poczatek = 0;
	miasta = new int*[liczbaMiast];
	for (int i = 0; i < liczbaMiast; i++) {
		miasta[i] = new int[liczbaMiast];
		for (int n = 0; n < liczbaMiast; n++) {
			miasta[i][n] = Dane[i][n];
		}
	}
}

ProblemKomiwojazera::~ProblemKomiwojazera() {
	for (int i = 0; i < liczbaMiast; i++) {
		delete[]miasta[i];
	}
	delete[]miasta;
}

// Metoda rozwiazuje problem komiwoja¿era z zastosowaniem algorytmu Tabu Search
void ProblemKomiwojazera::algorytmTabuSerach(int * najlepszeRozwiazanie)
{
	//srand(time(NULL));
	int tmpIloscIteracji = iloscIteracji;
	int licznikTymczasowy1 = 0, licznikTymczasowy2 = 0;
	Ruch ruch;
	licznikDoZdarzeniaKrytycznego = 0;
	rozpatrywaneRozwiazanie = new int[liczbaMiast - 1];
	najlepszeTeoretyczneRozwiazanie = new int[liczbaMiast - 1];
	algorytmZach(najlepszeRozwiazanie);
	for (int i = 0; i < liczbaMiast - 1; i++) {
		rozpatrywaneRozwiazanie[i] = najlepszeRozwiazanie[i + 1];
	}
	KopiujTablice(najlepszeTeoretyczneRozwiazanie, rozpatrywaneRozwiazanie);
	dlugoscTabuList = iloscIteracji;
	TabuList* tabuList = new TabuList(dlugoscTabuList, dlKadencji);

	while (iloscIteracji > 0) {
		ruch = WyborRuchu(tabuList);
		if (ObliczKosztPrzejscia(rozpatrywaneRozwiazanie) < ObliczKosztPrzejscia(najlepszeTeoretyczneRozwiazanie)) {
			KopiujTablice(najlepszeTeoretyczneRozwiazanie, rozpatrywaneRozwiazanie);
			licznikDoZdarzeniaKrytycznego = 0;
		}

		tabuList->ZmniejszKadencje();
		tabuList->DodajElement(ruch.miastoPoczatkowe, ruch.miastoDocelowe);

		if (zdarzenieKrytyczne()) {
			NoweLosowaniePoczatkowegoRozwiazania();
			if (ObliczKosztPrzejscia(rozpatrywaneRozwiazanie) < ObliczKosztPrzejscia(najlepszeTeoretyczneRozwiazanie)) {
				KopiujTablice(najlepszeTeoretyczneRozwiazanie, rozpatrywaneRozwiazanie);
			}
			licznikDoZdarzeniaKrytycznego = 0;
		}
		iloscIteracji--;
	}
	iloscIteracji = tmpIloscIteracji;
	najlepszeRozwiazanie[0] = 0;
	for (int i = 0; i < liczbaMiast - 1; i++) {
		najlepszeRozwiazanie[i + 1] = najlepszeTeoretyczneRozwiazanie[i];
	}
	najlepszeRozwiazanie[liczbaMiast] = 0;
	delete[]najlepszeTeoretyczneRozwiazanie;
	delete[]rozpatrywaneRozwiazanie;
}

// Metoda kopiuje wartosci z tablicy wartosci do tablicy zmieniana
void ProblemKomiwojazera::KopiujTablice(int* zmieniana, int* wartosci) {
	for (int i = 0; i < liczbaMiast - 1; i++) {
		zmieniana[i] = wartosci[i];
	}
}
// Metoda sprawdza czy nastapilo zdarzenie krytyczne i nale¿y dokonaæ dywersyfikacji
bool ProblemKomiwojazera::zdarzenieKrytyczne() {
	licznikDoZdarzeniaKrytycznego++;
	if (licznikDoZdarzeniaKrytycznego >= 2 * liczbaMiast) {
		return true;
	}
	else {
		return false;
	}
}
// Wyznacza nowe rozwiazanie poprzez dokonanie okreslonej liczby inwersji na obecnie rozpatrywanym rozwiazaniu
void ProblemKomiwojazera::NoweLosowaniePoczatkowegoRozwiazania()
{
	Ruch nowyruch;
	for (int i = 0; i < kryteriumLiczbyZamianWDywesyfikacji; i++) {
		nowyruch = LosujRuch();
		DokonajInwersji(rozpatrywaneRozwiazanie, nowyruch.miastoPoczatkowe, nowyruch.miastoDocelowe);
	}
}
// Wybor sasiada poprzez poprzez inwersje
void ProblemKomiwojazera::DokonajInwersji(int* rozwiazanie, int z, int d) {
	if (z > d) {
		int tmp = d;
		d = z;
		z = tmp;
	}
	int granica = (int)ceil((double)(z + d) / 2);
	for (int i = z, j = d; i < granica; i++, j--) {
		DokonajZamiany(rozwiazanie, i, j);
	}
}
// Metoda losuje ruch z przedzia³u od 0 do liczbyMiast - 1
Ruch ProblemKomiwojazera::LosujRuch() {
	Ruch ruch;
	ruch.miastoPoczatkowe = (std::rand() % (liczbaMiast - 1));
	ruch.miastoDocelowe = (std::rand() % (liczbaMiast - 1));
	while (ruch.miastoPoczatkowe == ruch.miastoDocelowe) {
		ruch.miastoDocelowe = (std::rand() % (liczbaMiast - 1));
	}
	if (ruch.miastoPoczatkowe > ruch.miastoDocelowe) {
		int tmp = ruch.miastoDocelowe;
		ruch.miastoDocelowe = ruch.miastoPoczatkowe;
		ruch.miastoPoczatkowe = tmp;
	}
	return ruch;
}
// Metoda wyszukuje najlepszy ruch z sasiedztwa obecnie rozpatrywanego rozwiazania
Ruch ProblemKomiwojazera::WyborRuchu(TabuList* tabuList)
{
	Ruch ruch;
	ruch.miastoPoczatkowe = 1;
	ruch.miastoDocelowe = 1;
	int ocenaRuchu;
	int* noweRozwiazanie = new int[liczbaMiast - 1];
	int najlepszeRozwiazanie = -nieskonczonosc;
	for (int z = 0; z < liczbaMiast - 1; z++) {
		for (int d = z; d < liczbaMiast - 1; d++) {
			if (z != d) {
				KopiujTablice(noweRozwiazanie, rozpatrywaneRozwiazanie);
				DokonajInwersji(noweRozwiazanie, z, d);
				//Alternatywne sposoby wyszukiwania s¹siadów:
				//DokonajZamiany(noweRozwiazanie, z, d);
				//DokonajWstawienia(noweRozwiazanie, z, d);
				ocenaRuchu = OcenaRuchu(rozpatrywaneRozwiazanie, noweRozwiazanie);
				if (ocenaRuchu > najlepszeRozwiazanie && (!(tabuList->SzukajElement(z, d)) || KryteriumAspiracji(noweRozwiazanie))) {
					najlepszeRozwiazanie = ocenaRuchu;
					ruch.miastoPoczatkowe = z;
					ruch.miastoDocelowe = d;
				}
			}
		}
	}
	delete[]noweRozwiazanie;
	DokonajZamiany(rozpatrywaneRozwiazanie, ruch.miastoPoczatkowe, ruch.miastoDocelowe);
	return ruch;
}
// Wybor sasiada poprzez poprzez zamiane
void  ProblemKomiwojazera::DokonajZamiany(int* rozwiazanie, int z, int d) {
	int tmp = rozwiazanie[d];
	rozwiazanie[d] = rozwiazanie[z];
	rozwiazanie[z] = tmp;
}
// Wybor sasiada poprzez poprzez wstawienie
void  ProblemKomiwojazera::DokonajWstawienia(int* rozwiazanie, int z, int d) {
	if (d > z) {
		int tmp = rozwiazanie[d];
		for (int i = d - 1; i >= z; i--) {
			rozwiazanie[i + 1] = rozwiazanie[i];
		}
		rozwiazanie[z] = tmp;
	}
	else if (d < z) {
		int tmp = rozwiazanie[d];
		for (int i = d; i < z - 1; i++) {
			rozwiazanie[i] = rozwiazanie[i + 1];
		}
		rozwiazanie[z - 1] = tmp;
	}
}

// Sprawdza czy nalezy zastosowac siê do listy tabu
bool  ProblemKomiwojazera::KryteriumAspiracji(int* tab) {
	if (OcenaRuchu(rozpatrywaneRozwiazanie, tab) > 0) {
		return true;
	}
	return false;
}

// Ocenia ruch ze wzglêdu na jego koszt przejscia. Im wiêkszy zwrócony wynik tym ruch jest lepszy.
// Wartosæ ujemna oznacza, ¿e otrzymane rozwiazanie jest gorsze
int ProblemKomiwojazera::OcenaRuchu(int* rozpatrywaneRozwiazanie, int* noweRozwiazanie)
{
	return ObliczKosztPrzejscia(rozpatrywaneRozwiazanie) - ObliczKosztPrzejscia(noweRozwiazanie);
}

// Metoda oblicza koszt przejscia podana jako argument œcie¿k¹ wierzcho³ków 
int ProblemKomiwojazera::ObliczKosztPrzejscia(int* rozpRozwiazanie) {
	int koszt = 0;
	koszt += miasta[0][rozpRozwiazanie[0]];

	for (int i = 0; i < liczbaMiast - 2; i++) {
		koszt += miasta[rozpRozwiazanie[i]][rozpRozwiazanie[i + 1]];
	}
	koszt += miasta[rozpRozwiazanie[liczbaMiast - 2]][0];
	return koszt;
}

// metoda rozwiazuje problem komiwojazera z wykorzystaniem algorytmu zachlannego
// zwraca wskaznik na liste bedaca rozwiazaniem problemu komiwojazera

Lista* ProblemKomiwojazera::algorytmZachlanny() {
	Lista* odwiedzoneMiasta;
	odwiedzoneMiasta = new Lista();
	odwiedzoneMiasta->dodaj(poczatek, 0);
	bool* tabMiastOdwiedzonych = new bool[liczbaMiast];
	int min;
	int rozpatrywane, docelowe;

	for (int i = 0; i < liczbaMiast; i++) {
		tabMiastOdwiedzonych[i] = false;
	}

	rozpatrywane = poczatek;

	for (int i = 0; i < liczbaMiast - 1; i++) {
		tabMiastOdwiedzonych[rozpatrywane] = true;
		min = nieskonczonosc;
		for (int n = 0; n < liczbaMiast; n++) {
			if (!tabMiastOdwiedzonych[n] && (miasta[rozpatrywane][n] < min)) {
				min = miasta[rozpatrywane][n];
				docelowe = n;
			}
		}
		odwiedzoneMiasta->dodaj(docelowe, miasta[rozpatrywane][docelowe]);
		rozpatrywane = docelowe;
	}

	odwiedzoneMiasta->dodaj(poczatek, miasta[rozpatrywane][poczatek]);
	delete[] tabMiastOdwiedzonych;
	return odwiedzoneMiasta;
}

// metoda rozwiazuje problem komiwojazera z wykorzystaniem algorytmu zachlannego
void ProblemKomiwojazera::algorytmZach(int* odwiedzoneMiasta) {
	odwiedzoneMiasta[0] = 0; 
	bool* tabMiastOdwiedzonych = new bool[liczbaMiast];
	int min;
	int rozpatrywane, docelowe;

	for (int i = 0; i < liczbaMiast; i++) {
		tabMiastOdwiedzonych[i] = false;
	}

	rozpatrywane = poczatek;

	for (int i = 0; i < liczbaMiast - 1; i++) {
		tabMiastOdwiedzonych[rozpatrywane] = true;
		min = nieskonczonosc;
		for (int n = 0; n < liczbaMiast; n++) {
			if (!tabMiastOdwiedzonych[n] && (miasta[rozpatrywane][n] < min)) {
				min = miasta[rozpatrywane][n];
				docelowe = n;
			}
		}
		odwiedzoneMiasta[i + 1] = docelowe;
		rozpatrywane = docelowe;
	}

	odwiedzoneMiasta[liczbaMiast] = 0;
	delete[] tabMiastOdwiedzonych;
}

/***********************************************************************************************************/
/* implementacja metody realizuj¹cej algorytm genetyczny                                                   */
/***********************************************************************************************************/

void ProblemKomiwojazera::algorytmGenetyczny(int * rozwiazanie)
{
	if (liczbaMiast > 3) {
		Populacja* populacja = new Populacja(miasta, liczbaMiast);
		populacja->GenerujPopulacjePoczatkowa();

		populacja->ObliczPrzystosowanieOsobnikow();
		int liczbaIteracji = 10 * liczbaMiast;
		while (liczbaIteracji > 0) {
			populacja->SeleckcjaTurniejowa();
			populacja->Krzyzowanie();
			//cout << "Przystosowanie pokolenia: " << populacja->SredniePrzystosowaniePopulacji() << endl;
			liczbaIteracji--;
		}
		populacja->ZwrocNajlepszegoOsobnika(rozwiazanie);
	}
	else {
		if (liczbaMiast != 0) {
			rozwiazanie[0] = 0;
			rozwiazanie[liczbaMiast] = 0;
			if(liczbaMiast == 2){
				rozwiazanie[1] = 1;
			}
		}		
	}
}