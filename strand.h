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
#include <cstdlib>
#include <math.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include "strand.h"
#include "macros.h"
#include "cylinder.h"

using namespace std;


class Strand {
public:
	vector < Strand* > sub_strands;
	vector < Cylinder* > cylinders;
	vtkSmartPointer<vtkTransform> transform;
	double alpha;
	double radius;
	double length;
	double init_pos[3];//initial position in the parent strand. init_pos[r,theta,z].
	double init_torsion_angle;
	bool basic_strand;
	bool stationary_rotation;

	void RotateWXYZ(double,double,double,double);
	void Translate(double,double,double);
	void AddStrand(Strand*);
	void AddCylinder();
	void Show(vtkRenderer*);
	void Show();
	void Seed();
	void Seed(double,vtkTransform*);
	Strand();
	Strand(double*);
	Strand(double,double,double);
	virtual ~Strand();

protected:
	double torsion_additive_angle;
	double height;
	void Update();
	void StationaryRotate(vtkTransform*, double*, double, double);
};

#endif /* STRAND_H_ */
