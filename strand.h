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

#define WITH_TILT		true
#define WITHOUT_TILT	false

class Strand {
public:
	vector < Strand* > sub_strands;

	double init_pos[3];//initial position in the parent strand. init_pos[r,theta,z].
	double init_torsion_angle;
	bool supreme_strand;
	bool stationary_rotation;
	Strand *parent_strand;

	void RotateWXYZ(double,double,double,double);
	void Translate(double,double,double);
	void AddStrand(Strand*);

	Strand();
	virtual ~Strand(){};
	virtual void Show(vtkRenderer*);
	virtual bool IsElemtalStrand(){return false;}
	void Show();
	virtual void Seed();
	virtual vtkSmartPointer<vtkTransform> AtomTransform(double,double){return 0;};
	void ConcatenateTransform(vtkTransform*,double);
	double TwistAngle(double);
	double TwistAngleFlexible(double);

protected:

	void StationaryRotate(vtkTransform*,double,bool);
};

#endif /* STRAND_H_ */
