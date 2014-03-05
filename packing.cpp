/*
 * packing.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: alinar
 */

#include "packing.h"

Packing::Packing(Strand* unit_strand_):number_of_units(0) {
	unit_strand	=	unit_strand_;
}

Packing::~Packing() {
}

void Packing::AddUnit(double alpha_,double beta_,double gamma_,
		double x_,double y_,double z_){
	alpha.push_back(alpha_);
	beta.push_back(beta_);
	gamma.push_back(gamma_);
	pos_x.push_back(x_);
	pos_y.push_back(y_);
	pos_z.push_back(z_);
	number_of_units++;
}

vtkSmartPointer<vtkTransform> Packing::UnitTransformer(unsigned int unit_number){
	vtkSmartPointer<vtkTransform>	trans	=	vtkSmartPointer<vtkTransform>::New();
	trans->Identity();
	trans->PostMultiply();
	trans->RotateY(gamma.at(unit_number));
	trans->RotateX(beta.at(unit_number));
	trans->RotateY(alpha.at(unit_number));
	trans->Translate(pos_x.at(unit_number),pos_y.at(unit_number),pos_z.at(unit_number));
	return trans;
}

void Packing::packPDB(PDB* pdb_in, PDB* pdb_out){
	vtkSmartPointer<vtkTransform>	trans;
	unsigned int i;

	pdb_in->BringToCenter();
	cout<<"number_of_units:"<<this->number_of_units<<endl;
	for (i=0 ; i<this->number_of_units ; i++)
	{
		trans	=	this->UnitTransformer(i);
		pdb_out->CatTransedPDB(trans, pdb_in);
	}

}

