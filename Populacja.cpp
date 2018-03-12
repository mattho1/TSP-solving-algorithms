#include "Populacja.hpp"



Populacja::Populacja(int ** Dane, int liczbaMiast)
{
	//srand(time(NULL));
	if (liczbaMiast % 2 == 0) {
		wielkoscPopulacji = 2 * liczbaMiast + liczbaMiast / 2;
	}
	else {
		wielkoscPopulacji = 2 * liczbaMiast + (liczbaMiast / 2) + 1;
	}
	this->liczbaMiast = liczbaMiast;
	miasta = new int*[liczbaMiast];
	for (int i = 0; i < liczbaMiast; i++) {
		miasta[i] = new int[liczbaMiast];
		for (int n = 0; n < liczbaMiast; n++) {
			miasta[i][n] = Dane[i][n];
		}
	}
	osobniki = new int*[wielkoscPopulacji];
	for (int i = 0; i < wielkoscPopulacji; i++) {
		osobniki[i] = new int[liczbaMiast-1];
	}
	przystowosawnieOsobnikow = new int[wielkoscPopulacji];
	tablicaOsobnikowDoKrzyzowania = new int*[wielkoscPopulacji / 4];
	for (int i = 0; i < (wielkoscPopulacji / 4); i++) {
		tablicaOsobnikowDoKrzyzowania[i] = new int[2];
	}
	numerNajlepszegoOsobnika = -1;
	numerNajgorszegoOsobnika = -1;
}

Populacja::~Populacja()
{
	for (int i = 0; i < liczbaMiast; i++) {
		delete[]miasta[i];
	}
	delete[]miasta;
	for (int i = 0; i < wielkoscPopulacji; i++) {
		delete[]osobniki[i];
	}
	delete[]osobniki;
	for (int i = 0; i < (wielkoscPopulacji / 4); i++) {
		delete[]tablicaOsobnikowDoKrzyzowania[i];
	}
	delete[]tablicaOsobnikowDoKrzyzowania;
	delete[]przystowosawnieOsobnikow;
}

