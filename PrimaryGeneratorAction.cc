#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction()
{
  G4int nParticles = 1;
  fParticleGun = new G4ParticleGun(nParticles);

  // Partícula primaria: fotón de rayos X
  fParticleGun->SetParticleDefinition(G4Gamma::Definition());

  // Posición inicial (delante del blindaje, asumiendo el blanco centrado en z = 0)
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -10. * cm));

  // Dirección de incidencia hacia el blindaje (+Z)
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

  // Energía por defecto
  fParticleGun->SetParticleEnergy(15. * keV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Energía aleatoria uniforme en [0.1, 30.0] keV
  G4double eMin = 0.1 * keV;
  G4double eMax = 30.0 * keV;
  G4double energy = eMin + G4UniformRand() * (eMax - eMin);

  fParticleGun->SetParticleEnergy(energy);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}