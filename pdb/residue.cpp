/*
 * Residue.cpp
 *
 *  Created on: Oct 2, 2013
 *      Author: alinar
 */

#include "Residue.h"


Residue::~Residue() {
}

void Residue::addAtom(const string str){

	atoms.resize(atoms.size()+1);
	atoms.back().element=	str.substr(76,2);
	atoms.back().name	=	str.substr(12,4);
	atoms.back().posX	=	atof( str.substr(30,8).data() );
	atoms.back().posY	=	atof( str.substr(38,8).data() );
	atoms.back().posZ	=	atof( str.substr(46,8).data() );
	atoms.back().occu	=	str.substr(54,6);
	atoms.back().temp	=	str.substr(60,6);
	atoms.back().residue=	str.substr(17,3);

	atoms.back().line	=	str;

}
void Residue::addAtom(const Atom *atom_new){

	atoms.resize(atoms.size()+1);
	atoms.back().element=	atom_new->element;
	atoms.back().name	=	atom_new->name;
	atoms.back().posX	=	atom_new->posX;
	atoms.back().posY	=	atom_new->posY;
	atoms.back().posZ	=	atom_new->posZ;
	atoms.back().occu	=	atom_new->occu;
	atoms.back().temp	=	atom_new->temp;
	atoms.back().residue=	atom_new->residue;

	atoms.back().line	=	atom_new->line;
}
