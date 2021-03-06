// PKLab3.cpp : Defines the entry point for the console application.
// @author Paweł Lodzik
/*Laboratorium 3 (PK3nz)

Napisać klasę Wektor, która dziedziczy z klasy Punkt(ćw. 1) .
W klasie Punkt współrzędne x, y są współrzędnymi początku wektora.
Klasa Wektor ma dodatkowe pola : długosc(d)  oraz kierunek(alfa) . (1p)
Napisać konstruktor  4 parametrowy, który ustawia położenie  wektora(x, y, d, alfa)
Konstruktor klasy wektor powinien wywołać konstruktor klasy punkt. (1p)
Napisać metodę :
Punkt wk();
która zwraca współrzędne końca wektora wyliczone na podstawie x, y, d, alfa. (2p)
Przedefiniować metodę dodaj(Punkt &).(1p)
Czy parametrem tej metody może być obiekt klasy Wektor ? (1p)
Co należy zrobić aby program działał  poprawnie ? (1p)
Zaimplementować klasę TablicaSort, która dziedziczy z klasy Tablica(laboratorium 1) i przechowuje wektory(wektory zaczepione w punkcie 0, 0 : klasa Punkt) posortowane wg.długości .
Zaimplementować dwa konstruktory :
TablicaSort(Tablica); (4p)
TablicaSort(TablicaSort); (2p)
operator strumieniowy, który wyświetla zawartosć tablicy(2p).
Wszystkie klasy i metody należy przetestować w funkcji main() (10p)
*/


#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class Punkt
{
protected:
	float x;
	float y;

public:
	Punkt(float x_ = 0, float y_ = 0);
	Punkt(const Punkt& p);
	void dodaj(const Punkt &p); //dodawanie do siebie współrzędnych wektora
	void dodaj(const Punkt *p);
	void drukuj();
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	float getX() { return this->x; }
	float getY() { return this->y; }
	~Punkt();

};

class Wektor : public Punkt {

protected:
	float d;
	float alfa;


public:
	Wektor(float x_ = 0, float y_ = 0, float d_ = 0, float alfa_ = 0)
		: Punkt(x_, y_), d(d_), alfa(alfa_) {};
	Punkt wk();
	void dodaj(const Wektor &w);
	void drukuj();
	void setD(float d) { this->d = d; };
	void setAlfa(float alfa) { this->alfa = alfa; };
	float getD() { return this->d; }
	float getAlfa() { return this->alfa; }
};

void Wektor::drukuj()
{
	cout << "X: " << this->x << " ";
	cout << "Y: " << this->y << " ";
	cout << "D: " << this->d << " ";
	cout << "Alfa: " << this->alfa << endl;
}

Punkt Wektor::wk() { //Obliczanie końca wektora
	float a = d*(sin(alfa));
	float b = sqrt((d*d) - (a*a));
	float x = this->x;
	float y = this->y;
	//4 przypadki zwrotu wektora
	if (alfa < 90.0f) {
		x += b;
		y += a;
	}
	else if (alfa < 180.0f)
	{
		x -= b;
		y += a;
	}
	else if (alfa < 270.0f) {
		x -= b;
		y -= a;
	}
	else {
		x += b;
		y -= a;
	}

	return Punkt(x, y);
}

void Wektor::dodaj(const Wektor &w) {
	this->x += w.x;
	this->y += w.y;
	this->d += w.d;
	this->alfa += w.alfa;
}


Punkt::Punkt(float x_, float y_)
{
	this->x = x_;
	this->y = y_;
}

Punkt::Punkt(const Punkt& p)
{
	this->x = p.x;
	this->y = p.y;
}

void Punkt::dodaj(const Punkt &p)
{
	this->x += p.x;
	this->y += p.y;
}

void Punkt::dodaj(const Punkt *p)
{
	this->x += p->x;
	this->y += p->y;
}

void Punkt::drukuj() {
	cout << "X: " << this->x << " ";
	cout << "Y: " << this->y;
	cout << endl;
}

Punkt::~Punkt()
{
}

class Tablica
{
protected:
	Wektor *w;
	int dl; //Długość tablicy

public:

	Tablica(int dl = 0); // tworzy Tablice o zadanej długości i wypełnia punktami (0,0)
	Tablica(const Tablica &w_); //inicjalizacja za pomocą Tablicy w_
	~Tablica();
	void dodaj(const Tablica &w_);// dodaje do siebie Tablice w_
	void dodaj(const Wektor w);
	bool porownaj(const Tablica &w);// porownaie z Tablica w_;
	void drukuj();
	int getDl() { return this->dl; };
	Wektor * getW() { return w; };
	friend ostream& operator<< (ostream& out, const Tablica& t) {
		if (!t.dl) {
			out << "Tablica jest pusta" << endl;
			return out;
		}

		out << "Wypisywanie tablicy" << endl;
		for (int i = 0; i < t.dl; i++) {
			out << "Wektor " << (i + 1) << endl;

			out << "X: " << t.w[i].getX() << " Y: " << t.w[i].getY() << " D: " << t.w[i].getD() << " Alfa: " << t.w[i].getAlfa() << endl;
		}

		return out;
	}

};

void Tablica::dodaj(const Wektor w) {
	Wektor * tmp = new Wektor[dl + 1];

	for (int i = 0; i < dl; i++)
	{
		tmp[i] = this->w[i];
	}

	dl++;

	delete[] this->w;
	this->w = tmp;

	this->w[dl - 1] = w;
}

