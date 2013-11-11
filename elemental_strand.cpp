/*
 * elemental_strand.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: alinar
 */

#include "elemental_strand.h"

ElementalStrand::ElementalStrand():radius(1.0),length(13.0),
	height(0){
		for (unsigned i=0;i<MAX_HIERARCHY_COMPLEXITY;i++)
			torsion_additive_angle[i]	=	0;

		init_torsion_angle	=	0;
		stationary_rotation	=	false;
		supreme_strand		=	false;
}

ElementalStrand::~ElementalStrand(){
	for (unsigned int i=0 ; i<cylinders.size() ; i++){
		delete cylinders.at(i);
	}
}

void ElementalStrand::Seed(){
	unsigned int i=0;
	double l_new,c;
		vtkSmartPointer<vtkTransform> transform_cat	=	vtkSmartPointer<vtkTransform>::New();
		transform_cat->Identity();
		transform_cat->PostMultiply();
		Strand* strand_iterator;
		i=0;
		c=1;
		for (strand_iterator=this ; !strand_iterator->supreme_strand ; strand_iterator=strand_iterator->parent_strand){
			strand_iterator->ConcatenateTransform(transform_cat,torsion_additive_angle[i]);
			l_new						=	c*length;
			torsion_additive_angle[i]	+=	strand_iterator->TwistAngle(l_new);
			c							*=	cos(strand_iterator->init_torsion_angle * DEG_2_RAD);
			i++;
		}
	transform_cat->Translate(0,height,0);
	height	+=	(length*c);
	AddCylinder();
	cylinders.back()->transform->Concatenate(transform_cat->GetMatrix());

}

vtkSmartPointer<vtkTransform> ElementalStrand::AtomTransform(double atom_height_in_strand, double atom_height_in_dimere){
	double height_new,c;
	double atom_torsion_angle;
		vtkSmartPointer<vtkTransform> transform_cat	=	vtkSmartPointer<vtkTransform>::New();
		transform_cat->Identity();
		transform_cat->PostMultiply();
		Strand* strand_iterator;
		c=1;
		//to make RotateZ work fine.
		transform_cat->Translate(0,-1*atom_height_in_dimere,0);
		for (strand_iterator=this ; !strand_iterator->supreme_strand ; strand_iterator=strand_iterator->parent_strand){
			height_new				=	c*atom_height_in_strand;
			atom_torsion_angle		=	strand_iterator->TwistAngleFlexible(height_new);
			strand_iterator->ConcatenateTransform(transform_cat,atom_torsion_angle);
			c						*=	cos(strand_iterator->init_torsion_angle * DEG_2_RAD);
		}
	transform_cat->Translate(0,c*atom_height_in_strand,0);

	return transform_cat;
}

void ElementalStrand::Show(vtkRenderer* renderer){
	unsigned int i;
	for (i=0 ; i<cylinders.size() ; i++){
		cylinders.at(i)->Show(renderer);
	}
}

void ElementalStrand::AddCylinder(){
		cylinders.push_back(new Cylinder(this->length - 0.1*this->length , this->radius));
	}
