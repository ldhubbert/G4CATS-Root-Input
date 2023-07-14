#ifndef B4Messenger_h
#define B4Messenger_h 1

#include "G4UImessenger.hh"

class B4PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class B4PrimaryGeneratorMessenger: public G4UImessenger
{
	public:
		B4PrimaryGeneratorMessenger(B4PrimaryGeneratorAction*);
		~B4PrimaryGeneratorMessenger();

		void SetNewValue(G4UIcommand*, G4String);

	private:
		B4PrimaryGeneratorAction* test;
		G4UIdirectory* variable;

	G4UIcmdWithAString* SetInputCmd;

};

#endif
