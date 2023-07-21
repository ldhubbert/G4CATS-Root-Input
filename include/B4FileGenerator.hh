#ifndef B4FileGenerator_h
#define B4FileGenerator_h 1
#include "G4String.hh"
#include "G4ThreeVector.hh"
#include <vector>

class G4ParticleDefinition;

class B4FileGenerator
{

	public:
		struct B4GenParticle_t
		{
			G4ParticleDefinition* fDef;
			G4ThreeVector fP;
			G4double fE;
			G4double fM;
			G4ThreeVector fX;
			G4double fT;
			G4bool fIsTrack;
		};
		enum EFileGenType
		{
			h1Branch
		};

	protected:
		EFileGenType fType;
		G4String fFileName;
		G4int fNEvents;
		B4GenParticle_t fBeam;
		G4ThreeVector fVertex;
		std::vector<B4GenParticle_t> fPart;

	public:
		B4FileGenerator(const char* filename, EFileGenType type);
		virtual ~B4FileGenerator() { }

		virtual G4bool Init() = 0;
		virtual G4bool ReadEvent(G4int event) = 0;

		EFileGenType GetType() const { return fType; }
		const G4String& GetFileName() const { return fFileName; }
		G4int GetNEvents() const { return fNEvents; }
		const G4ThreeVector& GetVertex() const { return fVertex; }
		const B4GenParticle_t& GeatBeam() const { return fBeam; }

		G4int GetNParticles() const { return fPart.size(); }
		const B4GenParticle_t& GetParticle(G4int p) const { return fPart[p]; }
		G4ParticleDefinition* GetParticleDefinition(G4int p) const { return fPart[p].fDef; }
		const G4ThreeVector& GetParticleMomentum(G4int p) const { return fPart[p].fP; }
		G4ThreeVector GetParticleDirection(G4int p) const { return G4ThreeVector(fPart[p].fP).unit(); }
		G4double GetParticleEnergy(G4int p) const {return fPart[p].fE; }
		G4double GetParticleKineticEnergy(G4int p) const { return fPart[p].fE - fPart[p].fM; }
		const G4ThreeVector& GetParticleVertex(G4int p) const { return fPart[p].fX; }
		G4double GetParticleTime(G4int p) const { return fPart[p].fT; }
		G4bool IsParticleTrack(G4int p) const { return fPart[p].fIsTrack; }

		void SetParticleIsTrack(G4int p, G4bool t = true);

		
};
#endif
