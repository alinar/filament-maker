/*
 * packing.h
 *
 *  Created on: Feb 10, 2014
 *      Author: alinar
 */

#ifndef PACKING_H_
#define PACKING_H_

#include <vector>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include "strand.h"
#include "pdb.h"

class Packing {
public:
	unsigned int number_of_units;
	vector<double>	alpha,beta,gamma;
	vector<double>	pos_x,pos_y,pos_z;
	Strand*			unit_strand;
	double			cuboid_x,cuboid_y,cuboid_z;
	Packing(Strand*);
	virtual ~Packing();

	void AddUnit(double,double,double,double,double,double);
	void AddUnit(double *p){
		this->AddUnit(p[0],p[1],p[2],p[3],p[4],p[5]);
	}
	void AddUnit(double*o,double*p){
		this->AddUnit(o[0],o[1],o[2],p[0],p[1],p[2]);
	}

	vtkSmartPointer<vtkTransform> UnitTransformer(unsigned int);

	void packPDB(PDB*,PDB*);
};

#endif /* PACKING_H_ */
