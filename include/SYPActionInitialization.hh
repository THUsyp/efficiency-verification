
/// \file SYPActionInitialization.hh
/// \brief Definition of the SYPActionInitialization class

#ifndef SYPActionInitialization_h
#define SYPActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class SYPActionInitialization : public G4VUserActionInitialization
{
  public:
    SYPActionInitialization();
    virtual ~SYPActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
