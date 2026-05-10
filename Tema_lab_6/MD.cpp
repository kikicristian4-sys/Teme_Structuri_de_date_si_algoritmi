#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <math.h>

using namespace std;

//teta (1)
TElem Nod::element_curent() {
	return e;
}

//teta (1)
Nod* Nod::urmator() {
	return this->urm;

}

//teta (1)
void Nod::schimba_urm(Nod* urmator)
{
	this->urm = urmator;
}

int MD::d(TElem e)
{
	return abs(e.first) % 10;
}

MD::MD() {
	m = 10;
	for(int i = 0; i < m; i ++)
		lista[i] = nullptr;
	dimensiune = 0;
}


void MD::adauga(TCheie c, TValoare v) {
	 
	TElem e = {c,v};
	int dispersie = d(e);
	if (lista[dispersie] == nullptr)
	{
		Nod* n = new Nod;
		n -> e = e;
		n -> urm = nullptr;
		lista[dispersie] = n;
		dimensiune++;
	}
	else {
		Nod* n = new Nod;
		n -> e = e;
		n -> urm = lista[dispersie];
		lista[dispersie] = n;
		dimensiune++;
	}

}


bool MD::sterge(TCheie c, TValoare v) {

	TElem e = {c,v};
	int dispersie = d(e);
	if(lista[dispersie] == nullptr)
		return false;

	Nod* parcurgere = lista[dispersie];
	if (parcurgere->e.second == e.second && parcurgere ->e.first == e.first)
	{
		
		lista[dispersie] = lista[dispersie] -> urm;
		parcurgere -> urm = nullptr;
		delete parcurgere;
		dimensiune--;
		return true;
	}
	else
	{
		while (parcurgere -> urm != nullptr)
			{
				if ((parcurgere->urm)->e.second == e.second && (parcurgere->urm) ->e.first == e.first)
				{
					Nod* nod_de_sters = parcurgere -> urm;
					parcurgere -> urm = (parcurgere -> urm) -> urm;
					delete nod_de_sters;
					dimensiune--;
					return true;

				}
				parcurgere = parcurgere -> urm;
			}
	}
	
	return false;
}


vector<TValoare> MD::cauta(TCheie c) const {

	vector <TValoare> v;

	int dispersie = abs(c) % 10;
	if(lista[dispersie] == nullptr)
		return v;
	else
	{
		Nod* parcurgere = lista[dispersie];
		while (parcurgere != nullptr)
		{
			if((parcurgere -> e).first == c)
				v.push_back((parcurgere -> e).second);
			parcurgere = parcurgere -> urm;
		}
	}
	return v;
}


int MD::dim() const {
	return dimensiune;
}


bool MD::vid() const {
	if(dimensiune == 0)
			return true;
	return false;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	for(int i = 0; i < 10; i ++)
		delete lista[i];
}

