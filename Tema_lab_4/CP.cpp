
#include "CP.h"
#include <exception>
#include <stdio.h>
#include <algorithm>
#include <stdexcept>

using namespace std;

//teta (1)
Element Nod::element_curent() {
	return e;
}

//teta (1)
Nod* Nod::urmator() {
	return urm;

}

//teta (1)
void Nod::schimba_urm(Nod* urmator)
{
	this->urm = urmator;
}

//teta (1)
CP::CP(Relatie r) {
	this -> relatie = r;
}

/*
Caz favorabil: elementul pe care il adaugam este cel mai prioritar -> teta(1)
Caz defavorabil: elementul pe care il adaugam este cel mai putin prioritar -> teta(n)
Caz mediu: teta(n)
Complexitate generala: O(n)
*/
void CP::adauga(TElem e, TPrioritate p) {
	if (vida())
	{
		Element elem(e,p);
		Nod* prim = new Nod(elem,nullptr);
		this->prim = prim;
	}
	else
	{
		Element elem(e,p);
		Nod* nod = new Nod(elem,nullptr);
		Nod* cautare = prim;
		if (! relatie(prim->element_curent().second, nod->element_curent().second))
		{
			nod->schimba_urm(prim);
			prim = nod;
			return;
		}
		
		while (cautare->urmator() != nullptr)
		{
			if (! relatie((cautare->urmator())->element_curent().second, nod->element_curent().second))				
			{
				nod->schimba_urm(cautare->urmator());
				cautare->schimba_urm(nod);
				return;
			}
			cautare = cautare->urmator();
		}
		cautare->schimba_urm(nod);
	}
}

//arunca exceptie daca coada e vida
//teta (1)
Element CP::element() const {
	if(vida())
		throw std::length_error("Lista este vida!");

	return pair <TElem, TPrioritate>  (this ->prim->element_curent().first, this ->prim->element_curent().second);
;
}

//teta (1)
Element CP::sterge() {
	if (vida())
		throw std::length_error("Lista este vida!");

	auto elem = prim->element_curent().first;
	auto priority = prim -> element_curent().second;

	Nod* nod_de_sters = prim;
	prim = prim->urmator();

	delete nod_de_sters;
	
	return pair <TElem, TPrioritate> (elem, priority);
	
}

//teta (1)
bool CP::vida() const {
	if(this->prim == nullptr)
		return true;
	return false;
}

//teta (n)
CP::~CP() {
	if(! vida())
		while (prim->urmator() != nullptr)
			{
				Nod* nod_de_sters = prim;
				prim = prim->urmator();
				delete nod_de_sters;
			}
};

