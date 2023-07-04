
/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

#ifndef SYPDetectorConstruction_h
#define SYPDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class SYPDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SYPDetectorConstruction();
    virtual ~SYPDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    // method
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    // function member
    void DefineMaterials();
    // optionally: G4VPhysicalVolume* DefineVolumes();
    // data member
    G4LogicalVolume*  fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

