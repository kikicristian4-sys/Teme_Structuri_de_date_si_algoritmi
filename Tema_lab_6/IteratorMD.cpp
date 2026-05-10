#include "IteratorMD.h"
#include "MD.h"
#include <exception>

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	if (md.vid())
	{
		poz_curent = 0;
		curent = nullptr;

	}
	else
	{
		for (int i = 0; i < 10; i++)
			if (md.lista[i] != nullptr)
			{
				poz_curent = i;
				curent = md.lista[i];
				break;
			}
	}
	
	
}

TElem IteratorMD::element() const{
	if(curent == nullptr)
		throw exception("Iterator invalid!");
	return curent ->element_curent();
}

bool IteratorMD::valid() const {
	if(curent != nullptr)
		return true;
	return false;
}

void IteratorMD::urmator() {
	if (curent == nullptr)
		throw exception("Iterator invalid!");
	if(curent -> urmator() != nullptr)
		curent = curent ->urmator();
	else
	{
		int cp_poz = poz_curent;
		for (int i = poz_curent+1; i < 10; i++)
			if (md.lista[i] != nullptr)
			{
				poz_curent = i;
				curent = md.lista[i];
				break;
			}
		if (poz_curent == cp_poz)
		{
			poz_curent = 10;
			curent = nullptr;
		}
	}
		
}

void IteratorMD::prim() {
	if (md.vid())
	{
		poz_curent = 0;
		curent = nullptr;
	}
	else
	{
		for (int i = 0; i < 10; i++)
			if (md.lista[i] != nullptr)
			{
				poz_curent = i;
				curent = md.lista[i];
				break;
			}
	}
}

