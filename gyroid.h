/*
 * gyroid.h
 *
 *  Created on: Mar 3, 2014
 *      Author: alinar
 */

#ifndef GYROID_H_
#define GYROID_H_

#include <vtkmarchingcubes.h>
#include <vtkpolydata.h>
#include <vtksmartpointer.h>
#include "pdb.h"

class Gyroid {
public:
	vtkSmartPointer<vtkMarchingCubes>	marchingCubes;
	vtkSmartPointer<vtkPolyData>		surface_poly;
	vtkSmartPointer<vtkDataArray>		surface_normal ;
	vtkSmartPointer<vtkDataObject>		surface_data ;
	PDB pdb[3];
	double period;

	void reset(){this->iterator = 0;}
	double Function(double x,double y, double z){
		return sin(x)*cos(y)+sin(y)*cos(z)+sin(z)*cos(x);
	}
	int GetNextTransform(vtkTransform*);
	void PrepareMolecules();
	vtkTransform* ExtractTransform(double*,double*);
	explicit Gyroid(double);

//protected:
	vtkIdType iterator;
	vtkIdType N_poly;
};

#endif /* GYROID_H_ */
