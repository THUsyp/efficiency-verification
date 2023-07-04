
/// \file SYPSteppingAction.cc
/// \brief Implementation of the SYPSteppingAction class

#include "SYPSteppingAction.hh"
#include "SYPEventAction.hh"
#include "SYPRunAction.hh"
#include "SYPDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "math.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SYPSteppingAction::SYPSteppingAction(SYPRunAction* fRunAction)
: G4UserSteppingAction(),
  fRunAction(fRunAction)
  //ScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SYPSteppingAction::~SYPSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SYPSteppingAction::UserSteppingAction(const G4Step* step) {

    G4TouchableHandle touchableHandle = step->GetPreStepPoint()->GetTouchableHandle();
    G4LogicalVolume* volume = touchableHandle->GetVolume()->GetLogicalVolume();
    G4String volumeName = volume->GetName();
    G4Track* track = step->GetTrack();
    G4int trackID = track->GetTrackID();
    G4String createProcess = track->GetCreatorModelName();
    G4String particleName = track->GetParticleDefinition()->GetParticleName();
    G4String postProcessName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

    // count the secondary in chamber

    if (volumeName=="gas")
    {
        if(trackID==1&&postProcessName=="Rayl"||postProcessName=="phot"||postProcessName=="conv"||postProcessName=="compt")
        {
            fRunAction->count++;
        }
        if(particleName=="e-")
        {
            track->SetTrackStatus(fKillTrackAndSecondaries);
        }
        if(particleName=="gamma"&&createProcess=="eBrem")
        {
            track->SetTrackStatus(fKillTrackAndSecondaries);
        }
    }

}