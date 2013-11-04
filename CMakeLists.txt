cmake_minimum_required (VERSION 2.6) 

PROJECT(main)


include_directories("${PROJECT_SOURCE_DIR}" "/usr/local/include/rapidxml-1.13/")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
add_executable(main main.cpp xml_file_interactor cylinder strand elemental_strand)
if(VTK_LIBRARIES)
  target_link_libraries(main ${VTK_LIBRARIES})
  message("Links to VTK_LIBRARIES")
else()
  target_link_libraries(main vtkHybrid)
  message("Links to vtkHybrid")
endif()

