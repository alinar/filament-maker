/*
 * PDB.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: alinar
 */
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <vtk-6.0/vtkTransform.h>
#include <vtk-6.0/vtkMath.h>
#include <vtk-6.0/vtkSmartPointer.h>
#include <vtk-6.0/vtkTransform.h>
#include "PDB.h"
using namespace std;

PDB::~PDB(){
	//delete [] residue;
}
int PDB::readFile(const char* f){
	size_t	i	=	0;
	string aux_line;
	fstream file(f);
	if (file.is_open())
	{
		while ( getline (file	,	aux_line ) )
		{
			//cout << lines.at(i) << endl ;
			lines.push_back(aux_line);
			++i;
		}
	}
	cout << "i: " << (i) << endl;
	cout << "size: "<<lines.size() << endl;
	file.close();
	return 1;
}
int PDB::readLines(){
	string num_str,chainID1="\0",chainID2="\0";
	int q = -1,s = -1;
	for (unsigned int i=0 ; i < (lines.size()) ; i++){

		if ( lines.at(i).length() > 4 && lines.at(i).substr(0,4).compare("ATOM") == 0)
		{
			num_str=lines.at(i).substr(22,4);
			chainID1=lines.at(i).substr(21,1);
			q = atoi(num_str.data());
			if (chainID1.compare(chainID2) != 0) addChain(*chainID1.data());
			if (q != s)	chains.back().addResidue(lines.at(i).substr(17,3));
			chains.back().residues.back().addAtom(lines.at(i));
			s = atoi(num_str.data());
			chainID2=lines.at(i).substr(21,1);
		}
	}
	return 1;
}

int PDB::addChain(char chainID_){
	chains.resize(chains.size()+1);
	chains.back().chainID = chainID_;
	return 1;
}

//int PDB::printInfo(int res){
//	cout << "number of residues:" << residues.size() << endl<<"**********************"<<endl;
//	cout << "residue name: " << residues.at(res).type<<endl;
//	cout << "number of atoms: " << residues.at(res).atoms.size() << endl;
//	Atom *atom;
//	for (unsigned int i=0;i<residues.at(res).atoms.size();++i){
//		atom = &residues.at(res).atoms.at(i);
//		cout << "atom name :" << atom->name << endl;
//		cout << "atom element :" << atom->element << endl;
//		cout << "atom position: " <<atom->posX<<" , "<< atom->posY<<" , "<< atom->posZ<< endl<<endl;
//	}
//	return 1;
//}

int PDB::writeFile(char* file_name){
	char atom_number[5];
	char res_num[4];
	char atomX[9];
	char atomY[9];
	char atomZ[9];
	ofstream file(file_name);
	int n=1,m=1;
	string atom_line;
	string term_line(26,' ');

	for (unsigned int i=0; i < chains.size() ; i++){
		for (unsigned int j=0; j < chains.at(i).residues.size() ; j++){
			for (unsigned int k=0; k < chains.at(i).residues.at(j).atoms.size() ; k++){
				atom_line=chains.at(i).residues.at(j).atoms.at(k).line;
				//=== atom count ===
				sprintf(atom_number,"%5d",n );
				atom_line.replace(6,5,atom_number);
				//=== residue count ===
				sprintf(res_num,"%4d",m );
				atom_line.replace(22,4,res_num);
				//=== atom position ===
				sprintf(atomX,"%8.3f",chains.at(i).residues.at(j).atoms.at(k).posX );
				sprintf(atomY,"%8.3f",chains.at(i).residues.at(j).atoms.at(k).posY );
				sprintf(atomZ,"%8.3f",chains.at(i).residues.at(j).atoms.at(k).posZ );
				atom_line.replace(30,8,atomX);
				atom_line.replace(38,8,atomY);
				atom_line.replace(46,8,atomZ);

				file << atom_line<< endl;
				n++;
			}
			m++;
		}
		// add terminator:------------------------------
		term_line.replace(0,26,26,' ');
		term_line.replace(0,3,"TER");
		sprintf(atom_number,"%5d",n);
		term_line.replace(6,5,atom_number);
		term_line.replace(17,3,chains.at(i).residues.back().type);
		term_line.replace(21,1,&chains.at(i).chainID);
		sprintf(res_num,"%4d",m-1);
		term_line.replace(22,4,res_num);
		file << term_line <<endl ;
		n++;
		//-----------------------------------------------
	}

	file.close();
	return 1;
}



