/*
 * PDB.h
 *
 *  Created on: Oct 2, 2013
 *      Author: alinar
 */

#ifndef PDB_H_
#define PDB_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "Residue.h"
#include "chain.h"
#include "strand.h"
using namespace std;


class PDB{
public:
	vector <string> lines ;
	vector <chain> chains ;

	~PDB();
	int readFile(const char* f);
	int readLines();
	int addChain(char);
	int printInfo(int);
	int writeFile(char*);
	static void TransformToY(PDB*);
	double CalcLength();
	static void Transformer(PDB *pdb_in,PDB *pdb_out,Strand* ,unsigned int);
};


#endif /* PDB_H_ */
