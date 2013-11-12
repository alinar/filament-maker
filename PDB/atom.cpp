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

void Atom::ApplyTransform(vtkTransform *trans){
	double pos[3];
	pos[0]	=	posX;
	pos[1]	=	posY;
	pos[2]	=	posZ;
	trans->TransformPoint(pos,pos);
	posX	=	pos[0];
	posY	=	pos[1];
	posZ	=	pos[2];
}
