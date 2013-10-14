/*
 * Filament.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: alinar
 */

#include <cstdio>
#include <cstdlib>
#include <math.h>

#include "filament.h"



Filament::~Filament() {
	for (unsigned int i=0 ; i < cylinders.size() ; i++){
		delete cylinders.at(i);
	}
	for (unsigned int i=0 ; i < spheres.size() ; i++){
		delete spheres.at(i);
	}
}

void Filament::AddCylinder(){
	cylinders.resize(cylinders.size()+1);
	cylinders.back() = new Cylinder();
}

void Filament::AddSphere(){
	spheres.resize(spheres.size()+1);
	spheres.back() = new Sphere();
}

int Filament::Show(){
	vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
			vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	// Add the actor to the scene

	for (unsigned int i=0 ; i < cylinders.size() ; i++){
		cylinders.at(i)->Show(renderer);
	}
	for (unsigned int i=0 ; i < spheres.size() ; i++){
		spheres.at(i)->Show(renderer);
	}
	renderer->SetBackground((double)204/255,(double)204/255,(double)255/255);

	// Render and interact
	renderWindow->SetWindowName("Filament");
	renderWindow->Render();
	renderWindowInteractor->Start();

	return 1;
}

void Filament::PlaceElements(){
	const double r=2.00;
	const double l=13;
	const double a = 1.732;
	const double b = 1.000;
	const double alpha =5;
	const double displacement=2;
	const double k=1/cos(alpha * M_PI / 180.0);
	double torsion_addetive_angle=atan(displacement*sin(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	double torsion_addetive_angle_2=atan(0.5*l*sin(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	cout << torsion_addetive_angle << endl;

	for (int s=0 ; s<3 ; s++){
		for (int i=0 ; i<6 ; i++){
			AddCylinder();
			//cylinders.back()->actor->RotateZ(alpha);
			cylinders.back()->actor->SetPosition(0,i*displacement + s*l/k,r*k);
			cylinders.back()->actor->SetOrigin(0,0,-r*k);
			cylinders.back()->actor->RotateWXYZ(-1 * i * (60 + torsion_addetive_angle)
					- 2 * s * torsion_addetive_angle_2,0,1,0); //YES!!
			cylinders.back()->actor->RotateZ(alpha);
			if (i % 6 == 0) cylinders.back()->actor->GetProperty()->SetColor(0,0,1);
			//cylinders.back()->actor->GetProperty()->SetColor(0,0,0);

			//AddSphere();
			//spheres.back()->actor->SetPosition(0 , 0.5*l*sin(alpha * M_PI / 180.0)/r + i*displacement),r*k);
		}

	}
	AddSphere();
	spheres.back()->actor->GetProperty()->SetColor(0,1,0);
	//	AddSphere();
	//	spheres.back()->SetPosition(2,0,21);
	//	AddSphere();
	//	spheres.back()->SetPosition(b,a,5+21);
	//	AddSphere();
	//	spheres.back()->SetPosition(-1*b,a,10+21);
	//	AddSphere();
	//	spheres.back()->SetPosition(-2,0,15+21);
	//	AddSphere();
	//	spheres.back()->SetPosition(-1*b,-1*a,20+21);
	//	AddSphere();
	//	spheres.back()->SetPosition(b,-1*a,25+21);
	//
	//	AddCylinder();
	//	cylinders.back()->SetPosition(2,0,0+42);
	//	AddCylinder();
	//	cylinders.back()->SetPosition(b,a,5+42);
	//	AddCylinder();
	//	cylinders.back()->SetPosition(-1*b,a,10+42);
	//	AddCylinder();
	//	cylinders.back()->SetPosition(-2,0,15+42);
	//	AddCylinder();
	//	cylinders.back()->SetPosition(-1*b,-1*a,20+42);
	//	AddCylinder();
	//	cylinders.back()->SetPosition(b,-1*a,25+42);


}

