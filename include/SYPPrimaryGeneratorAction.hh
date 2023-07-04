
/// \file SYPPrimaryGeneratorAction.hh
/// \brief Definition of the SYPPrimaryGeneratorAction class

#ifndef SYPPrimaryGeneratorAction_h
#define SYPPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 3 MeV gamma beam, randomly distributed
/// in front of the chamber of the (X,Y) chamber size.

class SYPPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    SYPPrimaryGeneratorAction();
    virtual ~SYPPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
