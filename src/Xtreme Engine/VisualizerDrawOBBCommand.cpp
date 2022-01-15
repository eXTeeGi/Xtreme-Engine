#include "VisualizerDrawOBBCommand.h"
#include "Visualizer.h"
#include "VisualizerAttorney.h"
#include "VisualizerDrawOBBCommandFactory.h"

VisualizerDrawOBBCommand::~VisualizerDrawOBBCommand() {

}

VisualizerDrawOBBCommand::VisualizerDrawOBBCommand(Matrix S, const Vect col)
	:m(S), c(col)
{

}

void VisualizerDrawOBBCommand::Initialize(Matrix S, const Vect col) {
	m = S;
	c = col;
}

void VisualizerDrawOBBCommand::execute() {
	VisualizerAttorney::Draw::RenderOBB(m, c);
	VisualizerDrawOBBCommandFactory::RecycleVisualizerDrawOBBCommand(this);
}