// Funkcja oblicza pierwszego osobnika z wykorzystaniem algrytmu zach³annego. Jako drugiego osobnika
// ustwaia osobnika o ci¹gu wierzcho³ków od 1 do n
void Populacja::WyliczPierwszeRozwiazania()
{
	bool* tabMiastOdwiedzonych = new bool[liczbaMiast];
	int min;
	int rozpatrywane, docelowe;
	for (int i = 0; i < liczbaMiast; i++) {
		tabMiastOdwiedzonych[i] = false;
	}
	rozpatrywane = 0;
	for (int i = 0; i < liczbaMiast - 1; i++) {
		tabMiastOdwiedzonych[rozpatrywane] = true;
		min = nieskonczonosc;
		for (int n = 0; n < liczbaMiast; n++) {
			if (!tabMiastOdwiedzonych[n] && (miasta[rozpatrywane][n] < min)) {
				min = miasta[rozpatrywane][n];
				docelowe = n;
			}
		}
		osobniki[0][i] = docelowe;
		rozpatrywane = docelowe;
	}
	delete[] tabMiastOdwiedzonych;
	for (int i = 1; i < liczbaMiast; i++) {
		osobniki[1][i-1] = i;
	}
}
// Funkcja generuje populacje poczatkowa z drugiego osobnika stworzonego w funkcj WyliczPierwszeRozwiazania
// Tworzy osobniki poprzez wykonanie okreœlonej liczby inwersji, zamian, wstawieñ na osobniku bazowym.
void Populacja::GenerujPopulacjePoczatkowa()
{
	WyliczPierwszeRozwiazania();
	for (int i = 2; i < wielkoscPopulacji; i++) {
		KopiujTablice(osobniki[i],osobniki[1]);
		for (int j = 0; j < 20; j++) {
			DokonajInwersji(osobniki[i]);
			DokonajZamiany(osobniki[i]);
			DokonajWstawienia(osobniki[i]);
		}
	}
}
// Funkcja umo¿liwiaj¹ca wyswietlenie przystosowania wszystkich osobników do œrodowiska
void Populacja::TestoweWyswietlenieCalejPopulacji() {
	ObliczPrzystosowanieOsobnikow();
	for (int i = 0; i < wielkoscPopulacji; i++) {
		cout << "Przystosowanie = " << przystowosawnieOsobnikow[i] << "  ";
		pomocniczeWyswietlanieOsobnika(osobniki[i]);
	}
}
// Funkcja pomocnicza do wyœwietlenia œcie¿ki reprezentowanej przez osobnika 
void Populacja::pomocniczeWyswietlanieOsobnika(int* testowaTablica)
{
	cout << endl << "Trasa = ";
	cout << testowaTablica[0] << " - ";
	for (int i = 1; i < liczbaMiast - 1; i++) {
		cout << testowaTablica[i];
		if (i != liczbaMiast - 1) {
			cout << " - ";
		}
	}
	cout << endl;
}
// Funkcja uzupe³niaj¹ca tablice zmieniana wartoœciami tablicy wartoœci
void Populacja::KopiujTablice(int* zmieniana, int* wartosci) {
	for (int i = 0; i < liczbaMiast - 1; i++) {
		zmieniana[i] = wartosci[i];
	}
}
// Funkcja wykorzystywana do mutacji losuje wierzcho³ek który ma zostaæ wstawiony w wylosowane miejsce 
void  Populacja::DokonajWstawienia(int* rozwiazanie) {
	Zamiana miejsca = LosujMiejsca();
	if (miejsca.d > miejsca.z) {
		int tmp = rozwiazanie[miejsca.d];
		for (int i = miejsca.d - 1; i >= miejsca.z; i--) {
			rozwiazanie[i + 1] = rozwiazanie[i];
		}
		rozwiazanie[miejsca.z] = tmp;
	}
	else if (miejsca.d < miejsca.z) {
		int tmp = rozwiazanie[miejsca.d];
		for (int i = miejsca.d; i < miejsca.z - 1; i++) {
			rozwiazanie[i] = rozwiazanie[i + 1];
		}
		rozwiazanie[miejsca.z - 1] = tmp;
	}
}
// Funkcja wykonuje inwersje na tablicy otrzymanej jako argument
// Funkcja losuje wierzcho³ki wzglêdem których zostanie wykonana inwersja
void Populacja::DokonajInwersji(int* rozwiazanie) {
	Zamiana miejsca = LosujMiejsca();
	int granica = ceil((double)(miejsca.z + miejsca.d) / 2);
	for (int i = miejsca.z, j = miejsca.d; i < granica; i++, j--) {
		int tmp = rozwiazanie[j];
		rozwiazanie[j] = rozwiazanie[i];
		rozwiazanie[i] = tmp;
	}
}
// Funkcja dokonuje zamiany dwóch wierzcho³ków w tablicy otrzymanej jako argument.
// Funkcja losuje wierzcho³ki do zamiany.
void  Populacja::DokonajZamiany(int* rozwiazanie) {
	Zamiana miejsca = LosujMiejsca();
	int tmp = rozwiazanie[miejsca.d];
	rozwiazanie[miejsca.d] = rozwiazanie[miejsca.z];
	rozwiazanie[miejsca.z] = tmp;
}

