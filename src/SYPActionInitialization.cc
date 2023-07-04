
/// \file SYPActionInitialization.cc
/// \brief Implementation of the SYPActionInitialization class

#include "SYPActionInitialization.hh"
#include "SYPPrimaryGeneratorAction.hh"
#include "SYPRunAction.hh"
#include "SYPEventAction.hh"
#include "SYPSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SYPActionInitialization::SYPActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SYPActionInitialization::~SYPActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SYPActionInitialization::BuildForMaster() const
{
  SYPRunAction* runAction = new SYPRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SYPActionInitialization::Build() const
{
  SetUserAction(new SYPPrimaryGeneratorAction);

  SYPRunAction* runAction = new SYPRunAction;
  SetUserAction(runAction);
  
  SYPEventAction* eventAction = new SYPEventAction(runAction);
  SetUserAction(eventAction);

  SYPSteppingAction* steppingAction = new SYPSteppingAction(runAction);
  SetUserAction(steppingAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
