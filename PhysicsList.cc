#include "PhysicsList.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
  : G4VModularPhysicsList()
{
  // Verbosidad general de la lista física
  SetVerboseLevel(1);

  // Modelo electromagnético de baja energía (adecuado para fotones/electrones de 0-30 keV)
  RegisterPhysics(new G4EmLivermorePhysics());
}