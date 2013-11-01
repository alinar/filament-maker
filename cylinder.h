/*
 * Cylinder.h
 *
 *  Created on: Oct 8, 2013
 *      Author: alinar
 */

#ifndef CYLINDER_H_
#define CYLINDER_H_

#include <vtkCylinderSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
class Cylinder {

public:
	double position[3];
	double orientation[3];
	double height;
	double radius;
	static int resolution;
	vtkSmartPointer<vtkTransform> transform;
	vtkSmartPointer<vtkCylinderSource> vtk_cylinder;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;


	Cylinder(double,double);
	virtual ~Cylinder();
	int Show (vtkRenderer*);
	int Show ();
	void SetPosition(double x,double y,double z);
	void SetOrientation(double x,double y,double z);
	void UpdateActor();
};

#endif /* CYLINDER_H_ */
