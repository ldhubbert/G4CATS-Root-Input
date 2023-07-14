#ifndef B4FileGenerator_h1Branch_h
#define B4FileGenerator_h1Branch_h 1

#include "Rtypes.h"

#include "B4FileGeneratorTree.hh"

class B4FileGenerator_h1Branch : public B4FileGeneratorTree
{
	protected:
		Float_t fVertexBr[3];
		Float_t fBeamBr[5];
		G4int fNPart;
		Float_t** fPartPBr;
		Float_t** fPartVBr;

		static const G4int fgMaxParticles;

	public:
		B4FileGenerator_h1Branch(const char* filename);
		virtual ~B4FileGenerator_h1Branch();
		virtual G4bool Init();
		virtual G4bool ReadEvent(G4int event);
};

#endif
