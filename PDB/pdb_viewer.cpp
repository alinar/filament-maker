/*
 * pdb_viewer.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: alinar
 */

#include "pdb_viewer.h"

#include <vtkSmartPointer.h>
#include <cmath>
#include <vtkGlyph3D.h>
#include <vtkLODActor.h>
#include <vtkLODActor.h>
#include <vtkPDBReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTubeFilter.h>

PDBViewer::PDBViewer() {
	// TODO Auto-generated constructor stub

}

PDBViewer::~PDBViewer() {
	// TODO Auto-generated destructor stub
}

void PDBViewer::OpenAndView(char *pdb_file){

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.1, .2, .3);
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(300, 300);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPDBReader> pdb =
    vtkSmartPointer<vtkPDBReader>::New();
  pdb->SetFileName(pdb_file);
  pdb->SetHBScale(1.0);
  pdb->SetBScale(1.0);
  pdb->Update();
  std::cout <<"# of atoms is: " << pdb->GetNumberOfAtoms() << std::endl;

  double resolution = std::sqrt(300000.0 / pdb->GetNumberOfAtoms());
  if (resolution > 20)
    {
    resolution = 20;
    }
  if (resolution < 4)
    {
    resolution = 4;
    }
  std::cout <<"Resolution is: " << resolution << std::endl;
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetCenter(0, 0, 0);
  sphere->SetRadius(1);
  sphere->SetThetaResolution(static_cast<int>(resolution));
  sphere->SetPhiResolution(static_cast<int>(resolution));

  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(pdb->GetOutputPort());
  glyph->SetOrient(1);
  glyph->SetColorMode(1);
  // glyph->ScalingOn();
  glyph->SetScaleMode(2);
  glyph->SetScaleFactor(.25);
  glyph->SetSourceConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> atomMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  atomMapper->SetInputConnection(glyph->GetOutputPort());
  atomMapper->ImmediateModeRenderingOn();
  atomMapper->UseLookupTableScalarRangeOff();
  atomMapper->ScalarVisibilityOn();
  atomMapper->SetScalarModeToDefault();

  vtkSmartPointer<vtkLODActor> atom =
    vtkSmartPointer<vtkLODActor>::New();
  atom->SetMapper(atomMapper);
  atom->GetProperty()->SetRepresentationToSurface();
  atom->GetProperty()->SetInterpolationToGouraud();
  atom->GetProperty()->SetAmbient(0.15);
  atom->GetProperty()->SetDiffuse(0.85);
  atom->GetProperty()->SetSpecular(0.1);
  atom->GetProperty()->SetSpecularPower(30);
  atom->GetProperty()->SetSpecularColor(1, 1, 1);
  atom->SetNumberOfCloudPoints(30000);

  renderer->AddActor(atom);

  vtkSmartPointer<vtkTubeFilter> tube =
    vtkSmartPointer<vtkTubeFilter>::New();
  tube->SetInputConnection(pdb->GetOutputPort());
  tube->SetNumberOfSides(static_cast<int>(resolution));
  tube->CappingOff();
  tube->SetRadius(0.2);
  tube->SetVaryRadius(0);
  tube->SetRadiusFactor(10);

  vtkSmartPointer<vtkPolyDataMapper> bondMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  bondMapper->SetInputConnection(tube->GetOutputPort());
  bondMapper->ImmediateModeRenderingOn();
  bondMapper->UseLookupTableScalarRangeOff();
  bondMapper->ScalarVisibilityOff();
  bondMapper->SetScalarModeToDefault();

  vtkSmartPointer<vtkLODActor> bond =
    vtkSmartPointer<vtkLODActor>::New();
  bond->SetMapper(bondMapper);
  bond->GetProperty()->SetRepresentationToSurface();
  bond->GetProperty()->SetInterpolationToGouraud();
  bond->GetProperty()->SetAmbient(0.15);
  bond->GetProperty()->SetDiffuse(0.85);
  bond->GetProperty()->SetSpecular(0.1);
  bond->GetProperty()->SetSpecularPower(30);
  bond->GetProperty()->SetSpecularColor(1, 1, 1);
  bond->GetProperty()->SetDiffuseColor(1.0000, 0.8941, 0.70981);

  renderer->AddActor(bond);

  interactor->Initialize();
  interactor->Start();

}

