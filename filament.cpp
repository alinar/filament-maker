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
	//add axis
	vtkSmartPointer<vtkAxesActor> axes =
			vtkSmartPointer<vtkAxesActor>::New();
	axes->AxisLabelsOff();
	axes->SetTotalLength(5,5,5);

	renderer->AddActor(axes);

	// Render and interact
	renderWindow->SetWindowName("Filament");
	renderWindow->Render();
	renderWindowInteractor->Start();

	return 1;
}

void Filament::PlaceElements(){
	vtkIndent ind;
	vtkSmartPointer<vtkTransform> transform ;
	double position[3];
	const double r=2.00;
	const double l=13;
	const double a = 1.732;
	const double b = 1.000;
	const double alpha = 5;
	const double beta = 30;
	const double displacement=2;
	const double k=1/cos(alpha * M_PI / 180.0);
	double torsion_additive_angle=atan(displacement*tan(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	double torsion_additive_angle_2=atan((l/k - 5*displacement)*tan(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	double torsion_additive_angle_3=2*atan((0.5*l)*sin(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	cout << torsion_additive_angle << endl;
	cout << torsion_additive_angle_2 << endl;
	for (int s=0 ; s<10 ; s++){
		for (int i=0 ; i<6 ; i++){
			transform = vtkSmartPointer<vtkTransform> ::New();
			transform->Identity();

			transform->PostMultiply();

			transform->Translate(r*k,displacement*i,0);
			//transform->RotateX(alpha);
			cout<<transform->GetPosition()[0]<<","<<transform->GetPosition()[1]<<","<<transform->GetPosition()[2]<<endl;
			transform->RotateY(-60*i+torsion_additive_angle);
			transform->GetMatrix()->PrintSelf(cout,ind);
			position[0]=transform->GetPosition()[0];position[1]=transform->GetPosition()[1];position[2]=transform->GetPosition()[2];

			transform->Translate(-1*position[0],-1*position[1],-1*position[2]);
			transform->GetMatrix()->PrintSelf(cout,ind);
			//transform->RotateWXYZ(beta,1,0,0);
			transform->Translate(4,s*l/k,0);
			transform->GetMatrix()->PrintSelf(cout,ind);
			//transform->RotateX(beta);
			transform->RotateWXYZ(-1*beta*s,0,1,0);
			transform->GetMatrix()->PrintSelf(cout,ind);
			cout<<"**********************************"<<endl;
			transform->Translate(position);

			AddCylinder();
			cylinders.back()->actor->SetUserTransform(transform);

			if (i == 0) cylinders.back()->actor->GetProperty()->SetColor(0,0,1);
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

