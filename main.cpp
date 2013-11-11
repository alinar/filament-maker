/*
 * main.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: alinar
 */

#include <cstdio>
#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include "pdb/pdb.h"
#include "pdb/pdb_viewer.h"
#include "cylinder.h"
#include "strand.h"
#include "xml_file_interactor.h"

void MakePdbFile(Strand *strand,char *filename){
	PDB pdb,pdb_out;
	char *out_file1 = "1.pdb";
	char *out_file2 = "2.pdb";
	pdb.readFile(filename);
	pdb.readLines();
	//pdb.printInfo(3);
	//==============================================
	PDB::TransformToY(&pdb);
	pdb.writeFile(out_file1);
	PDB::Transformer(&pdb,&pdb_out,strand,3);
	pdb_out.writeFile(out_file2);

}

int main(int argc, char *argv[])
{
	if (argc<2) {
		cerr << "Please enter an XML file name as the input argument."<<endl ;
		return EXIT_FAILURE;
	}

	XMLFileInteractor *xml_file_interactor=new XMLFileInteractor(argv[1]);

	xml_file_interactor->MakeStructure();

	xml_file_interactor->master_strand->Show();

	MakePdbFile(xml_file_interactor->master_strand,argv[2]);

	delete xml_file_interactor;

	return EXIT_SUCCESS;
}




