/*
 * main.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: alinar
 */

#include <cstdio>

#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>

#include "filament.h"
#include "cylinder.h"
#include "strand.h"



int main(int, char *argv[])
{
	//	Filament filament;
	//
	//	filament.PlaceElements();
	//	cout<< filament.cylinders.size()<<endl;
	//
	//	filament.Show();
	Strand* strand_basic1=new Strand();
	strand_basic1->basic_strand	=	true;
	strand_basic1->length		=	13;
	strand_basic1->init_pos[0]	=	1;
	strand_basic1->init_pos[1]	=	90;
	strand_basic1->init_pos[2]	=	0;
	strand_basic1->init_torsion_angle	=	0;
	//
	Strand* strand_basic2=new Strand();
	strand_basic2->basic_strand	=	true;
	strand_basic2->length		=	13;
	strand_basic2->init_pos[0]	=	1;
	strand_basic2->init_pos[1]	=	-90;
	strand_basic2->init_pos[2]	=	0;
	strand_basic2->init_torsion_angle	=	0;
	//
	Strand* master_1=new Strand();

	master_1->init_pos[0]	=	2;
	master_1->init_pos[1]	=	0;
	master_1->init_pos[2]	=	0;
	master_1->init_torsion_angle	=	-5;
	master_1->AddStrand(strand_basic1);
	master_1->AddStrand(strand_basic2);
	master_1->stationary_rotation=true;

	//**************************************************
	Strand* strand_basic3=new Strand();
	strand_basic3->basic_strand	=	true;
	strand_basic3->length		=	13;
	strand_basic3->init_pos[0]	=	1;
	strand_basic3->init_pos[1]	=	90;
	strand_basic3->init_pos[2]	=	0;
	strand_basic3->init_torsion_angle	=	0;
	//
	Strand* strand_basic4=new Strand();
	strand_basic4->basic_strand	=	true;
	strand_basic4->length		=	13;
	strand_basic4->init_pos[0]	=	1;
	strand_basic4->init_pos[1]	=	-90;
	strand_basic4->init_pos[2]	=	0;
	strand_basic4->init_torsion_angle	=	0;
	//
	Strand* master_2=new Strand();

	master_2->init_pos[0]	=	2;
	master_2->init_pos[1]	=	180;
	master_2->init_pos[2]	=	0;
	master_2->init_torsion_angle	=	-5;
	master_2->AddStrand(strand_basic3);
	master_2->AddStrand(strand_basic4);
	//******************************************************************
	Strand* master=new Strand();

	master->AddStrand(master_1);
	master->AddStrand(master_2);

	//

	cout << "substrands:" << master->sub_strands.size() << endl;

	for (int i=0;i<10;i++) master->Seed();

	master->Show();

	return EXIT_SUCCESS;
}




