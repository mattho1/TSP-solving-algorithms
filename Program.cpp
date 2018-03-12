#include "Program.hpp"

Program::Program() {
	srand((int)time(NULL));
}

Program::~Program() {
	for (int i = 0; i<liczbaMiast; i++) {
		delete[]dane[i];
	}
	if (czyodwiedzonemiasta) {
		delete odwiedzoneMiasta;
	}
	delete[]dane;
	delete problemKomiwojazera;
}

// metoda menu obsluguje komunikacje z uzytkownikiem 
// i pozwala na pokierowanie dzialaniem programu
// zarzadza dzialaniem programu i wybieraniem wykonywanych dzialan

void Program::menu() {
	long long int frequency, start, elapsed;
	double wynikczasowy;

	int wyborOpcji, wyborPrezentacji, wyborRozszerzenia;
	int wyjscieZProgramu;
	int lMiast;
	float sredniCzas = 0;
	float sredniWynik = 0;
	czyodwiedzonemiasta = false;
	string nazwaPliku;
	bool czyOtwartyPlik, czyDobraOpcja;

	do {
		czyDobraOpcja = true;
		cout << endl << "[1] test" << endl << "[2] prezentacja" << endl << "Wybor opcji: ";
		cin >> wyborPrezentacji;
		cout << endl;
		if (wyborPrezentacji == 0) {
			exit(0);
		}
		if (wyborPrezentacji != 1 && wyborPrezentacji != 2) {
			cout << "Wybrana zla opcja. Prosze sprobowac ponownie" << endl;
			cout << "Zamkniecie programu po wpisaniu wartosci 0" << endl;
			czyDobraOpcja = false;
		}
	} while (!czyDobraOpcja);


	do {
		wyjscieZProgramu = 1;
		if (wyborPrezentacji == 1) {
			cout << endl << "Podaj ilosc miast: " << endl;
			cin >> lMiast;
			if (!generator(lMiast)) {
				cout << endl << "Nie mozna wygenerowac danych o podanych parametrach.";
				cout << " Upewnij sie czy podana wielkosc jest wieksza od zera. " << endl;
				cout << " Program zostanie zamkniety. " << endl;
				_getch();
				exit(0);
			}

			if (!pobierzDane("DanePK", 1)) {
				cout << endl << "Plik z danymi nie zostal poprawnie otwarty. Sprawdz czy istnieje plik o podanej nazwie ";
				cout << "jezeli nie to uruchom ponownie i podaj poprawna nazwe pliku. [poprawna nazwa to DanePK.txt]" << endl;
				cout << " Program zostanie zamkniety. " << endl;
				_getch();
				exit(0);
			}

		}
		else {
			do {
				cout << endl << "Podaj nazwe pliku z danymi [bez rozszerzenia]: " << endl;
				cin >> nazwaPliku;
				if (nazwaPliku == "exit" || nazwaPliku == "Exit" || nazwaPliku == "EXIT") {
					exit(0);
				}
				cout << endl << "[0] xml" << endl << "[1] txt" << endl << "Wybor rozszerzenia pliku: ";
				cin >> wyborRozszerzenia;

				czyOtwartyPlik = pobierzDane(nazwaPliku, wyborRozszerzenia);
				if (!czyOtwartyPlik) {
					cout << endl << "Plik z danymi nie zostal poprawnie otwarty. Sprawdz czy istnieje plik o podanej nazwie: ";
					cout << nazwaPliku << endl;
					cout << endl << "W celu wyjscia z programu wpisz: exit" << endl;
					_getch();
				}
			} while (!czyOtwartyPlik);
		}
		problemKomiwojazera = new ProblemKomiwojazera(dane, liczbaMiast, poczatek);
		do {
			cout << endl << endl << "Wybierz czynnosc dla danego problemu." << endl;
			cout << "[1] wyswietl dane" << endl << "[2] rozwiaz problem - algorytm przeglad zupelny" << endl;
			cout << "[3] rozwiaz problem - algorytm podzialu i ograniczen" << endl << "[4] rozwiaz problem - algorytm Tabu Search"
				<< endl << "[5] rozwiaz problem - algorytm Zachlanny" << endl << "[6] rozwiaz problem - algorytm Genetyczny" << endl << "[11] cofnij do wprowadzania danych" << endl << "[0] zakoncz program" << endl << "Wybor opcji: ";
			cin >> wyborOpcji;
			switch (wyborOpcji) {
			case 0:
				wyborOpcji = 0;
				wyjscieZProgramu = 0;
				break;
			case 1:
				wyswietlDane();
				break;
				break;
			case 2:
				wynikczasowy = 0;
				QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
				start = read_QPC();
				odwiedzoneMiasta = problemKomiwojazera->algorytmPrzegladZupelny();
				elapsed = read_QPC() - start;
				wynikczasowy = ((1.0 * elapsed) / frequency);
				cout << "Czas [s] = " << setprecision(6) << wynikczasowy << endl;
				czyodwiedzonemiasta = true;
				wyswietlPK();
				break;
			case 3:
				rozwiazanie = new int[liczbaMiast + 1];
				QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
				start = read_QPC();
				problemKomiwojazera->algorytmPodzialuIOgraniczen(rozwiazanie);
				elapsed = read_QPC() - start;
				wynikczasowy = ((1.0 * elapsed) / frequency);
				cout << "Czas [s] = " << setprecision(6) << wynikczasowy << endl;
				wyswietlRozwiazanie();
				break;
			case 4:
				rozwiazanie = new int[liczbaMiast + 1];
				QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
				start = read_QPC();
				problemKomiwojazera->algorytmTabuSerach(rozwiazanie);
				elapsed = read_QPC() - start;
				wynikczasowy = ((1.0 * elapsed) / frequency);
				cout << "Czas [s] = " << setprecision(6) << wynikczasowy << endl;
				wyswietlRozwiazanie();
				break;
			case 5:
				wynikczasowy = 0;
				QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
				start = read_QPC();
				odwiedzoneMiasta = problemKomiwojazera->algorytmZachlanny();
				elapsed = read_QPC() - start;
				wynikczasowy = ((1.0 * elapsed) / frequency);
				cout << "Czas [s] = " << setprecision(6) << wynikczasowy << endl;
				czyodwiedzonemiasta = true;
				wyswietlPK();
				break;
			case 6:
				rozwiazanie = new int[liczbaMiast + 1];
				QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
				start = read_QPC();
				problemKomiwojazera->algorytmGenetyczny(rozwiazanie);
				elapsed = read_QPC() - start;
				wynikczasowy = ((1.0 * elapsed) / frequency);
				cout << "Czas [s] = " << setprecision(6) << wynikczasowy << endl;
				wyswietlRozwiazanie();
				break;
			case 11:
				wyborOpcji = 0;
				wyjscieZProgramu = 1;
				if (czyodwiedzonemiasta) {
					delete odwiedzoneMiasta;
					czyodwiedzonemiasta = false;
				}
				for (int i = 0; i<liczbaMiast; i++) {
					delete[]dane[i];
				}
				delete[]dane;
				delete problemKomiwojazera;
				break;
			default:
				cout << endl << "Podano niepoprawna opcje." << endl;
				wyborOpcji = -1;
				break;
			}
		} while (wyborOpcji != 0);


	} while (wyjscieZProgramu != 0);
}
// metoda pobierzDane pobiera dane z pliku ktorego nazwe dostaje jako argument
// argument wybor okresla czy dane sa wczytywane z pliku txt czy z xml
// 0 plik xml
// 1 plik txt
// metoda zwraca wartosc logiczna okreslajaca czy dane zostaly pobrane poprawnie

