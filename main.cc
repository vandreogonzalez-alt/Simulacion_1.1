#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"

int main()
{
  // Forzar modo secuencial al registrar PrimaryGeneratorAction directamente sin ActionInitialization
  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserAction(new PrimaryGeneratorAction());

  runManager->Initialize();

  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);

  delete runManager;
  return 0;
}