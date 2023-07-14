#include "B4FileGenerator.hh"

B4FileGenerator::B4FileGenerator(const char* filename, EFileGenType type)
{
	fType = type;
	fFileName = filename;
	fNEvents = 0;
}

