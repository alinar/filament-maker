/*
 * Residue.h
 *
 *  Created on: Oct 2, 2013
 *      Author: alinar
 */

#ifndef RESIDUE_H_
#define RESIDUE_H_
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <vector>
#include <string>
#include "Atom.h"
using namespace std;

class Residue {
public:
	vector<Atom> atoms;
	string type;

	Residue():type(3,'X'){};
	virtual ~Residue();
	void addAtom(const string);
	void addAtom(const Atom*);
};

#endif /* RESIDUE_H_ */