// Metoda losuje ruch z przedzia³u od 0 do liczbyMiast - 1
Zamiana Populacja::LosujMiejsca() {
	Zamiana miejsca;
	miejsca.z = (std::rand() % (liczbaMiast - 1));
	miejsca.d = (std::rand() % (liczbaMiast - 1));
	while (miejsca.z == miejsca.d) {
		miejsca.d = (std::rand() % (liczbaMiast - 1));
	}
	if (miejsca.z > miejsca.d) {
		int tmp = miejsca.d;
		miejsca.d = miejsca.z;
		miejsca.z = tmp;
	}
	return miejsca;
}
// Funkcja realizuj¹ca operacje selekcji turniejowej
void Populacja::SeleckcjaTurniejowa()
{
	int liczebnoscPomniejszonejPopulacji = wielkoscPopulacji;
	int tmpLczebnosc = liczebnoscPomniejszonejPopulacji;
	int* losoweOsobniki = new int[wielkoscTurnieju];
	int losowyOsobnik;
	int zwyciescaTurnieju;
	int min = nieskonczonosc;
	int* tablicaNieWybranychOsobnikow = new int[wielkoscPopulacji];
	
	for (int i = 0; i < wielkoscPopulacji; i++) {
		tablicaNieWybranychOsobnikow[i] = i;
	}
	for (int i = 0; i < wielkoscPopulacji / 4; i++) {
		for (int j = 0; j < 2; j++) {
			min = nieskonczonosc;
			for (int n = 0; n < wielkoscTurnieju; n++) {
				losowyOsobnik = (std::rand() % (liczebnoscPomniejszonejPopulacji - 1));
				if (przystowosawnieOsobnikow[tablicaNieWybranychOsobnikow[losowyOsobnik]] < min) {
					min = przystowosawnieOsobnikow[losowyOsobnik];
					zwyciescaTurnieju = tablicaNieWybranychOsobnikow[losowyOsobnik];
					tablicaNieWybranychOsobnikow[losowyOsobnik] = tablicaNieWybranychOsobnikow[liczebnoscPomniejszonejPopulacji - 1];
					tablicaNieWybranychOsobnikow[liczebnoscPomniejszonejPopulacji - 1] = zwyciescaTurnieju;
				}
			}
			--liczebnoscPomniejszonejPopulacji;
			tablicaOsobnikowDoKrzyzowania[i][j] = zwyciescaTurnieju;
		}
	}
	delete[]tablicaNieWybranychOsobnikow;
	delete[]losoweOsobniki;
}
// Funkcja oblicza przystosowanie osobników populacji. Uzupe³nia tablicê przystosowanieOsobnikow
// Wyszukuje najgorszego osbnik i najlepszego
void Populacja::ObliczPrzystosowanieOsobnikow() {
	int max = 0, min = nieskonczonosc;
	for (int i = 0; i < wielkoscPopulacji; i++) {
		przystowosawnieOsobnikow[i] = OcenaPrzystosowania(osobniki[i]);
		if (przystowosawnieOsobnikow[i] > max) {
			max = przystowosawnieOsobnikow[i];
			numerNajgorszegoOsobnika = i;
		}
		if (przystowosawnieOsobnikow[i] < min) {
			min = przystowosawnieOsobnikow[i];
			numerNajlepszegoOsobnika = i;
		}
	}
}
// Funkcja ocenia przystosowanie osobnika podanego jako argument funkcji.
int Populacja::OcenaPrzystosowania(int * osobnik) {
	int kosztPrzejscia = 0;
	kosztPrzejscia += miasta[0][osobnik[0]];
	for (int i = 1; i < liczbaMiast - 1; i++) {
		kosztPrzejscia += miasta[osobnik[i - 1]][osobnik[i]];
	}
	kosztPrzejscia += miasta[osobnik[liczbaMiast - 2]][0];
	return kosztPrzejscia;
}
// Funkcja zapisuje ci¹g wierzcho³ków reprezentowany przez najlepszego osbnika 
//	do tablicy podanej jako argument. Uzupe³nia rozwiazanie o miasto pocz¹tkowe 
void Populacja::ZwrocNajlepszegoOsobnika(int* rozwiazanie) { // nie testowana
	rozwiazanie[0] = 0;
	for (int i = 1; i < liczbaMiast; i++) {
		rozwiazanie[i] = osobniki[numerNajlepszegoOsobnika][i - 1];
	}
	rozwiazanie[liczbaMiast] = 0;
}
// Funkcja oblicza czy wykonaæ krzy¿owanie z prawdopodobieñstwem prawdopodobienstwoKrzyzowania
bool Populacja::CzyKrzyzowanie() {
	int przedzial = 10000;
	int wylosowanaLiczba = (rand() % (10000 - 1));
	int przedzialTrafienia = przedzial * prawdopodobienstwoKrzyzowania;
	if (wylosowanaLiczba < (przedzialTrafienia - 1) && wylosowanaLiczba > 0) {
		return true;
	}
	else {
		return false;
	}
}
// Funkcja zarz¹dza operacj¹ krzy¿owania i mutacji. Dodaje potomkow do populacji.
void Populacja::Krzyzowanie() {
	Potomkowie* potomkowie;
	int liczbaParPotomkow = 0;
	potomkowie = new Potomkowie[(wielkoscPopulacji / 4)];
	for (int i = 0; i < (wielkoscPopulacji / 4); i++) {
		potomkowie[i].pierwszeDziecko = new int[liczbaMiast - 1];
		potomkowie[i].drugieDziecko = new int[liczbaMiast - 1];
	}

	for (int i = 0; i < (wielkoscPopulacji / 4); i++) {
		if (CzyKrzyzowanie()) {
			KrzyzowanieOX(potomkowie[liczbaParPotomkow], osobniki[tablicaOsobnikowDoKrzyzowania[i][0]], osobniki[tablicaOsobnikowDoKrzyzowania[i][1]]);
			liczbaParPotomkow++;
		}
	}
	for (int i = 0; i < liczbaParPotomkow; i++) {
		if (CzyMutacja()) {
			Mutacja(potomkowie[i].pierwszeDziecko);
		}
		DodajNowegoOsobnikaDoPopulacji(potomkowie[i].pierwszeDziecko);
		if (CzyMutacja()) {
			Mutacja(potomkowie[i].drugieDziecko);
		}
		DodajNowegoOsobnikaDoPopulacji(potomkowie[i].drugieDziecko);
	}
	for (int i = 0; i < (wielkoscPopulacji / 4); i++) {
		delete[]potomkowie[i].pierwszeDziecko;
		delete[]potomkowie[i].drugieDziecko;
	}
	delete[]potomkowie;
}
// Funkcja realizuje krzy¿owanie OX.
void Populacja::KrzyzowanieOX(Potomkowie& potomkowie, int* pierwszyRodzic, int* drugiRodzic) {
	Zamiana graniceSekcjiDopasowania = LosujMiejsca();
	for (int i = graniceSekcjiDopasowania.z; i < graniceSekcjiDopasowania.d + 1; i++) {
		potomkowie.pierwszeDziecko[i] = drugiRodzic[i];
		potomkowie.drugieDziecko[i] = pierwszyRodzic[i];
	}
	int dlSekcjiDopasowania = graniceSekcjiDopasowania.d - graniceSekcjiDopasowania.z;
	int* wierzcholkiNieWykorzystanePierwszyRodzic = new int[liczbaMiast - 1 - dlSekcjiDopasowania];
	int* wierzcholkiNieWykorzystaneDrugiRodzic = new int[liczbaMiast - 1 - dlSekcjiDopasowania];
	for (int i = 0, j = graniceSekcjiDopasowania.d + 1, n = graniceSekcjiDopasowania.d + 1; i < liczbaMiast - 1; i++) {
		if (j == liczbaMiast - 1) {
			j = 0;
		}
		if (n == liczbaMiast - 1) {
			n = 0;
		}
		if (SprawdzCzyMoznaWstawic(graniceSekcjiDopasowania.z, graniceSekcjiDopasowania.d,
			drugiRodzic, pierwszyRodzic[n])) {
			potomkowie.pierwszeDziecko[j] = pierwszyRodzic[n];
			j++;
		}
		n++;
	}
	for (int i = 0, j = graniceSekcjiDopasowania.d + 1, n = graniceSekcjiDopasowania.d + 1; i < liczbaMiast - 1; i++) {
		if (j == liczbaMiast - 1) {
			j = 0;
		}
		if (n == liczbaMiast - 1) {
			n = 0;
		}
		if (SprawdzCzyMoznaWstawic(graniceSekcjiDopasowania.z, graniceSekcjiDopasowania.d,
			pierwszyRodzic, drugiRodzic[n])) {
			potomkowie.drugieDziecko[j] = drugiRodzic[n];
			j++;
		}
		n++;
	}
	delete[]wierzcholkiNieWykorzystanePierwszyRodzic;
	delete[]wierzcholkiNieWykorzystaneDrugiRodzic;
}
// Funkcja pomocnicza sprawdza czy wierzcho³ek o numerze podanym w zmiennej wartoscSprawdzana 
// znajduje sie w tablicy tablica w przedziale od poczatek do koniec.
bool Populacja::SprawdzCzyMoznaWstawic(int poczatek, int koniec, int*tablica, int wartoscSprawdzana) {
	for (int i = poczatek; i < koniec + 1; i++) {
		if (wartoscSprawdzana == tablica[i]) {
			return false;
		}
	}
	return true;
}
// Funkcja realizuj¹ca próbê dodania nowego osobnika do populacji
// Dodaje osobnika poprzez usuniêcie najgorszego. Dodaje osobnika 
// gdy nowy osobnik lepiej przystosowany od najgorszego osobnika.
void Populacja::DodajNowegoOsobnikaDoPopulacji(int* nowyOsobnik) {
	int przystosowanieNowegoOsobnika = OcenaPrzystosowania(nowyOsobnik);
	if (przystosowanieNowegoOsobnika < przystowosawnieOsobnikow[numerNajgorszegoOsobnika]) { // mniejszy bo minimalizujemy 
		if (przystosowanieNowegoOsobnika < przystowosawnieOsobnikow[numerNajlepszegoOsobnika]) {
			KopiujTablice(osobniki[numerNajgorszegoOsobnika], osobniki[numerNajlepszegoOsobnika]);
			KopiujTablice(osobniki[numerNajlepszegoOsobnika], nowyOsobnik);
			przystowosawnieOsobnikow[numerNajgorszegoOsobnika] = przystowosawnieOsobnikow[numerNajlepszegoOsobnika];
			przystowosawnieOsobnikow[numerNajlepszegoOsobnika] = przystosowanieNowegoOsobnika;
		}
		else {
			KopiujTablice(osobniki[numerNajgorszegoOsobnika], nowyOsobnik);
			przystowosawnieOsobnikow[numerNajgorszegoOsobnika] = przystosowanieNowegoOsobnika;
		}
		numerNajgorszegoOsobnika = ZnajdzNajgorszegoOsobnika();
	}
}
// Funkcja wyszukuje pozycje w populacji najgorszego osobnika
int Populacja::ZnajdzNajgorszegoOsobnika() {
	int max = 0;
	int pozycja;
	for (int i = 0; i < wielkoscPopulacji; i++) {
		if (przystowosawnieOsobnikow[i] > max) {
			pozycja = i;
			max = przystowosawnieOsobnikow[i];
		}
	}
	return pozycja;
}
//	Funkcja okresla czy wykonaæ mutacjê z prawdopodobieñstwem prawdopodobienstwoMutacji.
bool Populacja::CzyMutacja() {
	int przedzial = 10000;
	int wylosowanaLiczba = (rand() % (10000 - 1));
	int przedzialTrafienia = przedzial * prawdopodobienstwoMutacji;
	if (wylosowanaLiczba < (przedzialTrafienia - 1) && wylosowanaLiczba > 0) {
		return true;
	}
	else {
		return false;
	}
}
// Funkcja wykonuje mutacjê.
void Populacja::Mutacja(int * osobnik) {
	DokonajInwersji(osobnik);
}
// Funkcja oblicza œrednie przystosowanie populacji.
float Populacja::SredniePrzystosowaniePopulacji() {
	float srednia = 0;
	for (int i = 0; i < wielkoscPopulacji; i++) {
		srednia += przystowosawnieOsobnikow[i];
	}
	srednia = srednia / (float)wielkoscPopulacji;
	return srednia;
}