#ifndef B4FileGenerator_h
#define B4FileGenerator_h 1
#include "G4String.hh"
#include "G4ThreeVector.hh"

class G4ParticleDefinition;

class B4FileGenerator
{

	public:
		struct B4GenParticle_t
		{
			G4ThreeVector fP;
			G4double fE;
			G4double fM;
			G4double fT;
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
};
#endif
