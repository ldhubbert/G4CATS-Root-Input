#include "TTree.h"
#include "B4FileGenerator_h1Branch.hh"

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4ParticleTable.hh"

using namespace CLHEP;

B4FileGenerator_h1Branch::B4FileGenerator_h1Branch(const char* filename)
:B4FileGeneratorTree(filename, h1Branch, "h1")
{
	fNPart = 0;
	//records particle momentum and energy
	fPartPBr = new Float_t*[fNEvents];
	//records particle position and time
	fPartVBr = new Float_t*[fNEvents];
	for (Int_t i = 0; i <= fNEvents; i++)
	{
		fPartPBr[i] = 0;
		fPartVBr[i] = 0;
	}

}

B4FileGenerator_h1Branch::~B4FileGenerator_h1Branch()
{
	if (fPartPBr)
	{
		for (G4int i = 0; i < fNPart; i++)
		{
			if (fPartPBr[i])
				delete [] fPartPBr[i];
			if (fPartVBr[i])
				delete [] fPartVBr[i];
		}
		delete [] fPartPBr;
		delete [] fPartVBr;
	}
}

G4bool B4FileGenerator_h1Branch::Init()
{
	LinkBranch("X_vtx", &fVertexBr[0]);
	LinkBranch("Y_vtx", &fVertexBr[1]);
	LinkBranch("Z_vtx", &fVertexBr[2]);

	LinkBranch("Px_bm", &fBeamBr[0]);
	LinkBranch("Py_bm", &fBeamBr[1]);
	LinkBranch("Pz_bm", &fBeamBr[2]);
	LinkBranch("Pt_bm", &fBeamBr[4]);
	LinkBranch("En_bm", &fBeamBr[3]);

	G4int nbr = fTree->GetNbranches();

	fNPart = 0;
	TString prefix;
	TObjArray* objarray = fTree->GetListOfBranches();
	for (G4int i = 0; i <= fNEvents; i++)
	{
		prefix.Form("Px_l%02d", i+1);

		for (G4int j = 0; j <= nbr; j++)
		{
			TBranch* branch = (TBranch*)objarray->At(j);
			TString bname = TString(branch->GetName());

			if (bname.BeginsWith(prefix))
			{
				TString g3_id_str(bname);
				g3_id_str.ReplaceAll(prefix, "");
				G4int g3_id = g3_id_str.Atoi();

				fPartPBr[fNPart] = new Float_t[5];

				LinkBranch(TString::Format("Px_l%02d%02d", i+1, g3_id).Data(), &fPartPBr[fNPart][0]);
				LinkBranch(TString::Format("Py_l%02d%02d", i+1, g3_id).Data(), &fPartPBr[fNPart][1]);
				LinkBranch(TString::Format("Pz_l%02d%02d", i+1, g3_id).Data(), &fPartPBr[fNPart][2]);
				LinkBranch(TString::Format("Pt_l%02d%02d", i+1, g3_id).Data(), &fPartPBr[fNPart][4]);
				LinkBranch(TString::Format("En_l%02d%02d", i+1, g3_id).Data(), &fPartPBr[fNPart][3]);

				if (fTree->GetBranch(TString::Format("Vx_l%02d%02d", i+1, g3_id).Data()))
				{
					fPartVBr[fNPart] = new Float_t[4];
					LinkBranch(TString::Format("Vx_l%02d%02d", i+1, g3_id).Data(), &fPartVBr[fNPart][0], false);
					LinkBranch(TString::Format("Vy_l%02d%02d", i+1, g3_id).Data(), &fPartVBr[fNPart][1], false);
					LinkBranch(TString::Format("Vz_l%02d%02d", i+1, g3_id).Data(), &fPartVBr[fNPart][2], false);
					LinkBranch(TString::Format("Vt_l%02d%02d", i+1, g3_id).Data(), &fPartVBr[fNPart][3], false);
				}
			}
		}
	}

	return true;
}

G4bool B4FileGenerator_h1Branch::ReadEvent(G4int event)
{
	if (!B4FileGeneratorTree::ReadEvent(event))
		return false;

	fVertex.set(fVertexBr[0]*cm, fVertexBr[1]*cm, fVertexBr[2]*cm);
	fBeam.fP.set(fBeamBr[0]*fBeamBr[4]*MeV, fBeamBr[1]*fBeamBr[4]*MeV, fBeamBr[2]*fBeamBr[4]*MeV);
	fBeam.fE = fBeamBr[3]*MeV;

	for (G4int i = 0; i < fNPart; i++)
	{
		fPart[i].fP.set(fPartPBr[i][0]*fPartPBr[i][4]*MeV, fPartPBr[i][1]*fPartPBr[i][4]*MeV, fPartPBr[i][2]*fPartPBr[i][4]*MeV);
		fPart[i].fE = fPartPBr[i][3]*MeV;

	fPart[i].fX.set(fPartVBr[i][0]*cm, fPartVBr[i][1]*cm, fPartVBr[i][2]*cm);
	fPart[i].fT = fPartVBr[i][3]*ns;
	}

	return true;
}
