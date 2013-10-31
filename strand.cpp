/*
 * strand.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: alinar
 */

#include "strand.h"

Strand::Strand():radius(0),alpha(0),init_torsion_angle(0),
	height(0),basic_strand(false),stationary_rotation(false),
	supreme_strand(false)
{
	for (unsigned i=0;i<MAX_HIETATCHY_COMPLEXITY;i++)
		torsion_additive_angle[i]	=	0;
}


Strand::~Strand() {
	for (unsigned int i; i<cylinders.size() ; i++){
		delete cylinders.at(i);
	}
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
	//renderer->SetBackground((double)204/255,(double)204/255,(double)255/255);

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

void Strand::ConcatenateTransform(vtkTransform* in_trans,double torsion_angle_add){
	double k	=	1/cos(init_torsion_angle * DEG_2_RAD);
	in_trans->Translate(0,0,init_pos[0]*k);
	if (!stationary_rotation){
		in_trans->RotateZ(init_torsion_angle);
		in_trans->RotateY(init_pos[1]);
		in_trans->RotateY(-1*torsion_angle_add);
	}
	else{
		StationaryRotate(in_trans,torsion_angle_add);
	}
}
double Strand::TwistAngle(double in_length){
	double k	=	1/cos(init_torsion_angle * DEG_2_RAD);
	return  atan(in_length*sin(init_torsion_angle * DEG_2_RAD)/(init_pos[0]*k) ) * RAD_2_DEG;
}

void Strand::Seed(){
	unsigned int i=0;
	double l_new,c;

	if (basic_strand){
		vtkSmartPointer<vtkTransform> transform_cat	=	vtkSmartPointer<vtkTransform>::New();
		transform_cat->Identity();
		transform_cat->PostMultiply();
		Strand* strand_iterator;
		i=0;
		c=1;
		for (strand_iterator=this ; !strand_iterator->supreme_strand ; strand_iterator=strand_iterator->parent_strand){
			strand_iterator->ConcatenateTransform(transform_cat,torsion_additive_angle[i]);
			l_new		=	c*length;
			torsion_additive_angle[i]	+=	strand_iterator->TwistAngle(l_new);
			c	*=	cos(strand_iterator->init_torsion_angle * DEG_2_RAD);
			i++;
		}
	transform_cat->Translate(0,height,0);
	height	+=	(length*c);
	AddCylinder();
	cylinders.back()->transform->Concatenate(transform_cat->GetMatrix());
	}
	else
		for (i=0 ; i < sub_strands.size() ; i++)
			sub_strands.at(i)->Seed();
}


void Strand::AddStrand(Strand* new_strand){
		sub_strands.push_back(new_strand);
		new_strand->parent_strand = this;
	}

void Strand::AddCylinder(){
	cylinders.push_back(new Cylinder(this->length - 2));
}
void Strand::StationaryRotate(vtkTransform* transform ,   double torsion_angle_add){
	double point[3]		=	{0,0,0};
	double base[3]		=	{0,0,0};
	double vector[3]	=	{0,0,0};
	double k			=	1/cos(init_torsion_angle * DEG_2_RAD);
	vtkSmartPointer<vtkTransform> aux_trans	=	vtkSmartPointer<vtkTransform> ::New();
	aux_trans->PostMultiply();

	aux_trans->Identity();
	aux_trans->Translate(0,0,init_pos[0]*k);
	aux_trans->RotateY(init_pos[1]);

	aux_trans->TransformPoint(base,base);

	aux_trans->RotateY(-1*torsion_angle_add);
	aux_trans->TransformPoint(point,point);

	vtkMath::Subtract(point,base,vector);

	transform->Translate(0,0,init_pos[0]*k);
	transform->RotateY(init_pos[1]);
	transform->Translate(vector);
	transform->RotateWXYZ(init_torsion_angle,point[0],point[1],point[2]);

}
