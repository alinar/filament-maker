/*
 * Sphere.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: alinar
 */

#include <cstdio>
#include <cstdlib>

#include "sphere.h"

int Sphere::theta_resolution = 50;
int Sphere::phi_resolution = 50;

Sphere::Sphere() : radius(1.0) {
	vtk_Sphere = vtkSmartPointer<vtkSphereSource> :: New();
	mapper = vtkSmartPointer<vtkPolyDataMapper> :: New();
	actor = vtkSmartPointer<vtkActor> :: New();

	vtk_Sphere->SetThetaResolution(theta_resolution);
	vtk_Sphere->SetPhiResolution(phi_resolution);
	mapper->SetInputConnection(this->vtk_Sphere->GetOutputPort());
	actor->SetMapper(this->mapper);
	actor->GetProperty()->SetColor(1,0,0);

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

void Sphere::SetPosition(double x,double y,double z){
	this->position[0] = y ;
	this->position[1] = z ;
	this->position[2] = x ;
}


int Sphere::Show(vtkRenderer *renderer) {
	UpdateActor();
	renderer->AddActor(actor);
	return 1;
}

void Sphere::UpdateActor(){
	vtk_Sphere->SetRadius(this->radius);

	actor->SetPosition(this->position);
}

int Sphere::Show(){

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

