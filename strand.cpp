/*
 * strand.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: alinar
 */

#include "strand.h"

Strand::Strand():init_torsion_angle(0),stationary_rotation(false),
	supreme_strand(false)
{
}



void Strand::Show(vtkRenderer* renderer){
	unsigned int i;
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
	axes->SetTotalLength(10,10,10);

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
double Strand::TwistAngle(double in_length){
	double k	=	1/cos(init_torsion_angle * DEG_2_RAD);
	if (init_pos[0]!=0)
		return  atan(in_length*sin(init_torsion_angle * DEG_2_RAD)/(init_pos[0]*k) ) * RAD_2_DEG;
	else return 0;
}

void Strand::Seed(){
	unsigned int i=0;
	for (i=0 ; i < sub_strands.size() ; i++)
		sub_strands.at(i)->Seed();
}


void Strand::AddStrand(Strand* new_strand){
		sub_strands.push_back(new_strand);
		new_strand->parent_strand = this;
	}



