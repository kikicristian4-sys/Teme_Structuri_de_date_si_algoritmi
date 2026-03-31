#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		/* 
		aici e reprezentarea 
		Aceasta trebuie facuta intr-un vector dinamic
		*/

		//capacitate
		int cp;

		//lungime
		int lungime;

		//elemente
		TElem *e;

		//redimensioneaza vectorul prin adaugare
		void redim_plus();

		//redimensioneaza vectorul prin scadere
		void redim_minus();
		

    public:
 		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem);

		//returneaza diferenta dintre valoarea maxima si cea minima (presupunem valori intregi)
		//daca multimea este vida, se returneaza -1
		int diferentaMaxMin() const;

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem);


		//verifica daca un element se afla in multime
		bool cauta(TElem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// destructorul multimii
		~Multime();
};




