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



int main(int, char *argv[])
{
	Filament filament;

	filament.PlaceElements();
	cout<< filament.cylinders.size()<<endl;

	filament.Show();

	return EXIT_SUCCESS;
}


