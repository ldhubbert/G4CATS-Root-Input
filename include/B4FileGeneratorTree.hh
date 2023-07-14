#ifndef B4FileGeneratorTree_h
#define B4FileGeneratorTree_h 1
#include "B4FileGenerator.hh"

class TFile;
class TTree;

class B4FileGeneratorTree : public B4FileGenerator
{
	protected:
		TFile* fFile;
		TTree* fTree;

		G4bool LinkBranch(const char* bname, void* addr, G4bool verbose = true);

	public:
		B4FileGeneratorTree(const char* filename, EFileGenType type, const char* treename);
		virtual ~B4FileGeneratorTree();
		virtual G4bool Init();
		virtual G4bool ReadEvent(G4int event);
};
#endif
