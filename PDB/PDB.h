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
};


#endif /* PDB_H_ */
