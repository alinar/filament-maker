/*
 * chain.h
 *
 *  Created on: Oct 4, 2013
 *      Author: alinar
 */

#ifndef CHAIN_H_
#define CHAIN_H_
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "Residue.h"
using namespace std;

class chain {
public:
	vector <Residue> residues ;
	char chainID;

	int addResidue(const string);

};

#endif /* CHAIN_H_ */
