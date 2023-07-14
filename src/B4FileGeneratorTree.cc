#include "B4FileGeneratorTree.hh"
#include "TFile.h"
#include "TTree.h"

B4FileGeneratorTree::B4FileGeneratorTree(const char* filename, EFileGenType type, const char* treename)
:B4FileGenerator(filename, type)
{
	fFile = 0;
	fTree = 0;
	fFile = new TFile(fFileName.c_str());
	fTree = (TTree*)fFile->Get(treename);
}

B4FileGeneratorTree::~B4FileGeneratorTree()
{
	delete fTree;
	delete fFile;
}

G4bool B4FileGeneratorTree::Init()
{
	fNEvents = fTree->GetEntries();
	return true;
}

G4bool B4FileGeneratorTree::ReadEvent(G4int event)
{
	fTree->GetEntry(event);
	return true;
}

G4bool B4FileGeneratorTree::LinkBranch(const char* bname, void* addr, G4bool /*verbose*/)
{
	TBranch* b = fTree->GetBranch(bname);
	if (b)
	{
		b->SetAddress(addr);
		return true;
	}
	else
	{
		return false;
	}
}

