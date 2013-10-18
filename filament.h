/*
 * Filament.h
 *
 *  Created on: Oct 8, 2013
 *      Author: alinar
 */

#ifndef FILAMENT_H_
#define FILAMENT_H_

#include <vector>

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

#include <vtkTransform.h> //for 3D calculations
#include <vtkAxesActor.h>
#include "cylinder.h"
#include "sphere.h"

using namespace std;

class Filament {
public:

	vector<Cylinder*> cylinders;
	vector<Sphere*> spheres;

	~Filament();
	void AddCylinder();
	void AddSphere();

	int Show();
	void PlaceElements();
};

#endif /* FILAMENT_H_ */
