/*
 * gyroid.cpp
 *
 *  Created on: Mar 3, 2014
 *      Author: alinar
 */
#define _USE_MATH_DEFINES
#include "gyroid.h"
#include <vtkTransform.h>
#include <vtkimagedata.h>
#include <vtkpolygon.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkMath.h>
#include <cmath>

Gyroid::Gyroid(double side_length_) : iterator(0),N_poly(0),step_number(32){
	this->side_length	=	side_length_;
	this->marchingCubes	=	vtkSmartPointer<vtkMarchingCubes>::New();
	vtkSmartPointer<vtkImageData> volume	=	vtkSmartPointer<vtkImageData>::New();

	vtkCell	*cell;
	vtkPolygon *polygon;
	double pos[3];
	double x,y,z,f;
	double step	=	4 * M_PI / double(this->step_number);
	volume->SetDimensions(this->step_number, this->step_number, this->step_number);
	volume->AllocateScalars(VTK_DOUBLE,1);
	for ( int i=0 ; i<this->step_number ; i++){
		for ( int j=0 ; j<this->step_number ; j++){
			for ( int k=0 ; k<this->step_number ; k++){
				x=i*step;
				y=j*step;
				z=k*step;
				f=sin(x)*cos(y)+sin(y)*cos(z)+sin(z)*cos(x);
				volume->SetScalarComponentFromDouble(i,j,k,0,f);
			}
		}
	}

	this->marchingCubes->SetInputData(volume);
	this->marchingCubes->ComputeNormalsOn();
	this->marchingCubes->SetValue(0, 0);
	//	surface->SetValue(1, -1.49);
	//	surface->SetValue(1, 1);

	this->marchingCubes->Update();
	this->marchingCubes->UpdateInformation();
	surface_poly = this->marchingCubes->GetOutput(0);
	surface_poly->GetPoints()->Print(cout);
	cout << surface_poly->GetNumberOfCells()<<endl ;
	cout << surface_poly->GetNumberOfPoints()<<endl ;
	//surface_poly->Print(cout);
	surface_normal=surface_poly->GetPointData()->GetNormals();
	//surface_normal->Print(cout);
	this->N_poly = surface_poly->GetNumberOfCells();
}


void Gyroid::PrepareMolecules(){
	vtkSmartPointer<vtkTransform> trans	=	vtkSmartPointer<vtkTransform>::New();
	const char	*file1	=	"1.pdb";
	const char	*file2	=	"2.pdb";
	const char	*file3	=	"3.pdb";
	pdb[0].readFile(file1);
	pdb[1].readFile(file2);
	pdb[2].readFile(file3);
	pdb[0].readLines();
	pdb[1].readLines();
	pdb[2].readLines();

	pdb[0].BringToCenter();
	pdb[1].BringToCenter();
	pdb[2].BringToCenter();

	trans->Identity();
	trans->PostMultiply();
	trans->RotateX(90);

	PDB out;
	double vector[3]	=	{2.5,0,0};
	trans->RotateY(180.0);
	trans->Translate(vector);
	trans->RotateY(0.0);
	pdb[0].ApplyTransform(trans);
	trans->RotateX(180.0);
	trans->Translate(0,-30,0);
	trans->RotateY(120.0);
	pdb[2].ApplyTransform(trans);
	trans->RotateY(100.0);
	pdb[1].ApplyTransform(trans);
	out.Concatenate(&pdb[0]);
	out.Concatenate(&pdb[1]);
	out.Concatenate(&pdb[2]);
	out.writeFile("lipid.pdb");
}

vtkTransform* Gyroid::ExtractTransform(double *coor,double *normal){
	vtkSmartPointer<vtkTransform> trans	=	vtkSmartPointer<vtkTransform>::New();
	trans->Identity();
	trans->PostMultiply();
	trans->Translate(coor);

	return trans;
}

int Gyroid::GetNextTransform(vtkTransform* trans){
	if (this->iterator >= this->N_poly) return 0;
	vtkCell *cell;
	vtkPolygon *polygon;
	double normal[3]={0,0,0};
	double coor[4][3];
	double center[3]={0,0,0};
	int N;
	vtkIdType id,cellId=this->iterator;

	cell	=	surface_poly->GetCell(cellId);

	polygon = static_cast<vtkPolygon*>(cell);
	N	=	polygon->GetNumberOfPoints();
	if (N != 3 ) cout <<"cell with more than 3: "<< cellId << endl;
	if (N == 0) return 1;
	normal[0]=0.0;normal[1]=0.0;normal[2]=0.0;
	center[0]=0.0;center[1]=0.0;center[2]=0.0;
	for (int i=0 ; i<N ; i++){
		//		polygon->GetPoints()->GetPoint(id, coor);
		id	=	polygon->GetPointId(i);
		surface_poly->GetPoints()->GetPoint(id,coor[i]);
		vtkMath::Add(center,coor[i],center);
		vtkMath::Add(normal,surface_normal->GetTuple(id),normal);
	}
	//cout << center[0]<<","<<center[1]<<","<<center[2]<<endl;
	vtkMath::MultiplyScalar(center , this->side_length / (N * (this->step_number - 1)) );
	vtkMath::Normalize(normal);
	trans->Identity();
	trans->PostMultiply();
	double phi,theta;
	phi		= acos(normal[1]) * RAD_2_DEG;
	theta	= atan(normal[2]/normal[0]) * RAD_2_DEG;
	if (normal[0]<0) theta = theta + 180;
	trans->RotateZ(-1*phi);
	trans->RotateY(-1*theta);
	trans->Translate(center);
	this->iterator++;

//	testing:
//	double unit_v[3]={0,1.0,0};
//	trans->TransformVector(unit_v,unit_v);
//	double angle=acos(vtkMath::Dot(normal,unit_v))*RAD_2_DEG;
//	if (angle>5 || angle<-5) {
//		cout<<"transed:"<<unit_v[0]<<unit_v[1]<<unit_v[2];
//		cout<<" surface:"<<normal[0]<<normal[1]<<normal[2];
//		cout<<" thera:"<<theta<<" phi:"<<phi;
//		cout<<" angle:"<<angle<<endl;
//	}
	return 1;
}
