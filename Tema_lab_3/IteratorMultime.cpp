#include "IteratorMultime.h"
#include "Multime.h"
#include <stdexcept>

//Complexitate teta(1)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	curent = 0;
}

//Complexitate teta(1)
void IteratorMultime::prim() {
	curent = 0;
}

//Complexitate teta(1)
void IteratorMultime::urmator() {
	if (valid() == false)
		throw std::invalid_argument(" Iteratorul nu mai este valid! ");
	curent++;
	
}

//Complexitate teta(1)
TElem IteratorMultime::element() const {
	return multime.e[curent];
}

//Complexitate teta(1)
bool IteratorMultime::valid() const {
	if(curent < multime.dim())
		return true;

	return false;
}
