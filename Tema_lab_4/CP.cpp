
#include "CP.h"
#include <exception>
#include <stdio.h>
#include <algorithm>
#include <stdexcept>

using namespace std;


CP::CP(Relatie r) {
	this -> relatie = r;
	this -> urmator = nullptr;
	this -> e = nullptr;
}


void CP::adauga(TElem e, TPrioritate p) {
	if (this -> e == nullptr)
		this -> e = new Element (e,p);
	else
	{
		if (this->urmator == nullptr)
		{
			CP* nod_nou = new CP(this -> relatie);
			nod_nou -> e = new Element(e, p);
			nod_nou -> urmator = nullptr;

			if (this -> relatie(this->e->second, nod_nou->e->second))
			{
				this -> urmator = nod_nou;
			}
			else
			{
				swap(this -> e, nod_nou -> e);
				this -> urmator = nod_nou;
				
			}
		}
		else
		{
			CP* nod_nou =  new CP(this -> relatie);
			nod_nou->e = new Element(e, p);

			if (!this->relatie(this->e->second, nod_nou->e->second))
			{
				swap(this->e, nod_nou->e);
				nod_nou -> urmator = this -> urmator;
				this->urmator = nod_nou;
			}
			else
			{
				CP* parcurgere = this;
				while (parcurgere -> urmator != nullptr)
				{
					if (this->relatie(parcurgere->urmator->e->second, nod_nou->e->second))
					{
						parcurgere = parcurgere ->urmator;
					}
					else
					{
						nod_nou -> urmator = parcurgere -> urmator;
						parcurgere -> urmator = nod_nou;
						break;
					}
				}
				if (parcurgere->urmator == nullptr)
				{
					parcurgere -> urmator = nod_nou;
					nod_nou -> urmator = nullptr;
				}
			}	
		}
		
	}
}

//arunca exceptie daca coada e vida
Element CP::element() const {
	if(this -> e == nullptr)
		throw std::length_error("Lista este vida!");

	return pair <TElem, TPrioritate>  (this ->e -> first, this -> e -> second);       // copy constructor
;
}

Element CP::sterge() {
	if (this->e == nullptr)
		throw std::length_error("Lista este vida!");

	if (this->urmator != nullptr)
	{
		CP* nod_de_sters = this->urmator;

		swap(this->e, this->urmator->e);
		this->urmator = this->urmator->urmator;

		TElem valoare = nod_de_sters->e->first;
		TPrioritate prioritate = nod_de_sters->e->second;


		nod_de_sters -> urmator = nullptr;
		delete nod_de_sters;

		return pair <TElem, TPrioritate>(valoare, prioritate);
	}
	else
	{
		TElem valoare = this ->e->first;
		TPrioritate prioritate =this ->e->second;

		delete this -> e;
		this -> e = nullptr;

		return pair <TElem, TPrioritate>(valoare, prioritate);
	}
	
}

bool CP::vida() const {
	if(this -> e == nullptr)
		return true;
	return false;
}


CP::~CP() {
	delete this -> e;

	CP* parcurgere = this -> urmator;
	while (parcurgere != nullptr)
	{
		CP* nod_urmator_curent = parcurgere;
		
		parcurgere = parcurgere -> urmator;

		nod_urmator_curent -> urmator = nullptr;		
		delete nod_urmator_curent;
		
		
	}
	
};

