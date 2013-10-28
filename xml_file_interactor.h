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
using namespace rapidxml;
using namespace std;

class XMLFileInteractor {
protected:
	xml_document<>	doc;
	char*			str;
	vector<Strand*>	strands;
	int number_of_rows;

	int ReadFile(char*);
	Strand* AddStrand();
	void AddStrand(Strand*);

public:
	Strand* master_strand;

	XMLFileInteractor(char*);
	~XMLFileInteractor();
	void MakeStructure();
	int WriteFile(char*);
	void Parse();
	void RecursiveAdd(xml_node<>*, Strand*);
};

#endif /* XML_FILE_INTERACTOR_H_ */
