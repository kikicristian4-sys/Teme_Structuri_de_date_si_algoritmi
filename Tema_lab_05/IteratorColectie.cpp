#include "IteratorColectie.h"
#include "Colectie.h"
#include <stdexcept>

//teta(1)
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = col.prim;
}

//teta(1)
TElem IteratorColectie::element() const{
	return col.els[curent].first;
}
//teta(1)
bool IteratorColectie::valid() const {
	if (curent < col.nr_elemente && curent != -1)
		return true;
	return false;
}

//teta(1)
void IteratorColectie::urmator() {
	if(! valid())
		throw std::length_error("Iteratorul nu este valid!");
	curent = col.urm[curent];
}

//teta(1)
void IteratorColectie::prim() {
	curent = col.prim;
}