bool Program::pobierzDane(string nazwaPliku, int wybor) {
	if (wybor == 0) {
		nazwaPliku = nazwaPliku + ".xml";
		ifstream file(nazwaPliku.c_str());
		if (!file) {
			return false;
		}
		file.seekg(0, file.end);
		const auto fileSize = file.tellg();
		file.seekg(0);

		unique_ptr < char[] > xmlFileContext(new char[(unsigned int)(fileSize + static_cast < decltype(fileSize) >(1))]);
		file.read(xmlFileContext.get(), fileSize);

		xml_document <> document;
		document.parse < 0 >(xmlFileContext.get()); // <0>

		xml_node <>* wezelPoczatkowy = document.first_node();

		xml_node <>* wezelPrzejsciowy = wezelPoczatkowy->first_node();
		for (int a = 0; a < 5; a++, wezelPrzejsciowy = wezelPrzejsciowy->next_sibling()) {}
		xml_node <>* wyznaczanieWielkosci = wezelPrzejsciowy->first_node()->last_node();
		liczbaMiast = atoi(wyznaczanieWielkosci->value()) + 1;
		dane = new int*[liczbaMiast];
		for (int i = 0; i < liczbaMiast; i++) {
			dane[i] = new int[liczbaMiast];
		}
		int i = 0;
		for (xml_node <>* vertex = wezelPrzejsciowy->first_node(); vertex; i++, vertex = vertex->next_sibling()) { //vertex
			for (xml_node <>* edge = vertex->first_node(); edge; edge = edge->next_sibling()) { // edge
				dane[i][atoi(edge->value())] = (int)atof(edge->first_attribute()->value());
			}
			dane[i][i] = 0;
		}
		file.close();
		return true;
	}
	else {
		ifstream plik;
		nazwaPliku = nazwaPliku + ".txt";
		plik.open(nazwaPliku);

		if (plik.good()) {
			plik >> liczbaMiast;
			dane = new int*[liczbaMiast];
			for (int i = 0; i < liczbaMiast; i++) {
				dane[i] = new int[liczbaMiast];
			}
			for (int i = 0; i < liczbaMiast; i++) {
				for (int n = 0; n < liczbaMiast; n++) {
					plik >> dane[i][n];
				}
			}
			poczatek = 0;

		}
		else {
			return false;
		}
		plik.close();
		return true;
	}
}

