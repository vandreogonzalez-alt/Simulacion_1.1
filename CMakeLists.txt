cmake_minimum_required(VERSION 3.16)
project(Simulacion_1)

option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" OFF)

if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  main.cc
  DetectorConstruction.cc
  PhysicsList.cc
  PrimaryGeneratorAction.cc
)

set(HEADERS
  DetectorConstruction.hh
  PhysicsList.hh
  PrimaryGeneratorAction.hh
)

add_executable(simulacion_1 ${SOURCES} ${HEADERS})
target_link_libraries(simulacion_1 ${Geant4_LIBRARIES})
