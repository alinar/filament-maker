/*
 * Cylinder.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: alinar
 */

#include <cstdio>
#include <cstdlib>

#include "cylinder.h"

int Cylinder::resolution = 100;

Cylinder::Cylinder(double h=11) : radius(1.0) {
	this->height=h;
	vtk_cylinder = vtkSmartPointer<vtkCylinderSource> :: New();
	mapper = vtkSmartPointer<vtkPolyDataMapper> :: New();
	actor = vtkSmartPointer<vtkActor> :: New();
	transform=vtkSmartPointer<vtkTransform> :: New();

	vtk_cylinder->SetHeight(this->height);
	vtk_cylinder->SetRadius(this->radius);
	vtk_cylinder->SetResolution(this->resolution);
	transform->Identity();
	transform->PostMultiply();
	actor->SetUserTransform(transform);
	mapper->SetInputConnection(this->vtk_cylinder->GetOutputPort());
	actor->SetMapper(this->mapper);
	//actor->GetProperty()->SetOpacity(0.5);
	//actor->GetProperty()->SetColor(1,1,1);
}

Cylinder::~Cylinder() {
	// TODO Auto-generated destructor stub
}

void Cylinder::SetPosition(double x,double y,double z){
	this->position[0] = y ;
	this->position[1] = z ;
	this->position[2] = x ;
	UpdateActor();
}

void Cylinder::SetOrientation(double x,double y,double z){
	this->orientation[0] = y ;
	this->orientation[1] = z ;
	this->orientation[2] = x ;
	UpdateActor();
}

int Cylinder::Show(vtkRenderer *renderer) {
	UpdateActor();
	renderer->AddActor(actor);
	return 1;
}

void Cylinder::UpdateActor(){
//	vtk_cylinder->SetHeight(this->height);
//	vtk_cylinder->SetRadius(this->radius);
//
//	actor->SetPosition(this->position);
//	actor->SetOrientation(this->orientation);
}

int Cylinder::Show(){

	UpdateActor();

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return 1;
}

