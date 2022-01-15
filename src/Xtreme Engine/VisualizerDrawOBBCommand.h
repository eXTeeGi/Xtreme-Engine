#ifndef _VisualizerDrawOBBCommand
#define _VisualizerDrawOBBCommand

#include "AzulCore.h"
#include "VisualizerCommandBase.h"

class VisualizerDrawOBBCommand : public VisualizerCommandBase
{
public:
	VisualizerDrawOBBCommand() = default;
	~VisualizerDrawOBBCommand();
	VisualizerDrawOBBCommand(Matrix S, const Vect col);
	VisualizerDrawOBBCommand(const VisualizerDrawOBBCommand&) = default;

	void Initialize(Matrix S, const Vect col);
	void execute();
private:
	Matrix m;
	Vect c;
};

#endif _VisualizerDrawOBBCommand