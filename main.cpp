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

int ColorLookup()
{
  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();

  lookupTable->SetTableRange(0.0, 10.0);
  // If you don't want to use the whole color range, you can use
  // SetValueRange, SetHueRange, and SetSaturationRange
  lookupTable->Build();

  double color[3];
  lookupTable->GetColor(1.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;

  lookupTable->GetColor(5.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;

  return EXIT_SUCCESS;
}

int main(int, char *argv[])
{
	Filament filament;

	filament.PlaceElements();
	cout<< filament.cylinders.size()<<endl;

	filament.Show();

	return EXIT_SUCCESS;
}


