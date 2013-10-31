/*
 * xml_file_interactor.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: alinar
 */

#include "xml_file_interactor.h"

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

		master_strand = AddStrand();
		master_strand->supreme_strand	=	true;
		RecursiveAdd (filament_node,master_strand);
	}
	else cerr << "There shout be a node with the name \"filament\" in the XML file. " << endl;

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
	for (xml_node<> *child_node	=	parent_node->first_node(STRAND_STR) ;
			child_node;
			child_node	=	child_node->next_sibling() )
	{
			child_strand	=	AddStrand();
			parent_strand->AddStrand(child_strand);
			r				=	child_node->first_attribute(R_STR);
			theta			=	child_node->first_attribute(THETA_STR);
			z				=	child_node->first_attribute(Z_STR);
			t_ang			=	child_node->first_attribute(TORSION_ANGLE_STR);
			swing			=	child_node->first_attribute(SWING_STR);
			if (r)		child_strand->init_pos[0]			=	atof (r->value() );
			if (theta)	child_strand->init_pos[1]			=	atof (theta->value() );
			if (z)		child_strand->init_pos[2]			=	atof (z->value() );
			if (t_ang)	child_strand->init_torsion_angle	=	atof (t_ang->value() );
			if (swing && strcmp(swing->value() , STATIONARY_STR) == 0)
				child_strand->stationary_rotation=true;

			RecursiveAdd(child_node,child_strand);
	}
	for (xml_node<> *child_node	=	parent_node->first_node(BASIC_STRAND_STR) ;
			child_node;
			child_node	=	child_node->next_sibling())
	{
			child_strand	=	AddStrand();
			parent_strand->AddStrand(child_strand);
			child_strand->basic_strand	=	true;
			r				=	child_node->first_attribute(R_STR);
			theta			=	child_node->first_attribute(THETA_STR);
			z				=	child_node->first_attribute(Z_STR);
			t_ang			=	child_node->first_attribute(TORSION_ANGLE_STR);
			swing			=	child_node->first_attribute(SWING_STR);
			length			=	child_node->first_attribute(LENGTH_STR);
			if (r)		child_strand->init_pos[0]			=	atof (r->value() );
			if (theta)	child_strand->init_pos[1]			=	atof (theta->value() );
			if (z)		child_strand->init_pos[2]			=	atof (z->value() );
			if (t_ang)	child_strand->init_torsion_angle	=	atof (t_ang->value() );
			if (length)	child_strand->length				=	atof (length->value() );
			if (swing && strcmp(swing->value() , STATIONARY_STR) == 0)
				child_strand->stationary_rotation=true;
	}
}

Strand* XMLFileInteractor::AddStrand(){
	Strand *new_strand = new Strand;
	strands.push_back(new_strand);
	return new_strand;
}

void XMLFileInteractor::AddStrand(Strand* strand_){
	strands.push_back(strand_);
}
