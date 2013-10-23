/*
 * strand.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: alinar
 */

#include "strand.h"

Strand::Strand():radius(0),alpha(0),init_torsion_angle(0),torsion_additive_angle(0),height(0),basic_strand(false) {
	transform = vtkSmartPointer<vtkTransform>::New();
	transform->Identity();
}
//Strand::Strand(double* init_pos_):radius(2),alpha(5){
//	init_pos[0]	=	init_pos_[0];
//	init_pos[1]	=	init_pos_[1];
//	init_pos[2]	=	init_pos_[2];
//	transform = vtkSmartPointer<vtkTransform>::New();
//	transform->Identity();
//	transform->PostMultiply();
//	this->RotateWXYZ(alpha,0,0,1);//RotateZ
//	this->Translate(0,init_pos[2],init_pos[1]);
//	this->RotateWXYZ(init_pos[0],0,1,0);//RotateY
//}
//Strand::Strand(double theta,double r,double z):radius(2),alpha(5){
//	init_pos[0]	=	theta;
//	init_pos[1]	=	r;
//	init_pos[2]	=	z;
//	transform = vtkSmartPointer<vtkTransform>::New();
//	transform->Identity();
//	transform->PostMultiply();
//	transform->RotateZ(alpha);
//	transform->Translate(0,init_pos[2],init_pos[1]);
//	transform->RotateY(init_pos[0]);
//}

Strand::~Strand() {
}

void Strand::RotateWXYZ(double angle,double x,double y,double z){
	unsigned int i;
	for (i=0 ; i<sub_strands.size() ; i++){
		sub_strands.at(i)->RotateWXYZ(angle,x,y,z);
	}
	for (i=0 ; i<cylinders.size() ; i++){
		cylinders.at(i)->transform->RotateWXYZ(angle,x,y,z);
	}
}

void Strand::Translate (double x,double y,double z){
	unsigned int i;
	for (i=0 ; i<sub_strands.size() ; i++){
		sub_strands.at(i)->Translate(x,y,z);
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
	for (i=0 ; i<sub_strands.size() ; i++){
		sub_strands.at(i)->Show(renderer);
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

	//Add axis
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

void Strand::Seed(){
	unsigned int i;
	double* pos;
	double sub_length,sub_alpha,k;
	double sub_radius,z=0;
	vtkSmartPointer<vtkTransform> transform_cat;


	for (i=0 ; i<sub_strands.size() ; i++){
		transform_cat=vtkSmartPointer<vtkTransform>::New();
		transform_cat->Identity();
		transform_cat->PostMultiply();
		sub_length	=	sub_strands.at(i)->length;
		sub_alpha	=	sub_strands.at(i)->init_torsion_angle;
		pos			=	sub_strands.at(i)->init_pos;
		k			=	1/cos(sub_alpha * DEG_2_RAD);
		cout << "main_torsion: " << torsion_additive_angle << endl;
		transform_cat->RotateZ(sub_alpha);
		transform_cat->Translate(0,0,pos[0]*k);
		transform_cat->RotateY(pos[1]);
		transform_cat->RotateY(-1*torsion_additive_angle);

		sub_strands.at(i)->Seed(k,transform_cat);
	}

	torsion_additive_angle	=	torsion_additive_angle + atan( sub_length * sin(sub_alpha * DEG_2_RAD)/(pos[0]*k) ) * RAD_2_DEG;
}
	void Strand::Seed(double h,vtkTransform* transform){
		vtkSmartPointer<vtkTransform> transform_cat;

		unsigned int i;
		double* pos;
		double sub_length,sub_alpha,k;
		double sub_radius,z=0;

	if (!this->basic_strand){
		for (i=0 ; i<sub_strands.size() ; i++){
			sub_length	=	sub_strands.at(i)->length;
			sub_alpha	=	sub_strands.at(i)->init_torsion_angle;
			pos			=	sub_strands.at(i)->init_pos;
			k			=	1/cos(sub_alpha * DEG_2_RAD);


			cout << "torsion: " << torsion_additive_angle << endl;
			transform_cat=vtkSmartPointer<vtkTransform>::New();
			transform_cat->Identity();
			transform_cat->PostMultiply();


			transform_cat->RotateZ(sub_alpha);
			transform_cat->Translate(0,0,pos[0]*k);
			transform_cat->RotateY(pos[1]);
			transform_cat->RotateY(-1*torsion_additive_angle);
			transform_cat->Concatenate(transform->GetMatrix());
			sub_strands.at(i)->Seed(k*h,transform_cat);
		}

		torsion_additive_angle	=	torsion_additive_angle + atan( sub_length * sin(sub_alpha * DEG_2_RAD)/(pos[0]*k) ) * RAD_2_DEG;
	}
	else{
		AddCylinder();
		cylinders.back()->transform->Concatenate(transform->GetMatrix());
		cylinders.back()->transform->Translate(0,this->height,0);
		height	=	this->height + this->length / h;
		vtkIndent indent;
		//cylinders.back()->transform->PrintSelf(cout,indent);
	}
}

void Strand::AddStrand(Strand* new_strand){
		sub_strands.push_back(new_strand);
		double new_length	=	new_strand->length / cos(new_strand->init_torsion_angle * DEG_2_RAD);
		if (this->length < new_length) this->length	 =	new_length;
	}
void Strand::AddStrand(){
	sub_strands.push_back(new Strand);
}
void Strand::AddCylinder(){
	cylinders.push_back(new Cylinder());
}
