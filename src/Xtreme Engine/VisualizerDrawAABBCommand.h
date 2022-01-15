#ifndef _VisualizerDrawAABBCommand
#define _VisualizerDrawAABBCommand

#include "AzulCore.h"
#include "VisualizerCommandBase.h"

class VisualizerDrawAABBCommand : public VisualizerCommandBase
{
public:
	VisualizerDrawAABBCommand() = default;
	~VisualizerDrawAABBCommand();
	VisualizerDrawAABBCommand(Matrix S, const Vect col);
	VisualizerDrawAABBCommand(const VisualizerDrawAABBCommand&) = default;

	void Initialize(Matrix S, const Vect col);
	void execute();
private:
	Matrix m;
	Vect c;
};

#endif _VisualizerDrawAABBCommand