#ifndef _VisualizerDrawBSphereCommand
#define _VisualizerDrawBSphereCommand

#include "AzulCore.h"
#include "VisualizerCommandBase.h"

class VisualizerDrawBSphereCommand : public VisualizerCommandBase
{
public:
	VisualizerDrawBSphereCommand() = default;
	~VisualizerDrawBSphereCommand();
	VisualizerDrawBSphereCommand(Matrix S, const Vect col);
	VisualizerDrawBSphereCommand(const VisualizerDrawBSphereCommand&) = default;

	void Initialize(Matrix S, const Vect col);
	void execute();
private:
	Matrix m;
	Vect c;
};

#endif _VisualizerDrawBSphereCommand