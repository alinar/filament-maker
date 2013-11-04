/*
 * chain.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: alinar
 */

#include "chain.h"

int chain::addResidue(const string str){
	residues.resize(residues.size()+1);
	residues.back().type = str;
	return 1;
}



