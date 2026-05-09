#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>



//teta (1)
bool rel(TElem e1, TElem e2) {
	if(e1 < e2)
		return true;
	return false;
}

int Colectie::aloca() {
	
	int i = prim_liber;
	prim_liber = urm[prim_liber];
	return i;
}

void Colectie::dealoca(int i) {
	
	urm[i] = prim_liber;
	prim_liber = i;
}

int Colectie::creeazaNod(TElem e) {
	
	int i = aloca();
	if (i != -1) {
		els[i].first = e;
		els[i].second = 1;
		urm[i] = -1;
	}
	return i;
}


void Colectie::redim() {
	prim_liber = capacitate;
	capacitate = capacitate * 2;
	pair<TElem,int>* new_e = new pair<TElem,int> [capacitate];
	int* new_urm = new int[capacitate];

	

	for (int i = 0; i < nr_elemente; i++)
	{
		new_e[i] = els[i];
		new_urm[i] = urm[i];
	}
	delete [] els;
	delete [] urm;

	els = new_e;
	urm = new_urm;

	
	for (int i = nr_elemente; i < capacitate ; i++)
	{
		
		els[i].first = -1;
		els[i].second = 0;
		if(i != capacitate-1)
			urm[i] = i + 1;
		else
			urm[i] = -1;

	}
}

//teta (1)
Colectie::Colectie() {
	els = new pair<TElem, int>[1];
	urm = new int[1];
	els[0].first = -1;
	els[0].second = 0;
	urm[0] = -1;
	capacitate = 1;
	prim = -1;
	prim_liber = 0;
	nr_elemente = 0;
	nr_elem_cu_frecv = 0;
}

/*
Caz favorabil: elementul pe care il adaugam este cel mai prioritar -> teta(1)
Caz defavorabil: elementul pe care il adaugam este cel mai putin prioritar -> teta(n)
Caz mediu: teta(n)
Complexitate generala: O(n)
*/
void Colectie::adauga(TElem e) {
	
	if(nr_elemente == capacitate)
		redim();

	if (vida())
	{
		prim = 0;
		int i = creeazaNod(e);
		nr_elemente++;
		nr_elem_cu_frecv++;
	}
	else {
		if (! rel(els[prim].first, e))
		{
			if (els[prim].first == e)
			{
				els[prim].second++;
				nr_elem_cu_frecv++;
			}
				
			else
			{
				int i = creeazaNod(e);
				urm[i] = prim;
				prim = i;
				
				nr_elemente++;
				nr_elem_cu_frecv++;

			}
			
		}
		else {
			int parcurgere = prim;
			while(urm[parcurgere] != -1 && parcurgere != -2)
			{
				if (! rel(els[urm[parcurgere]].first, e))
				{
					if (els[urm[parcurgere]].first == e)
					{
						els[urm[parcurgere]].second++;
						nr_elem_cu_frecv++;
						parcurgere = -2;
					}

					else
					{
						int i = creeazaNod(e);

						urm[i] = urm[parcurgere];
						urm[parcurgere] = i;
						
						nr_elemente++;
						nr_elem_cu_frecv++;
						parcurgere = -2;

					}
				}
				if(parcurgere != -2)
					parcurgere = urm[parcurgere];
			}
			if (parcurgere != -2)
			{
				int i = creeazaNod(e);

				urm[i] = -1;
				urm[parcurgere] = i;

				
				nr_elemente++;
				nr_elem_cu_frecv++;
			}
		}
	}




}

/*
Caz favorabil: elementul pe care il stergem este cel mai prioritar -> teta(1)
Caz defavorabil: elementul pe care il stergem este cel mai putin prioritar/nu exista elementul pe care il cautam sa il stergem -> teta(n)
Caz mediu: teta(n)
Complexitate generala: O(n)
*/
bool Colectie::sterge(TElem e) {
	if(vida())
		return false;
	if (els[prim].first == e)
	{
		if (els[prim].second > 1)
		{
			els[prim].second--;
			nr_elem_cu_frecv--;
			return true;
		}

		else
		{
			int urm_prim = urm[prim];
			dealoca(prim);
			prim = urm_prim;

			nr_elemente--;
			nr_elem_cu_frecv--;
			return true;

		}

	}
	else {
		int parcurgere = prim;
		while (urm[parcurgere] != -1)
		{
			if (els[urm[parcurgere]].first == e)
			{
				if (els[urm[parcurgere]].second > 1)
				{
					els[urm[parcurgere]].second--;
					nr_elem_cu_frecv--;
					return true;
				}

				else
				{
					int urmmatum = urm[parcurgere];
					urm[parcurgere] = urm[urm[parcurgere]];

					dealoca(urmmatum);

					nr_elemente--;
					nr_elem_cu_frecv--;
					return true;

				}
			}
			parcurgere = urm[parcurgere];
		}
		
	}
	return false;
}

/*
Caz favorabil: elementul pe care il cautam este cel mai prioritar -> teta(1)
Caz defavorabil: elementul pe care il cautam este cel mai putin prioritar/nu exista elementul pe care il cautam -> teta(n)
Caz mediu: teta(n)
Complexitate generala: O(n)
*/
bool Colectie::cauta(TElem elem) const {
	if(vida())
		return false;
	int parcurgere = prim;
	if(els[prim].first == elem)
		return true;
	while (urm[parcurgere] != -1)
	{
		if (els[urm[parcurgere]].first == elem)
			return true;
		parcurgere = urm[parcurgere];
	}
	return false;
}

/*
Caz favorabil: elementul pe care il cautam este cel mai prioritar -> teta(1)
Caz defavorabil: elementul pe care il cautam este cel mai putin prioritar/nu exista elementul pe care il cautam -> teta(n)
Caz mediu: teta(n)
Complexitate generala: O(n)
*/
int Colectie::nrAparitii(TElem elem) const {
	if(vida())
		return false;
	int parcurgere = prim;
	if (els[prim].first == elem)
		return els[prim].second;
	while (urm[parcurgere] != -1)
	{
		if (els[urm[parcurgere]].first == elem)
			return els[urm[parcurgere]].second;
		parcurgere = urm[parcurgere];
	}
	return 0;
}


//teta(1)
int Colectie::dim() const {
	return nr_elem_cu_frecv;
}

//teta(1)
bool Colectie::vida() const {
	if(prim == -1)
		return true;

	return false;
	
}

//teta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//teta(n)
Colectie::~Colectie() {
	delete [] els;
	delete [] urm;
}

