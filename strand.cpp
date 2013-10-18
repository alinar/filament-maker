/*
 * strand.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: alinar
 */

#include "strand.h"

Strand::Strand():position({0,0,0}),radius(2),alpha(5) {
}

Strand::~Strand() {

}

void Strand::RotateWXYZ(double angle,double x,double y,double z){
	unsigned int i;
	for (i=0 ; i<strands.size() ; i++){
		strands.at(i)->RotateWXYZ(angle,x,y,z);
	}
	for (i=0 ; i<cylinders.size() ; i++){
		cylinders.at(i)->actor->RotateWXYZ(angle,x,y,z);
	}
}

void Strand::Translate (double x,double y,double z){
	unsigned int i;
	for (i=0 ; i<strands.size() ; i++){
		strands.at(i)->Translate(x,y,z);
	}
	for (i=0 ; i<cylinders.size() ; i++){
		cylinders.at(i)->transform->Translate(x,y,z);
	}
}

void Strand::Show(vtkRenderer* renderer){
	unsigned int i;
	for (i=0 ; i<cylinders.size() ; i++){
		cylinders.at(i)->Show(renderer);
	}
	for (i=0 ; i<strands.size() ; i++){
		strands.at(i)->Show(renderer);
	}
}

void Strand::Show(){
	vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
			vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderer->SetBackground((double)204/255,(double)204/255,(double)255/255);

	//add axis
	vtkSmartPointer<vtkAxesActor> axes =
			vtkSmartPointer<vtkAxesActor>::New();
	axes->AxisLabelsOff();
	axes->SetTotalLength(5,5,5);

	//Add actors:
	renderer->AddActor(axes);
	this->Show(renderer);

	// Render and interact
	renderWindow->SetWindowName("Filament");
	renderWindow->Render();
	renderWindowInteractor->Start();

}

void Strand::AddStrand(){
	strands.push_back(new Strand);
}
void Strand::AddCylinder(){
	cylinders.push_back(new Cylinder);
}
