/*
 * elemental_strand.h
 *
 *  Created on: Nov 1, 2013
 *      Author: alinar
 */

#ifndef ELEMENTAL_STRAND_H_
#define ELEMENTAL_STRAND_H_

#include "strand.h"

class ElementalStrand : public Strand {
public:
	vector < Cylinder* > cylinders;
	double radius;
	double length;

	ElementalStrand();
	virtual ~ElementalStrand();
	void AddCylinder();
	void Seed();
	void Show(vtkRenderer*);
	bool IsElemtalStrand(){return true;}
	vtkSmartPointer<vtkTransform> AtomTransform(double,double);

protected:
	double torsion_additive_angle[MAX_HIERARCHY_COMPLEXITY];
	double height;
};

#endif /* ELEMENTAL_STRAND_H_ */
