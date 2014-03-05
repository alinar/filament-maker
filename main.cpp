/*
 * main.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: alinar
 */

#include <cstdio>
#include <cstdlib>
#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include "pdb/pdb.h"
#include "pdb/pdb_viewer.h"
#include "cylinder.h"
#include "strand.h"
#include "xml_file_interactor.h"
#include "packing.h"
#include "gyroid.h"
#include <vtktransform.h>

void MakePdbFile(Strand *strand,char *filename){
	PDB pdb,pdb_out;
	char *out_file2 = "filament.pdb";
	pdb.readFile(filename);
	pdb.readLines();
	//pdb.printInfo(3);
	//==============================================
	PDB::TransformToY(&pdb);
	//pdb.writeFile(out_file1);
	PDB::Transformer(&pdb,&pdb_out,strand,3);
	pdb_out.writeFile(out_file2);

}

void MakePacking(XMLFileInteractor* interactor,char *dimer_file){
	PDB dimer,unit,pack_pdb,cube_pdb;
	Packing *packing	=	interactor->packing;
	char *dimer_file_2 = "dimer.pdb";
	char *pack_file = "pack.pdb";
	char *unit_file = "unit.pdb";
	dimer.readFile(dimer_file);
	dimer.readLines();
	PDB::TransformToY(&dimer);
	dimer.writeFile(dimer_file_2);
	cout<<"The dimer is written to the file: "<< dimer_file_2<<endl;
	dimer.GrowToHeight(&unit,interactor->master_strand,interactor->filament_length);
	unit.writeFile(unit_file);
	cout<<"The unit is written to the file: "<< unit_file<<endl;
	packing->packPDB(&unit,&pack_pdb);
	pack_pdb.CuboidRepeat(packing->cuboid_x,packing->cuboid_y,packing->cuboid_z,&cube_pdb);
	cube_pdb.writeFile(pack_file);
	cout<<"The packing is written to the file: "<< unit_file<<endl;
}

void MakeLipidLayer(Gyroid *gyroid){
	char *file_out = "lipid_cell.pdb";
	const char file[] = "lipid.pdb";
	PDB lipid,lipid_cell;
	lipid.readFile(file);
	lipid.readLines();
	vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
	cout<<gyroid->N_poly<<endl;
	while(gyroid->GetNextTransform(trans)){
		//cout<<gyroid->iterator<<endl;
		lipid_cell.CatTransedPDB(trans,&lipid);
	}
	lipid_cell.writeFile(file_out);
	cout<<"The lipid cell is written to the file: "<< file_out<<endl;
}

int main(int argc, char *argv[])
{
//	if (argc<2) {
//		cerr << "Please enter an XML file name as the input argument following with the base molecule pdb file."<<endl
//				<<"Add -v as the third input argument if you want the abstract molecule to be viewed"<<endl;
//		return EXIT_FAILURE;
//	}
//
//	XMLFileInteractor *xml_file_interactor=new XMLFileInteractor(argv[1]);
//
//	xml_file_interactor->MakeStructure();
//
//	if (argc>=4) {
//		cout<<"Viewing the abstract..."<<endl;
//		xml_file_interactor->master_strand->Show();
//	}

//	MakePdbFile(xml_file_interactor->master_strand,argv[2]);

//	if 	(xml_file_interactor->ReadPacking())
//			MakePacking(xml_file_interactor,argv[2]);



	Gyroid *gyroid	=	new Gyroid(796);
	//gyroid->PrepareMolecules();
	MakeLipidLayer(gyroid);

//	delete xml_file_interactor;
	delete gyroid;
	return EXIT_SUCCESS;
}
