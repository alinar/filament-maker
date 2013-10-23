/*
 * sphere.h
 *
 *  Created on: Oct 9, 2013
 *      Author: alinar
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>

class Sphere {

public:
	double position[3];
	double radius;
	static int theta_resolution, phi_resolution;
	vtkSmartPointer<vtkSphereSource> vtk_Sphere;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;

	Sphere();
	virtual ~Sphere();
	int Show (vtkRenderer*);
	int Show ();
	void SetPosition(double x,double y,double z);
	void UpdateActor();

};

#endif /* SPHERE_H_ */
