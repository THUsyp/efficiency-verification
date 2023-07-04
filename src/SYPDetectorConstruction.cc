
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include <G4GenericTrap.hh>
#include <G4Tubs.hh>
#include "SYPDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "CADMesh.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SYPDetectorConstruction::SYPDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SYPDetectorConstruction::~SYPDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* SYPDetectorConstruction::Construct()
{
  // Material definition
  G4NistManager* nistManager = G4NistManager::Instance();

  // Air definition using NIST Manager
  nistManager->FindOrBuildMaterial("G4_AIR");

  // Parameter
  G4double  z, a, fractionmass, density;
  G4String name, symbol;
  G4int ncomponents;

  // 95WNiFe
  G4Element* elW  = new G4Element
          (name="Tungsten", symbol = "W", z= 74., a=183.84*g/mole);
  G4Element* elNi = new G4Element
          (name="Nickle",symbol="Ni",z=28.,a=58.69*g/mole);
  G4Element* elFe = new G4Element
          (name="Ferrum",symbol="Fe",z=26.,a=55.845*g/mole);
  density = 18.75*g/cm3;
  G4Material* W95NiFe = new G4Material
          (name="95WNiFe",density,ncomponents=3);
  W95NiFe->AddElement(elW, fractionmass=95*perCent);
  W95NiFe->AddElement(elNi,fractionmass=2.5*perCent);
  W95NiFe->AddElement(elFe,fractionmass=2.5*perCent);

  // Stainless Steel
  G4Element* elCr = new G4Element
          (name="chromium",symbol="Cr",z=24,a=51.996*g/mole);
  G4Element* elMn = new G4Element
          (name="Manganese",symbol="Mn",z=25,a=54.938*g/mole);
  density = 7.93*g/cm3;
  G4Material* SS = new G4Material
          (name="StainlessSteel",density,ncomponents=4);
  SS->AddElement(elFe,fractionmass=68*perCent);
  SS->AddElement(elCr,fractionmass=20*perCent);
  SS->AddElement(elNi,fractionmass=10*perCent);
  SS->AddElement(elMn,fractionmass= 2*perCent);

  // Xe-48atm
  new G4Material("Xe_48atm", z=54., a=131.2*g/mole,density= 0.3723*g/cm3,
                 kStateGas, 2.93*kelvin, 48*atmosphere);

  // Ar-1atm
  new G4Material("1atmAr",z=18,a=39.948*g/mole,density=0.00178*g/cm3,kStateGas,2.93*kelvin,
                 1*atmosphere);

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // Parameter

  G4double world_sizeX = 10*m; G4double world_sizeY = 10*m; G4double world_sizeZ = 10*m;
  //
  G4Material* world_mat = nistManager->FindOrBuildMaterial("G4_AIR");
  G4Material* det_mat = nistManager->FindOrBuildMaterial("StainlessSteel");


  //
  // World
  //

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Using this model to illustrate the difference between
  // detection efficiency and beer's law
  //

  //
  // Detector
  //

  G4Tubs * solid_Detector =
          new G4Tubs ( "Detector", 10*cm, 11*cm,
                       25*cm, 0, 2*CLHEP::pi);

  G4LogicalVolume* logic_Detector =
          new G4LogicalVolume( solid_Detector, det_mat, "Detector");

  G4ThreeVector det_pos = G4ThreeVector (0,0,-25*cm);
  G4VPhysicalVolume* phys_Detector =
          new G4PVPlacement (
                  0,
                  det_pos,
                  logic_Detector,
                  "Detector",
                  logicWorld,
                  false,
                  0,
                  checkOverlaps
                  );

  //
  // Chamber gas
  //

  G4Tubs * solid_gas = new G4Tubs( "gas", 0, 10*cm, 25*cm, 0, 2*CLHEP::pi);

  G4Material* gas_mat = nistManager->FindOrBuildMaterial("1atmAr");
  G4LogicalVolume* logic_gas = new G4LogicalVolume(
          solid_gas, gas_mat, "gas"
          );

  G4ThreeVector gas_pos = det_pos;
  G4VPhysicalVolume* phys_gas =
          new G4PVPlacement (
                  0,
                  gas_pos,
                  logic_gas,
                  "gas",
                  logicWorld,
                  false,
                  0,
                  checkOverlaps
                  );


  // Set working gas as scoring volume
  //
  fScoringVolume = logic_Detector;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
