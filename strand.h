/*
 * strand.h
 *
 *  Created on: Oct 17, 2013
 *      Author: alinar
 */

#ifndef STRAND_H_
#define STRAND_H_

#include <cstdio>
#include <vector>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "strand.h"

using namespace std;


class Strand {
public:
	vector < vtkSmartPointer<Strand> > strands;
	vector < vtkSmartPointer<Cylinder> > cylinders;
	double position[3];
	double alpha;
	double radius;

	void RotateWXYZ(double,double,double,double);
	void Translate(double,double,double);
	void AddStrand();
	void AddCylinder();
	void Show(vtkRenderer*);
	void Show();
	Strand();
	virtual ~Strand();
};

#endif /* STRAND_H_ */
