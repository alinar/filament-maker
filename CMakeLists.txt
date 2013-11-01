cmake_minimum_required (VERSION 2.6) 

PROJECT(main)
INCLUDE_DIRECTORIES("/usr/local/include/rapidxml-1.13/")
IF(APPLE)
  SET(EXECUTABLE_FLA MACOSX_BUNDLE)
ENDIF(APPLE)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
add_executable(main main.cpp strand cylinder sphere filament xml_file_interactor elemental_strand)
if(VTK_LIBRARIES)
  target_link_libraries(main ${VTK_LIBRARIES})
  message(Links to VTK_LIBRARIES)
else()
  target_link_libraries(main vtkHybrid)
  message(Links to vtkHybrid)
endif()

