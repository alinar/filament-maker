/*
 * Atom.cpp
 *
 *  Created on: Oct 2, 2013
 *      Author: alinar
 */

#include "Atom.h"

Atom::Atom() : posX(0),posY(0),posZ(0){
	this->line.resize(80,' ');
}

Atom::~Atom() {}

