#pragma once
#include <vector>
#include <utility>

using namespace std;

typedef int TElem;
typedef int TPrioritate;

typedef std::pair<TElem, TPrioritate> Element;

typedef bool (*Relatie)(TPrioritate p1, TPrioritate p2);

class Nod {
	Element e;//Valoarea elementului curent
	Nod* urm;//Pointer catre urmatorul element din lista

public:
	friend class CP;
	Nod() = default;

	Nod(Element e, Nod* urm) : e{ e }, urm{ urm } {};//constructor
	
	Element element_curent();
	Nod* urmator();
	void schimba_urm(Nod* urmator);

};

class CP {
private:

	
	Relatie relatie;//Relatia de ordine
	Nod* prim;

public:
	//constructorul implicit
	CP(Relatie r);

	//adauga un element in CP
	void adauga(TElem e, TPrioritate p);

	//acceseaza elementul cel mai prioritar in raport cu relatia de ordine
	//arunca exceptie daca CP e vida
	Element element()  const;

	//sterge elementul cel mai prioritar si il returneaza
	//arunca exceptie daca CP e vida
	Element sterge();

	//verifica daca CP e vida;
	bool vida() const;

	// destructorul cozii
	~CP();

};
