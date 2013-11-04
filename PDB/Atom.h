/*
 * Atom.h
 *
 *  Created on: Oct 2, 2013
 *      Author: alinar
 */

#ifndef ATOM_H_
#define ATOM_H_
#include <string>
using namespace std;

class Atom {
public:
	string line;
	double posX,posY,posZ;
	string element;
	string name;
	string occu,temp,residue;

	Atom();
	virtual ~Atom();
};

#endif /* ATOM_H_ */
