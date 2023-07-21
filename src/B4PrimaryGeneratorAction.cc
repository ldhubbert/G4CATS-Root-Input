//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 
/// \file B4PrimaryGeneratorAction.cc
/// \brief Implementation of the B4PrimaryGeneratorAction class

#include "B4PrimaryGeneratorMessenger.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4FileGenerator_h1Branch.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "TLorentzVector.h"
#include "TFile.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using namespace CLHEP;

B4PrimaryGeneratorAction::B4PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  auto particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(500.*MeV);

  fGunMessenger = new B4PrimaryGeneratorMessenger(this);
  fFileGen = 0;
  fNevent=0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction::~B4PrimaryGeneratorAction()
{
  if (fFileGen)
	  delete fFileGen;
  delete fParticleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume 
  // from G4LogicalVolumeStore
  //
/*  G4double worldZHalfLength = 0.;//was 0
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
  G4Box* worldBox = nullptr;
  if (  worldLV ) {
    worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  }

  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
      "MyCode0002", JustWarning, msg);
  } 
*/  
  // Set gun position
  //fParticleGun->SetParticlePosition(G4ThreeVector(4*cm, 0., -worldZHalfLength));//-worldZHalfLength
  fParticleGun->SetParticlePosition(G4ThreeVector(0*cm, 0., 0.));
  fParticleGun->GeneratePrimaryVertex(anEvent);

  fFileGen->ReadEvent(fNevent);

  for (G4int i = 0; i < fFileGen->GetNParticles(); i++)
  {
  	TString fmt = TString::Format("Particle %2d : ", i+1);
	if (fFileGen->GetParticleDefinition(i))
	{
  		fmt += TString::Format("%-12s PDG ID: %d", fFileGen->GetParticleDefinition(i)->GetParticleName().c_str(), fFileGen->GetParticleDefinition(i)->GetPDGEncoding());
	}
  }
  
  if (fNToBeTracked

  }

  fGenPosition[0] = fFileGen->GetVertex().x()/cm;
  fGenPosition[1] = fFileGen->GetVertex().y()/cm;
  fGenPosition[2] = fFileGen->GetVertex().z()/cm;

  const B4FileGenerator::B4GenParticle_t& beam = fFileGen->GetBeam();
  if (fBeamEnergy != 0)
	  fBeamLorentzVec->SetPxPyPzE(0, 0, fBeamEnergy, fBeamEnergy);
  else
	  fBeamLorentzVec->SetPxPyPzE(beam.fP.x(), beam.fP.y(), beam.fP.z(), beam.fE);

  fNGenParticles = fFileGen->GetNParticles();
  for (G4int i = 0; i < fFileGen->GetNParticles(); i++)
  {
  	const G4ThreeVector& mom = fFileGen->GetParticleMomentum(i);
	fGenLorentzVec[i]->SetPxPyPzE(mom.x(), mom.y(), mom.z(), fFileGen->GetParticleEnergy(i));
	fGenPartType[i] = fFileGen->GetparticleDefinition(i) ?
		PDGtoG3(fFileGen->GetParticleDefinition(i)->GetPDGEncoding()) : 0;
  }

  for (G4int i = 0, i < fFileGen->GetNParticles(); i++)
  {
  	if (fFileGen->IsParticleTrack(i))
	{
  		fParticleGun->SetParticleDefinition(fFileGen->GetParticleDefinition(i));
		fParticleGun->SetParticleMomentumDirection(fFileGen->GetParticleDefinition(i));
		fParticleGun->SetParticleEnergy(fFileGen->GetParticleKineticEnergy(i));
		fParticleGun->SetParticlePosition(fFileGen->GetParticleVertex(i));
		fParticleGun->SetParticleTime(fFileGen->GetParticleTime(i));
		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
  }
  
}

void B4PrimaryGeneratorAction::SetUpFileInput()
{
	TFile* ftest = new TFile(fInFileName);
	TTree* h1Branch = 0;
	h1Branch = (TTree*)ftest->Get("h1");
	fFileGen = new B4FileGenerator_h1Branch(fInFileName);
	fFileGen->Init();
}

G4int B4PrimaryGeneratorAction::GetNEvents()
{
	if (fFileGen)
		return fFileGen->GetNEvents();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

