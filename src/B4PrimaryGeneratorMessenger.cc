#include "B4PrimaryGeneratorMessenger.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

B4PrimaryGeneratorMessenger::B4PrimaryGeneratorMessenger(B4PrimaryGeneratorAction* par)
:test(par)
{
	variable = new G4UIdirectory("/G4CATS/generator/");
	variable->SetGuidance("PrimaryGenerator control");
	SetInputCmd = new G4UIcmdWithAString("/G4CATS/generator/InputFile",this);
	SetInputCmd->SetGuidance("Set the file the with the input ROOT file");
	SetInputCmd->SetParameterName("inputfile",false);
}

B4PrimaryGeneratorMessenger::~B4PrimaryGeneratorMessenger()
{
	delete variable;
	delete SetInputCmd;
}


void B4PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if(command == SetInputCmd)
	{
		test->SetInputFile(static_cast<TString>(newValue));
	}
}