void calc (PDB* pdb_obj){
	double pos[3],vector[3],pos_add_1[3]={0,0,0},pos_add_2[3]={0,0,0};
	unsigned int i,j,k,k_aux=0;
	unsigned int n=0,m=0;
	//==============	section 	======================

	for (i=0; i < pdb_obj->chains.size() ; i++){
		for (j=0; j < (int)floor(pdb_obj->chains.at(i).residues.size()*0.5) ; j++){
			for (k=0; k < 2 ; k++){
				m++;
				pos_add_1[0]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posX;
				pos_add_1[1]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posY;
				pos_add_1[2]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posZ;
			}
			m++;
			k_aux	=	pdb_obj->chains.at(i).residues.at(j).atoms.size()-2;
			pos_add_1[0]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k_aux).posX;
			pos_add_1[1]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k_aux).posY;
			pos_add_1[2]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k_aux).posZ;
		}
	}
	pos_add_1[0]	/=	double(m);
	pos_add_1[1]	/=	double(m);
	pos_add_1[2]	/=	double(m);

	for (i=0; i < pdb_obj->chains.size() ; i++){
		for (j=(int)floor(pdb_obj->chains.at(i).residues.size()*0.5); j < pdb_obj->chains.at(i).residues.size() ; j++){
			for (k=0; k < 2 ; k++){
				n++;
				pos_add_2[0]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posX;
				pos_add_2[1]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posY;
				pos_add_2[2]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posZ;
			}
			n++;
			k_aux	=	pdb_obj->chains.at(i).residues.at(j).atoms.size() - 2;
			pos_add_2[0]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k_aux).posX;
			pos_add_2[1]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k_aux).posY;
			pos_add_2[2]+=pdb_obj->chains.at(i).residues.at(j).atoms.at(k_aux).posZ;
		}
	}
	pos_add_2[0]	/=	double(n);
	pos_add_2[1]	/=	double(n);
	pos_add_2[2]	/=	double(n);
	cout <<"pos1:"<<pos_add_1[0]<<" , "<<pos_add_1[1]<<" , "<<pos_add_1[2] << " : "<<m<<endl;
	cout <<"pos2:"<<pos_add_2[0]<<" , "<<pos_add_2[1]<<" , "<<pos_add_2[2] <<" : "<<n<<endl<<endl;
	//==============	section 	======================
	vtkMath::Subtract(pos_add_1,pos_add_2,vector);
	vtkSmartPointer<vtkTransform> trans  = vtkSmartPointer<vtkTransform>::New();
	trans->Identity();
	trans->PostMultiply();
	vtkMath::MultiplyScalar(pos_add_2,-1);
	trans->Translate(pos_add_2);
	double theta = atan (vector[2]/vector[0]) * 180 / M_PI;
	trans->RotateY(theta);
	double alpha = atan (sqrt(vector[0]*vector[0]+vector[2]*vector[2])/vector[1]) * 180 / M_PI;
	trans->RotateZ(alpha);
	cout<<"vector before trans:" <<vector[0] <<","<<vector[1] <<","<<vector[2] <<endl;
	trans->TransformVector(vector,vector);
	cout<<"vector after trans:" <<vector[0] <<","<<vector[1] <<","<<vector[2] <<endl;
	cout<<"theta = "<< theta << endl << "alpha = " << alpha<< endl;
	//==============	section		======================

	for (i=0; i < pdb_obj->chains.size() ; i++){
		for (j=0; j < pdb_obj->chains.at(i).residues.size() ; j++){
			for (k=0; k < pdb_obj->chains.at(i).residues.at(j).atoms.size() ; k++){
				pos[0]	=	pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posX;
				pos[1]	=	pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posY;
				pos[2]	=	pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posZ;
				trans->TransformPoint(pos,pos);
				pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posX	=	pos[0];
				pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posY	=	pos[1];
				pdb_obj->chains.at(i).residues.at(j).atoms.at(k).posZ	=	pos[2];

			}
		}
	}

}


int main (int argc, char *argv[]){
	if (argc == 2){
		PDB pdb;
		char *out_file = "1.pdb";
		pdb.readFile(argv[1]);
		pdb.readLines();
		//pdb.printInfo(3);

		//==============================================
		calc(&pdb);
		pdb.writeFile(out_file);
	}
	else cout <<"Please enter a file name as the input PDB."<< endl ;
	return 0;
}

