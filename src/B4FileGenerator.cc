#include "B4FileGenerator.hh"
#include "G4ParticleDefinition.hh"

B4FileGenerator::B4FileGenerator(const char* filename, EFileGenType type)
{
	fType = type;
	fFileName = filename;
	fNEvents = 0;
}

void B4FileGenerator::SetParticleIsTrack(G4int p, G4bool t)
{
	if (t && !fPart[p].fDef)
		return;

	fPart[p].fIsTrack = t;
}