class TablicaSort : public Tablica {
	
	private:
		static int porownajWektory(const void * a, const void * b);

	public:
		TablicaSort(const TablicaSort &t) : Tablica(t) {};
		TablicaSort(Tablica tab);

};

int TablicaSort::porownajWektory(const void * a, const void * b)
{
	Wektor A = *(Wektor*)a;
	Wektor B = *(Wektor*)b;
	if (A.getD() < B.getD()) return -1;
	if (A.getD() == B.getD()) return 0;
	if (A.getD() > B.getD()) return 1;
};


TablicaSort::TablicaSort(Tablica tab) {
	this->dl = tab.getDl();
	if (dl) {
		this->w = new Wektor[dl];
		for (int i = 0; i < this->dl; i++) {
			*(this->w + i) = *(tab.getW() + i);
		}

		qsort(this->w, dl, sizeof(Wektor), TablicaSort::porownajWektory);
	}
	else {
		this->w = NULL;
	}

}


Tablica::Tablica(int dl)
{
	this->dl = dl;

	if (!dl) {
		this->w = NULL;
	}
	else {
		w = new Wektor[dl];
	}

}

Tablica::Tablica(const Tablica &w_)
{
	this->dl = w_.dl;

	if (!dl) {
		this->w = NULL;
	}
	else {
		this->w = new Wektor[this->dl];
		for (int i = 0; i < this->dl; i++) {
			*(this->w + i) = *(w_.w + i);
		}
	}
}


void Tablica::dodaj(const Tablica &w_)
{
	if (w_.dl != this->dl) {
		cout << "Tablice są różnych rozmiarów" << endl;
		return;
	}


	for (int i = 0; i < this->dl; i++) {
		this->w[i].dodaj(w_.w[i]);
	}
}

bool Tablica::porownaj(const Tablica &w_) {

	for (int i = 0; i < this->dl; i++) {
		if (this->w[i].getX() != w_.w[i].getX() || this->w[i].getY() != w_.w[i].getY())
		{
			return false;
		}
	}

	return true;
}

void Tablica::drukuj()
{
	cout << *this << endl;

}

Tablica::~Tablica()
{
	delete[] this->w;
}

int main()
{
	//Testowanie klasy Wektor
	//tworzenie wektora o współrzędnych x = 5 , y= 6, d = 7, alfa = 70
	Wektor w1(5, 6, 7, 70);
	
	//Drukowanie współrzędnych wektora
	cout << "Współrzędne wektora w1" << endl;
	w1.drukuj();

	//Tworzenie wektora w2 i dodawanie go do wektora w1 metodą dodaj z klasy wektor
	Wektor w2(14, 15, 20, 23);
	w1.dodaj(w2);

	//Sprawdzanie wyników dodania
	cout << "Współrzędne wektora w1" << endl;
	w1.drukuj();

	//Dodawanie wektora w3 do w1 za pomocą metody dodaj z klasy punkt
	Wektor w3(10, 10, 10, 10);
	w1.Punkt::dodaj(w3);
	cout << "Współrzędne wektora w1" << endl;
	w1.drukuj();
	//Czy parametrem metody dodaj(Punkt &) może być obiekt klasy wektor?
	/*
		Tak, może być obiekt klasy wektor, jednak wtedy dodają się jedynie x i y bez alfa i d.
		Parametrem może być obiekt klasy wektor, ponieważ dziedziczy ona po klasie punkt
	*/

	//Co należy zrobić aby program działał  poprawnie? 
	/*
		Nie wiem - mi działa poprawnie.
	*/

	//Testowanie obliczania punktów końca wektora dla różnych kątów alfa
	Wektor w4(4, 5, 10, 80);
	Punkt p1 = w4.wk();
	cout << "Punkt końcowy dla wektora w4" << endl;
	p1.drukuj();

	Wektor w5(4, 5, 13, 160);
	Punkt p2 = w5.wk();
	cout << "Punkt końcowy dla wektora w5" << endl;
	p2.drukuj();

	Wektor w6(4, 5, 16, 200);
	Punkt p3 = w6.wk();
	cout << "Punkt końcowy dla wektora w6" << endl;
	p3.drukuj();

	Wektor w7(4, 5, 19, 280);
	Punkt p4 = w7.wk();
	cout << "Punkt końcowy dla wektora w7" << endl;
	p4.drukuj();

	//Testowanie klasy TablicaSort
	
	//Tworzenie tablicy i dodawanie do niej punktów
	Tablica tab1;
	tab1.dodaj(w1);
	tab1.dodaj(w2);
	tab1.dodaj(w3);
	tab1.dodaj(w4);
	tab1.dodaj(w5);
	tab1.dodaj(w6);
	cout << "Tablica tab1" << endl;
	cout << tab1 << endl;

	//Tworzenie tablicy posortowanej po długości wektorów rosnąco
	TablicaSort tabSorted(tab1);
	cout << "Tablica tabSorted - posortowana" << endl;
	cout << tabSorted << endl;

	//Tworzenie kopii posortowanej tablicy tabSorted i wyświetlenie jej
	TablicaSort tabSorted2(tabSorted);
	cout << "Tablica tabSorted2 - posortowana" << endl;
	cout << tabSorted2 << endl;

	system("pause");
    return 0;
}