// metoda wyswietla wyniki rozwiazania problemu komiwoja¿era

void Program::wyswietlPK() {
	odwiedzoneMiasta->wyswietl();
}

// generator generuje dane losowe do testowania algorytmow rozwiazujacych problemy
// rodzaj - [true] problem plecakowy [false] problem komiwoja¿era
// metoda zwraca jako wynik wartosc logiczna okreslajaca czy wygenerowanie danych zostalo wykonane poprawnie
// metoda zapisuje wygenerowane dane odpowiednio do pliku DanePP.txt lub DanePK.txt

bool Program::generator(int wielkosc) {
	if (wielkosc < 0) return false;
	fstream plik;
	plik.open("DanePK.txt", ios::out);
	if (plik.good()) {
		plik << wielkosc << endl;
		for (int i = 0; i < wielkosc; i++) {
			for (int n = 0; n < wielkosc; n++) {
				if (i != n) {
					plik << (rand() % (3 * wielkosc)) + 5 << " ";
				}
				else {
					plik << 0 << " ";
				}
			}
			plik << endl;
		}

		plik.close();
	}
	else {
		return false;
	}

	return true;
}

// Metoda wyswietla rozwiazanie i oblicza dlugosc trasy rozwiazania
void Program::wyswietlRozwiazanie()
{
	int calkowityKoszt = 0;
	cout << endl << "Trasa = ";
	cout << rozwiazanie[0] << " - ";
	for (int i = 1; i < liczbaMiast + 1; i++) {
		cout << rozwiazanie[i];
		calkowityKoszt += dane[rozwiazanie[i - 1]][rozwiazanie[i]];
		if (i != liczbaMiast) {
			cout << " - ";
		}
	}
	delete[]rozwiazanie;
	cout << endl << "Dlugosc trasy = " << calkowityKoszt << endl;
	cout << endl;
}

// Metoda wyswietla dane wprowadzone do programu
void Program::wyswietlDane()
{
	cout << endl << "Liczba miast: " << liczbaMiast << endl;
	cout << endl << "Miasto startowe: " << poczatek << endl << endl;
	for (int i = 0; i < liczbaMiast; i++) {

		for (int n = 0; n < liczbaMiast; n++) {

			if ((dane[i][n] / 100) != 0) {
				cout << dane[i][n];
			}
			else if ((dane[i][n] / 10) != 0) {
				cout << " " << dane[i][n];
			}
			else {
				cout << " " << " " << dane[i][n];
			}
			if (n != (liczbaMiast - 1)) {
				cout << " ";
			}
		}
		cout << endl;
	}
}

// Metoda do obliczania czasu dzialania algorytmu 
long long int Program::read_QPC() {
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}
