#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "B4cDetectorConstruction.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4RunAction.hh"
#include "B4cEventAction.hh"

void G4CATS()
{
	G4String nameFileInput;
	G4UImanager* UI = G4UImanager::GetUIpointer();

	if (!nameFileInput.empty())
	{
		UI->ApplyCommand("/A2/generator/InputFile " + nameFileInput);
	}
}
