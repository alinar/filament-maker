/*
 * pdb_viewer.h
 *
 *  Created on: Nov 11, 2013
 *      Author: alinar
 */

#ifndef PDB_VIEWER_H_
#define PDB_VIEWER_H_

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

class PDBViewer {
public:
	PDBViewer();
	virtual ~PDBViewer();
	static void OpenAndView(char*);

};
#endif /* PDB_VIEWER_H_ */
