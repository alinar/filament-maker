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
	cylinders.back() = new Cylinder(13-2 , 1);
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
	vtkSmartPointer<vtkTransform> trans_cat = vtkSmartPointer<vtkTransform>::New();
	double position[3];
	vtkIndent indent;
	const double r=1.00;
	const double R=2.00;
	const double l=13;
	const double a = 1.732;
	const double b = 1.000;
	const double alpha = 10;
	const double beta = 30;
	const double displacement=2;
	const double k=1/cos(alpha * M_PI / 180.0);
	unsigned i;
	double torsion_additive_angle=atan(displacement*tan(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	double torsion_additive_angle_2=atan((l/k - 5*displacement)*tan(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	double torsion_additive_angle_3=atan(l*sin(alpha * M_PI / 180.0)/r) * 180.0 / M_PI;
	double torsion_additive_angle_4=atan((l/k)*sin(alpha * M_PI / 180.0)/R) * 180.0 / M_PI;
	cout << torsion_additive_angle << endl;
	cout << torsion_additive_angle_2 << endl;
	trans_cat->Identity();
	trans_cat->PostMultiply();
	for (i=0;i<10;i++){
		AddCylinder();

		trans_cat->GetMatrix()->PrintSelf(cout,indent);
		cylinders.back()->transform->RotateZ(alpha);
		cylinders.back()->transform->Translate(0,0,r*k);
		cylinders.back()->transform->Concatenate(trans_cat->GetMatrix());
		trans_cat->RotateY(-1*torsion_additive_angle_3);
	}
	trans_cat->Identity();
	trans_cat->PostMultiply();
	trans_cat->RotateY(-180);
	for (i=0;i<10;i++){
		AddCylinder();

		trans_cat->GetMatrix()->PrintSelf(cout,indent);
		cylinders.back()->transform->RotateZ(alpha);
		cylinders.back()->transform->Translate(0,0,r*k);
		cylinders.back()->transform->Concatenate(trans_cat->GetMatrix());
		trans_cat->RotateY(-1*torsion_additive_angle_3);
	}
	trans_cat->Identity();
	trans_cat->PostMultiply();
	for (i=0;i<10;i++){
		cylinders.at(i)->transform->RotateZ(alpha);
		cylinders.at(i)->transform->Translate(0,(i%10)*l/(k*k),2);
		cylinders.at(i)->transform->Concatenate(trans_cat->GetMatrix());
		trans_cat->RotateY(-1*torsion_additive_angle_4);
	}
	trans_cat->Identity();
	trans_cat->PostMultiply();
	for (i=10;i<20;i++){
		cylinders.at(i)->transform->RotateZ(alpha);
		cylinders.at(i)->transform->Translate(0,(i%10)*l/(k*k),2);
		cylinders.at(i)->transform->Concatenate(trans_cat->GetMatrix());
		trans_cat->RotateY(-1*torsion_additive_angle_4);
	}
	//********************************************
	trans_cat->Identity();
	trans_cat->PostMultiply();
	for (i=0;i<10;i++){
		AddCylinder();

		trans_cat->GetMatrix()->PrintSelf(cout,indent);
		cylinders.back()->transform->RotateZ(alpha);
		cylinders.back()->transform->Translate(0,0,r*k);
		cylinders.back()->transform->Concatenate(trans_cat->GetMatrix());
		cylinders.back()->actor->GetProperty()->SetColor(0,0,1);
		trans_cat->RotateY(-1*torsion_additive_angle_3);
	}
	trans_cat->Identity();
	trans_cat->PostMultiply();
	trans_cat->RotateY(-180);
	for (i=0;i<10;i++){
		AddCylinder();

		trans_cat->GetMatrix()->PrintSelf(cout,indent);
		cylinders.back()->transform->RotateZ(alpha);
		cylinders.back()->transform->Translate(0,0,r*k);
		cylinders.back()->transform->Concatenate(trans_cat->GetMatrix());
		cylinders.back()->actor->GetProperty()->SetColor(0,0,1);
		trans_cat->RotateY(-1*torsion_additive_angle_3);
	}
	trans_cat->Identity();
	trans_cat->PostMultiply();
	trans_cat->RotateY(-180);
	for (i=20;i<30;i++){

		cylinders.at(i)->transform->RotateZ(alpha);
		cylinders.at(i)->transform->Translate(0,(i%10)*l/(k*k),2);
		cylinders.at(i)->transform->Concatenate(trans_cat->GetMatrix());
		trans_cat->RotateY(-1*torsion_additive_angle_4);
	}
	trans_cat->Identity();
	trans_cat->PostMultiply();
	trans_cat->RotateY(-180);
	for (i=30;i<cylinders.size();i++){

		cylinders.at(i)->transform->RotateZ(alpha);
		cylinders.at(i)->transform->Translate(0,(i%10)*l/(k*k),2);
		cylinders.at(i)->transform->Concatenate(trans_cat->GetMatrix());
		trans_cat->RotateY(-1*torsion_additive_angle_4);
	}

		AddSphere();
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

