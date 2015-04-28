/*
 * xml_file_interactor.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: alinar
 */
#include <iostream>
#include "xml_file_interactor.h"
using namespace std;
using namespace rapidxml;

XMLFileInteractor::XMLFileInteractor(char* file_name) {
	ReadFile(file_name);
	cout<<str<<endl;
	Parse();
}
XMLFileInteractor::~XMLFileInteractor() {
	delete [] str;
	for (unsigned int i; i<strands.size() ; i++){
		if (strands.at(i)) {
			delete strands.at(i);
			strands.at(i)=NULL;
		}
	}
	if (packing) delete packing;
}

int XMLFileInteractor::ReadFile(char* file_name){
	fstream file(file_name);
	int length;
	if (file.is_open()){
		file.seekg(0, ios::end);	// go to the end
		length = file.tellg();		// report location (this is the length)
		file.seekg(0, ios::beg);
		this->str = new char[length];
		file.read(str,length+1);
		file.close();
		str[length]='\0';
	}
	else cerr<<"There is no file with the name."<<file_name<<endl;
	return 1;
}

void XMLFileInteractor::Parse(){
	doc.parse<0>(str);
}

void XMLFileInteractor::MakeStructure(){
	xml_attribute<> *attr;
	xml_node<> *filament_node = doc.first_node(FILAMENT_STR);
	if (filament_node){
		attr	=	filament_node->first_attribute(NUMBER_OF_ROWS_STR);
		if (attr) number_of_rows=atoi(attr->value());
		attr	=	filament_node->first_attribute(LENGTH_STR);
		if (attr) filament_length=atoi(attr->value()) * NANOMETER;
		attr	=	filament_node->first_attribute(FILE_OUT);
		if (attr) output_file=(attr->value());
		master_strand = AddNewStrand();
		master_strand->supreme_strand	=	true;
		RecursiveAdd (filament_node,master_strand);
	}
	else cerr << "There should be a node with the name \"filament\" in the XML file. " << endl;

	for (unsigned int i=0;i<number_of_rows;i++){
		master_strand->Seed();
	}
}
void XMLFileInteractor::RecursiveAdd(xml_node<> *parent_node, Strand *parent_strand){
	Strand *child_strand;
	xml_attribute<>* r;
	xml_attribute<>* theta;
	xml_attribute<>* z;
	xml_attribute<>* t_ang;
	xml_attribute<>* swing;
	xml_attribute<>* length;
	xml_attribute<>* diameter;
	for (xml_node<> *child_node	=	parent_node->first_node(STRAND_STR) ;
			child_node;
			child_node	=	child_node->next_sibling(STRAND_STR) )
	{
		child_strand	=	AddNewStrand();
		parent_strand->AddStrand(child_strand);
		r				=	child_node->first_attribute(R_STR);
		theta			=	child_node->first_attribute(THETA_STR);
		z				=	child_node->first_attribute(Z_STR);
		t_ang			=	child_node->first_attribute(TORSION_ANGLE_STR);
		swing			=	child_node->first_attribute(SWING_STR);
		if (r)		child_strand->init_pos[0]			=	atof (r->value() ) * NANOMETER;
		if (theta)	child_strand->init_pos[1]			=	atof (theta->value() );
		if (z)		child_strand->init_pos[2]			=	atof (z->value() ) * NANOMETER;
		if (t_ang)	child_strand->init_torsion_angle	=	atof (t_ang->value() );
		if (swing && strcmp(swing->value() , STATIONARY_STR) == 0)
			child_strand->stationary_rotation=true;

		RecursiveAdd(child_node,child_strand);
	}
	for (xml_node<> *child_node	=	parent_node->first_node(BASIC_STRAND_STR) ;
			child_node;
			child_node	=	child_node->next_sibling(BASIC_STRAND_STR) ){
		child_strand	=	AddNewElementalStrand();
		parent_strand->AddStrand(child_strand);
		r				=	child_node->first_attribute(R_STR);
		theta			=	child_node->first_attribute(THETA_STR);
		z				=	child_node->first_attribute(Z_STR);
		t_ang			=	child_node->first_attribute(TORSION_ANGLE_STR);
		swing			=	child_node->first_attribute(SWING_STR);
		length			=	child_node->first_attribute(LENGTH_STR);
		diameter		=	child_node->first_attribute(DIAMETER_STR);
		if (r)		child_strand->init_pos[0]			=	atof (r->value() ) * NANOMETER;
		if (theta)	child_strand->init_pos[1]			=	atof (theta->value() );
		if (z)		child_strand->init_pos[2]			=	atof (z->value() ) * NANOMETER;
		if (t_ang)	child_strand->init_torsion_angle	=	atof (t_ang->value() );
		if (length)	static_cast<ElementalStrand*>(child_strand)->length		=	atof (length->value() ) * NANOMETER;
		if (diameter) static_cast<ElementalStrand*>(child_strand)->radius	=	atof (diameter->value()) * 0.5 * NANOMETER;
		if (swing && strcmp(swing->value() , STATIONARY_STR) == 0)
			child_strand->stationary_rotation=true;
	}
}
int XMLFileInteractor::ReadPacking(){
	double alpha,beta,gamma,x,y,z;
	xml_attribute<> *alpha_atr,*beta_atr,*gamma_atr,*x_atr,*y_atr,*z_atr;
	xml_node<> *packing_node = doc.first_node(PACKING_STR);
	if (packing_node){
		packing	=	new Packing(this->master_strand);
		cout << "read packing information from the xml file...";
		for (xml_node<> *unit	=	packing_node->first_node(UNIT_STR) ;
				unit;
				unit	=	unit->next_sibling(UNIT_STR) ){
			alpha_atr	=	unit->first_attribute(ALPHA_STR);
			beta_atr	=	unit->first_attribute(BETA_STR);
			gamma_atr	=	unit->first_attribute(GAMMA_STR);
			x_atr		=	unit->first_attribute(X_STR);
			y_atr		=	unit->first_attribute(Y_STR);
			z_atr		=	unit->first_attribute(Z_STR);
			if (alpha_atr)	alpha	=	atof(alpha_atr->value());
			if (beta_atr)	beta	=	atof(beta_atr->value());
			if (gamma_atr)	gamma	=	atof(gamma_atr->value());
			if (x_atr)		x		=	atof(x_atr->value()) * NANOMETER;
			if (y_atr)		y		=	atof(y_atr->value()) * NANOMETER;
			if (z_atr)		z		=	atof(z_atr->value()) * NANOMETER;
			packing->AddUnit(alpha,beta,gamma,x,y,z);
		}
		xml_node<> *cuboid	=	packing_node->first_node(CUBOID_STR);
		if (cuboid) {
			x_atr		=	cuboid->first_attribute(X_STR);
			y_atr		=	cuboid->first_attribute(Y_STR);
			z_atr		=	cuboid->first_attribute(Z_STR);
			if (x_atr)	packing->cuboid_x	=	atof(x_atr->value()) * NANOMETER;
			if (y_atr)	packing->cuboid_y	=	atof(y_atr->value()) * NANOMETER;
			if (z_atr)	packing->cuboid_z	=	atof(z_atr->value()) * NANOMETER;

		}
		cout << "successful" << endl ;
		return 1;
	}
	else return 0;
}
Strand* XMLFileInteractor::AddNewStrand(){
	Strand *new_strand = new Strand;
	strands.push_back(new_strand);
	return new_strand;
}
ElementalStrand* XMLFileInteractor::AddNewElementalStrand(){
	ElementalStrand *new_strand = new ElementalStrand;
	strands.push_back(new_strand);
	return new_strand;
}
