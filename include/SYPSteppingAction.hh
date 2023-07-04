
/// \file SYPSteppingAction.hh
/// \brief Definition of the SYPSteppingAction class

#ifndef SYPSteppingAction_h
#define SYPSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SYPEventAction;
class SYPRunAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class SYPSteppingAction : public G4UserSteppingAction
{
  public:
    SYPSteppingAction(SYPRunAction* fRunAction);
    virtual ~SYPSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    SYPRunAction* fRunAction;
    //G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
