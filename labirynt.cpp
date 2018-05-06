#include<iostream>
#include<conio.h> //chcemy getch()

using namespace std;

//wymiary mapy labiryntu
const int height = 8;
const int width = 10;
const int utrata_ruch = 15, utrata_obrot = 10, utrata_swiatlo = 10, utrata_skok = 20, utrata_czekaj = 5, utrata_kolizja = 5, zasieg_swiatla = 2;


//elementy labiryntu
char sciana = '#', koryt = '.', szczel = 'S', wyjscie = 'W', start = 'P';
//mapa labiryntu
char mapa[height*width] = { sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana,
							sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana,
							sciana, sciana, sciana, sciana,	koryt,	koryt,	koryt,	koryt,	koryt,	sciana,
							sciana, sciana, start,	sciana,	koryt,	sciana, sciana,	koryt,	sciana, sciana,
							sciana, sciana, koryt,	szczel,	koryt,	szczel,	szczel,	koryt,	koryt,	wyjscie,
							sciana,	sciana, sciana, sciana, sciana, sciana,	sciana,	sciana, sciana, sciana,
							sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana,
							sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana, sciana,
};

//zmienne przechowujace aktualna pozycje gracza;
int pos_x, pos_y;

//ustalamy pozycje startowa gracza w zaleznosci od mapy
void znajdzStart() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (mapa[i*width + j] == start) {
				pos_x = j;
				pos_y = i;
			}
		}
	}
}

void rysujLabirynt() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {				
			cout.width(2);
			cout << mapa[i*width + j];
		}
		cout << endl;
	}
}

enum kierunki {
	LEWO = 0,
	PRAWO,
	GORA,
	DOL
};

void okreslCoPrzed(int aktualny_kierunek) {
	
	if (aktualny_kierunek == LEWO	&& mapa[pos_y*width + pos_x - 1] == sciana ||
		aktualny_kierunek == PRAWO	&& mapa[pos_y*width + pos_x + 1] == sciana ||
		aktualny_kierunek == GORA	&& mapa[(pos_y - 1)*width + pos_x] == sciana ||
		aktualny_kierunek == DOL	&& mapa[(pos_y + 1)*width + pos_x] == sciana) {
		cout << "Jestes w ciemnej jaskini przed Toba sciana" << endl;
	}	
	else if (aktualny_kierunek == LEWO	&& mapa[pos_y*width + pos_x - 1] == szczel ||
		aktualny_kierunek == PRAWO		&& mapa[pos_y*width + pos_x + 1] == szczel ||
		aktualny_kierunek == GORA		&& mapa[(pos_y - 1)*width + pos_x] == szczel ||
		aktualny_kierunek == DOL		&& mapa[(pos_y + 1)*width + pos_x] == szczel) {		
		cout << "Jestes w ciemnej jaskini Przed Toba szczelina" << endl;
	}	
	else if (aktualny_kierunek == LEWO		&& mapa[pos_y*width + pos_x - 1] == wyjscie ||
		aktualny_kierunek == PRAWO		&& mapa[pos_y*width + pos_x + 1] == wyjscie ||
		aktualny_kierunek == GORA		&& mapa[(pos_y - 1)*width + pos_x] == wyjscie ||
		aktualny_kierunek == DOL		&& mapa[(pos_y + 1)*width + pos_x] == wyjscie) {
		cout << "Jestes w ciemnej jaskini przed Toba wyjscie" << endl;		
	}
	else if (aktualny_kierunek == LEWO		&& mapa[pos_y*width + pos_x - 1] == koryt ||
		aktualny_kierunek == PRAWO		&& mapa[pos_y*width + pos_x + 1] == koryt ||
		aktualny_kierunek == GORA		&& mapa[(pos_y - 1)*width + pos_x] == koryt ||
		aktualny_kierunek == DOL		&& mapa[(pos_y + 1)*width + pos_x] == koryt) {
		cout << "Jestes w ciemnej jaskini przed Toba korytarz" << endl;
	}
}



