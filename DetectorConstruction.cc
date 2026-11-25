#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  // 1. Material del mundo (aire a condiciones estándar)
  G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // 2. Composición aproximada de acero inoxidable 316L (fracciones de masa)
  // Fe ~68%, Cr ~17%, Ni ~12%, Mo ~2.5%, Mn ~0.5% (densidad ~8.0 g/cm3)
  G4Element* elFe = nist->FindOrBuildElement("Fe");
  G4Element* elCr = nist->FindOrBuildElement("Cr");
  G4Element* elNi = nist->FindOrBuildElement("Ni");
  G4Element* elMo = nist->FindOrBuildElement("Mo");
  G4Element* elMn = nist->FindOrBuildElement("Mn");

  G4double density = 8.0 * g / cm3;
  G4Material* ss316l = new G4Material("SS316L", density, 5);
  ss316l->AddElement(elFe, 0.680);
  ss316l->AddElement(elCr, 0.170);
  ss316l->AddElement(elNi, 0.120);
  ss316l->AddElement(elMo, 0.025);
  ss316l->AddElement(elMn, 0.005);

  // 3. Volumen del mundo (semidimensiones: 50 cm x 50 cm x 50 cm)
  G4double worldSizeXY = 50. * cm;
  G4double worldSizeZ  = 50. * cm;

  G4Box* solidWorld = new G4Box("World", worldSizeXY, worldSizeXY, worldSizeZ);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(
      nullptr,                  // sin rotación
      G4ThreeVector(),          // posición (0, 0, 0)
      logicWorld,               // volumen lógico
      "World",                  // nombre
      nullptr,                  // sin volumen madre
      false,                    // no booleano
      0,                        // número de copia
      true);                    // comprobar solapamientos

  // 4. Blindaje de SS316L (ejemplo: lámina de 1.0 mm de espesor total en Z)
  G4double shieldSizeXY = 20. * cm;
  G4double shieldThickness = 1.0 * mm;

  G4Box* solidShield = new G4Box(
      "Shield",
      shieldSizeXY,
      shieldSizeXY,
      0.5 * shieldThickness);   // G4Box recibe la semidimensión en cada eje

  G4LogicalVolume* logicShield = new G4LogicalVolume(solidShield, ss316l, "Shield");

  new G4PVPlacement(
      nullptr,
      G4ThreeVector(0., 0., 0.),
      logicShield,
      "Shield",
      logicWorld,
      false,
      0,
      true);

  return physWorld;
}