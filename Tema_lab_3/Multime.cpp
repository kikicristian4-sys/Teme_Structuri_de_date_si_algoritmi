#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

//Complexitate teta(1)
Multime::Multime() {
	this -> cp = 1;

	this -> lungime =0;

    e = new TElem[cp];

}

/*
	Cand vine vorba de complexitatea acestei functii putem spune din start ca nu are cazuri favorabile sau nefavorabile.
	Motivul fiind ca este obligatoriu ca tot ce este in vechiul spatiu sa fie copiat in noul spatiu.
	Astfel caz favorabil = caz nefavorabil = caz mediu.
	Cazul mediu ce reiese din aceasta functie este teta(n). Totul vine de la copierea datelor.
*/
void Multime::redim_plus()
{
	int dim_noua = cp * 2;
	TElem* elem_nou = new TElem[dim_noua];

	for (int i = 0; i < this->lungime; i++)
	{
		elem_nou[i] = e[i];
	}

	this -> cp = dim_noua;

	delete [] e;

	e = elem_nou;

}

/*
	Complexitatea este exact aceeasi ca a functiei anterioare "redim_plus".
	Teta (n), motivul fiind acelasi, ca vrem, ca nu vrem, trebuie sa se copieze toate datele din memoria veche, in memoria noua.
*/
void Multime::redim_minus()
{
	int dim_noua = cp / 2;
	TElem* elem_nou = new TElem[dim_noua];

	
	for (int i = 0; i < this->lungime; i++)
	{
		elem_nou[i] = e[i];
	}

	this->cp = dim_noua;

	delete[] e;

	e = elem_nou;

}

/*
	In aceasta functie vine vorba despre un caz favorabil si un caz nefavorabil.
		In cazul favorabil adaugarea unui element nu se intampla, acesta fiind gasit din prima si functia returnand fals,
	ceea ce ar insemna o complexitate timp de teta(1).
		In cazul nefavorabil, elementul nu exista in vector si trebuie sa redimensionam, iar astfel la complexitatea functiei este adaugata si cea a "redim_plus"
	cat si cea a "cauta" calculul fiind: teta(n) + teta(n) + teta(1) = teta(n).
		In cazul mediu trebuie sa vorbim de sansa pe care o avem ca vectorul sa fie gasit si sa aibe nevoie de redimensionare....
	Astfel, cand vine vorba de calcule am avea (i de la 1 la n) i * 1/n + (i de la 0 la 1) n * 1/(n^i) + 1 = [(n * (n + 1))/2] * 1/n + n + n/n + 1= (n+1)/2 + n + 2 care apartine
	teta (n). Explicatia acestei complexitati vine din faptul ca: 
			-functia "cauta" are n cazuri posibile, numarul se gaseste pe prima pozitie, numarul se gaseste pe a doua pozitie,...., numarul se gaseste pe a n-a pozitie 
		numarul de pasi crescand cu fiecare posibilitate
			-functia "redim_plus" are doar doua cazuri: se intampla sau nu se intampla, intr-un caz complexitatea este 1 ( n/n ), in alt caz este n.
*/
bool Multime::adauga(TElem elem) {
	
	if(cauta(elem))
		return false;
	else
	{
		if( this -> lungime == this -> cp)
			redim_plus();
		
		this -> e[lungime++] = elem;
		return true;
	}
}

/*
	Aceasta functie este de asemenea interesanta, nu pentru ca este mai mult de discutat despre ea
	ci pentru ca nu are nici un caz favorabil sau nefavorabil => caz favorabil = caz nefavorabil = caz mediu.
	Motivul din spatele acestui lucru sunt cele 3 cazuri pe care le putem avea, unde toate au aceeasi complexitate.
		Cazul 1: elementul nu este in vector => se cauta elementul intr-un mod secvential => complexitate timp teta(n)
		Cazul 2: elementul este gasit, sters si nu se face redimensionare => Cautarea se va face incepand cu 0 si ducand
	pana in momentul in care este gasit elementul cautat, dupa care se continua parcurgerea vectorului si fiecare element
	primeste valoarea celui din fata, pentru a "ingropa" acel element. Complexitatea este teta(n - 1) care este tot teta(n),
	parcurgandu-se tot vectorul oricum.
		Cazul 3: elementul este gasit, sters si se face redimensionare => se intampla tot ce s-a intamplat in Cazul 2, insa de 
	aceasta data vine si vorba de redimensionare, care am stabilit ca are complexitatea teta(n), calculul este simplu: teta(n) + teta(n) = 
	teta(n). Complexitatea ramane teta(n).
*/
bool Multime::sterge(TElem elem)
{
	if(lungime == 0)
		return false;
	
	for(int i = 0; i < lungime; i++)
		if (this->e[i] == elem)
		{	
			lungime--;
			for(int j = i; j < lungime; j++)
				this -> e[j] = this -> e[j+1];

			
			if (lungime < (cp / 2) - 1)
				redim_minus();
			return true;
		}

	return false;

}

int Multime::diferentaMaxMin() const
{
	
	if( lungime == 0 )
		return -1;
	else
	{
		TElem min = e[0], max = e[0];
		for (int i = 1; i < lungime; i++)
		{
			if (e[i] < min)
				min = e[i];
			if(e[i] > max)
				max = e[i];

		}
		return max - min;

	}
}



/*
	O functie pe intelesul tuturor, cautarea se intampla secvential, complexitatea de timp 
	este obligatoriu teta(n), luandu-se fiecare element la mana.
	Deci caz favorabil = caz nefavorabil = caz mediu = teta(n).
*/
bool Multime::cauta(TElem elem) const {
	
	for(int i = 0; i < lungime; i++)
		if(this -> e[i] == elem)
			return true;

	return false;
}

//Complexitate teta(1).
int Multime::dim() const {
	return lungime;
}

//Complexitate teta(1).
bool Multime::vida() const {
	if(lungime == 0)
		return true;

		return false;
}


//Complexitate teta(1)
Multime::~Multime() {

	delete [] e;
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