int main()
{
	int pkt_energii = 400, skok = 2, liczba_swiatelek = 3;
	
	int aktualny_kierunek = GORA;	
	char wybrana_opcja;	
	char co_przed;
	char obrot_lewo = 'L', obrot_prawo = 'P', ruch = 'N', skacz = 'J', swiatlo = 'S', czekaj = 'W', koniec_gry = 'Q';
	//do testow
	rysujLabirynt();
	bool wygrana = false;
	bool czy_zyje = true;
	znajdzStart(); //przypisanie aktualnej pozycji zmiennym okreslajacym polozenie gracza

	while (wygrana == false && czy_zyje == true) {
		//wyswietlenie stanu gry
		cout << endl << endl;
		okreslCoPrzed(aktualny_kierunek); //wypisuje co mamy przed soba		
		cout << "Masz " << pkt_energii << " pkt. energii, " << liczba_swiatelek << " swiatelka." << endl;
		cout << " Co robisz: (L/P/N/J/S/W)?: "; //L-obrot w lewo, P-obrot w prawo, N-ruch, S-swiatelko, W-czekaj, J-skacz; 
		wybrana_opcja = _getch(); // cin >> wybrana_opcja; // zatwierdzic eneterem wtedy trzeba //_getch() po to zeby nie trzeba bylo naciskac entera
		//system("cls");
		//chcemy sie obroc w lewo
		if (wybrana_opcja == obrot_lewo) {
			cout << "Obrot lewo " << endl;
			pkt_energii -= utrata_obrot;
			if (aktualny_kierunek == LEWO) aktualny_kierunek = DOL;
			else if (aktualny_kierunek == DOL) aktualny_kierunek = PRAWO;
			else if (aktualny_kierunek == PRAWO) aktualny_kierunek = GORA;
			else if (aktualny_kierunek == GORA) aktualny_kierunek = LEWO;
		}
		//chcemy sie obrocic w prawo
		else if (wybrana_opcja == obrot_prawo) {
			pkt_energii -= utrata_obrot;
			cout << "Obrot prawo " << endl;
			if (aktualny_kierunek == LEWO) aktualny_kierunek = GORA;
			else if (aktualny_kierunek == DOL) aktualny_kierunek = LEWO;
			else if (aktualny_kierunek == PRAWO) aktualny_kierunek = DOL;
			else if (aktualny_kierunek == GORA) aktualny_kierunek = PRAWO;
		}
		//chcemy isc naprzod
		else if (wybrana_opcja == ruch) {//rozpatrujemy wszystkie mozliwe zdarzenia
			pkt_energii -= utrata_ruch;
			cout << "Naprzod " << endl;
			//chcemy isc ale jest sciana
			if (aktualny_kierunek == LEWO	&& mapa[pos_y*width + pos_x - 1] == sciana ||
				aktualny_kierunek == PRAWO	&& mapa[pos_y*width + pos_x + 1] == sciana ||
				aktualny_kierunek == GORA	&& mapa[(pos_y-1)*width + pos_x] == sciana || 
				aktualny_kierunek == DOL	&& mapa[(pos_y+1)*width + pos_x] == sciana) {
				cout << "Uderzasz glowa w sciane tracisz 5 pkt";
				pkt_energii -= utrata_kolizja;
			}
			//chcemy isc ale jest szczelina
			else if (aktualny_kierunek == LEWO	&& mapa[pos_y*width + pos_x - 1] == szczel ||
				aktualny_kierunek == PRAWO		&& mapa[pos_y*width + pos_x + 1] == szczel ||
				aktualny_kierunek == GORA		&& mapa[(pos_y - 1)*width + pos_x] == szczel ||
				aktualny_kierunek == DOL		&& mapa[(pos_y + 1)*width + pos_x] == szczel) {
				cout << "Wpadles do szczeliny. Koniec gry!";
				czy_zyje = false;
			}
			//chcemy isc ale jest wyjscie to wygralismy
			else if (aktualny_kierunek == LEWO		&& mapa[pos_y*width + pos_x - 1]   == wyjscie ||
					aktualny_kierunek == PRAWO		&& mapa[pos_y*width + pos_x + 1]   == wyjscie ||
					aktualny_kierunek == GORA		&& mapa[(pos_y - 1)*width + pos_x] == wyjscie ||
					aktualny_kierunek == DOL		&& mapa[(pos_y + 1)*width + pos_x] == wyjscie) {
					cout << "Udalo Ci sie wyjsc z labiryntu, Gratulacje! Koniec gry!";
					wygrana = true;
			}
			//mozemy swobodnie przjesc dalej
			else if (aktualny_kierunek == LEWO && mapa[pos_y*width + pos_x - 1] == koryt)	pos_x -= 1; //idziemy w lewo
			else if (aktualny_kierunek == PRAWO && mapa[pos_y*width + pos_x + 1] == koryt)	pos_x += 1;//idziemy w prawo
			else if (aktualny_kierunek == GORA && mapa[(pos_y - 1)*width + pos_x] == koryt) pos_y -= 1;//idziemy w gore
			else if (aktualny_kierunek == DOL && mapa[(pos_y + 1)*width + pos_x] == koryt)	pos_y += 1;//idziemy w dol				
			
		}
		//chcemy przeskoczyc
		else if (wybrana_opcja == skacz) {
			pkt_energii -= utrata_skok;
			cout << "Skok " << endl;
			//sprawdzamy czy nie wpadniemy na sciane
			if (aktualny_kierunek == LEWO	&& pos_x-skok >=0		&& mapa[pos_y*width + pos_x - skok] == sciana ||
				aktualny_kierunek == PRAWO	&& pos_x+skok<width		&& mapa[pos_y*width + pos_x + skok] == sciana ||
				aktualny_kierunek == GORA	&& pos_y-skok>=0		&& mapa[(pos_y - skok)*width + pos_x] == sciana ||
				aktualny_kierunek == DOL	&& pos_y+skok<height	&& mapa[(pos_y + skok)*width + pos_x] == sciana) {
					cout << "Wpadles do szczeliny. Koniec gry!";
					czy_zyje = false;
			}
			//sprawdzamy czy nie dotrzemy do wyjscia
			else if (aktualny_kierunek == LEWO	&& pos_x - skok >= 0		&& mapa[pos_y*width + pos_x - skok] == wyjscie ||
					 aktualny_kierunek == PRAWO	&& pos_x + skok < width		&& mapa[pos_y*width + pos_x + skok] == wyjscie ||
					 aktualny_kierunek == GORA	&& pos_y - skok >= 0		&& mapa[(pos_y - skok)*width + pos_x] == wyjscie ||
					 aktualny_kierunek == DOL	&& pos_y + skok < height	&& mapa[(pos_y + skok)*width + pos_x] == wyjscie) {
						cout << "Udalo Ci sie wyjsc z labiryntu, Gratulacje! Koniec gry!";
						wygrana = true;
			}
			//nic nie stoi na przeszkodzie to hopsamy
			else if (aktualny_kierunek == LEWO	&& pos_x - skok >= 0		&& mapa[pos_y*width + pos_x - skok] == koryt)		pos_x -= skok;//hopsamy w lewo
			else if (aktualny_kierunek == PRAWO && pos_x + skok < width		&& mapa[pos_y*width + pos_x + skok] == koryt)		pos_x += skok;//hopsamy w prawo
			else if (aktualny_kierunek == GORA	&& pos_y - skok >= 0		&& mapa[(pos_y - skok)*width + pos_x] == koryt)		pos_y -= skok;//hopsamy w gore
			else if (aktualny_kierunek == DOL	&& pos_y + skok < height	&& mapa[(pos_y + skok)*width + pos_x] == koryt)		pos_y += skok;//hopsamy w dol
		}
		//chcemy sobie poswiecic
		else if (wybrana_opcja == swiatlo) {
			pkt_energii -= utrata_swiatlo;
			if (aktualny_kierunek == LEWO	&& pos_x - zasieg_swiatla >= 0			&& mapa[pos_y*width + pos_x - zasieg_swiatla] == sciana ||
				aktualny_kierunek == PRAWO	&& pos_x + zasieg_swiatla < width		&& mapa[pos_y*width + pos_x + zasieg_swiatla] == sciana ||
				aktualny_kierunek == GORA	&& pos_y - zasieg_swiatla >= 0			&& mapa[(pos_y - zasieg_swiatla)*width + pos_x] == sciana ||
				aktualny_kierunek == DOL	&& pos_y + zasieg_swiatla < height		&& mapa[(pos_y + zasieg_swiatla)*width + pos_x] == sciana) {
					cout << "Na drugim polu przed Toba znajduje się sciana";
			}
			else if (aktualny_kierunek == LEWO	&& pos_x - zasieg_swiatla >= 0		&& mapa[pos_y*width + pos_x - zasieg_swiatla] == szczel ||
				aktualny_kierunek == PRAWO		&& pos_x + zasieg_swiatla < width	&& mapa[pos_y*width + pos_x + zasieg_swiatla] == szczel ||
				aktualny_kierunek == GORA		&& pos_y - zasieg_swiatla >= 0		&& mapa[(pos_y - zasieg_swiatla)*width + pos_x] == szczel ||
				aktualny_kierunek == DOL		&& pos_y + zasieg_swiatla < height	&& mapa[(pos_y + zasieg_swiatla)*width + pos_x] == szczel) {
				cout << "Na drugim polu przed Toba znajduje się szczelina";
			}
			else if (aktualny_kierunek == LEWO	&& pos_x - zasieg_swiatla >= 0		&& mapa[pos_y*width + pos_x - zasieg_swiatla] == koryt ||
				aktualny_kierunek == PRAWO		&& pos_x + zasieg_swiatla < width	&& mapa[pos_y*width + pos_x + zasieg_swiatla] == koryt ||
				aktualny_kierunek == GORA		&& pos_y - zasieg_swiatla >= 0		&& mapa[(pos_y - zasieg_swiatla)*width + pos_x] == koryt ||
				aktualny_kierunek == DOL		&& pos_y + zasieg_swiatla < height	&& mapa[(pos_y + zasieg_swiatla)*width + pos_x] == koryt) {
				cout << "Na drugim polu przed Toba znajduje się korytarz";
			}			
		}
		else if (wybrana_opcja == koniec_gry) czy_zyje = false;			
	}	
	return 0;
}

