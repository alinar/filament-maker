/*
 * xml_file_interactor.h
 *
 *  Created on: Oct 24, 2013
 *      Author: alinar
 */

#ifndef XML_FILE_INTERACTOR_H_
#define XML_FILE_INTERACTOR_H_

#include <rapidxml.hpp>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <vector>
#include "macros.h"
#include "strand.h"
#include "elemental_strand.h"
#include "packing.h"
using namespace rapidxml;
using namespace std;

class XMLFileInteractor {
protected:
	xml_document<>	doc;
	char*			str;
	vector<Strand*>	strands;
	int number_of_rows;
	int ReadFile(char*);
	Strand*				AddNewStrand();
	ElementalStrand*	AddNewElementalStrand();
public:
	Strand* master_strand;
	double filament_length;
	Packing*		packing;
	char*			output_file;

	XMLFileInteractor(char*);
	virtual ~XMLFileInteractor();
	void MakeStructure();
	int WriteFile(char*);
	void Parse();
	void RecursiveAdd(xml_node<>*, Strand*);
	int ReadPacking();
};

#endif /* XML_FILE_INTERACTOR_H_ */
