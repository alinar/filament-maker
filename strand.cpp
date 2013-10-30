/*
 * strand.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: alinar
 */

#include "strand.h"

Strand::Strand():radius(0),alpha(0),init_torsion_angle(0),torsion_additive_angle(0),
	height(0),basic_strand(false),stationary_rotation(false)
{
	transform = vtkSmartPointer<vtkTransform>::New();
	transform->Identity();
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

void Strand::Seed(){
	Update();
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

		transform_cat->Translate(0,0,pos[0]*k);
		if (!sub_strands.at(i)->stationary_rotation){
			transform_cat->RotateZ(sub_alpha);
			transform_cat->RotateY(pos[1]);
			transform_cat->RotateY(-1*torsion_additive_angle);
		}
		else{
			StationaryRotate(transform_cat,pos,k,sub_alpha);
		}
		sub_strands.at(i)->Seed(k,transform_cat);
	}

	torsion_additive_angle	=	torsion_additive_angle + atan( sub_length * sin(sub_alpha * DEG_2_RAD)/(pos[0]*k) ) * RAD_2_DEG;
}
	void Strand::Seed(double h,vtkTransform* transform){
		Update();
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

			transform_cat=vtkSmartPointer<vtkTransform>::New();
			transform_cat->Identity();
			transform_cat->PostMultiply();


			transform_cat->Translate(0,0,pos[0]*k);
			if (!sub_strands.at(i)->stationary_rotation){
				transform_cat->RotateZ(sub_alpha);
				transform_cat->RotateY(pos[1]);
				transform_cat->RotateY(-1*torsion_additive_angle);
			}
			else{
				StationaryRotate(transform_cat,pos,k,sub_alpha);
			}

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
	}
}

	void Strand::Update(){
		double new_length;
		for (unsigned int i=0 ; i<sub_strands.size() ; i++){
			new_length	=	sub_strands.at(i)->length / cos(sub_strands.at(i)->init_torsion_angle * DEG_2_RAD);
			if (this->length < new_length) this->length	 =	new_length;
		}
	}

void Strand::AddStrand(Strand* new_strand){
		sub_strands.push_back(new_strand);
	}

void Strand::AddCylinder(){
	cylinders.push_back(new Cylinder(this->length - 2));
}
void Strand::StationaryRotate(vtkTransform* transform , double* pos, double k, double sub_alpha){
	double point[3]={0,0,0};
	double base[3]={0,0,0};
	double vector[3]={0,0,0};
	vtkSmartPointer<vtkTransform> aux_trans	=	vtkSmartPointer<vtkTransform> ::New();
	point[2]=pos[0]*k;
	base[2]=pos[0]*k;
	aux_trans->Identity();
	aux_trans->RotateY(-1*torsion_additive_angle);
	aux_trans->TransformPoint(point,point);
	vtkMath::Subtract(point,base,vector);

	transform->RotateY(pos[1]);
	transform->Translate(vector);

	aux_trans->Identity();
	aux_trans->RotateY(pos[1]);
	aux_trans->TransformPoint(point,point);

	transform->RotateWXYZ(sub_alpha,point[0],point[1],point[2]);

}
