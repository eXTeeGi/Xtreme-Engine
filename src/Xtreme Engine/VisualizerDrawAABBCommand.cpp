#include "VisualizerDrawAABBCommand.h"
#include "Visualizer.h"
#include "VisualizerAttorney.h"
#include "VisualizerDrawAABBCommandFactory.h"

VisualizerDrawAABBCommand::~VisualizerDrawAABBCommand() {

}

VisualizerDrawAABBCommand::VisualizerDrawAABBCommand(Matrix S, const Vect col)
	:m(S), c(col)
{

}

void VisualizerDrawAABBCommand::Initialize(Matrix S, const Vect col) {
	m = S;
	c = col;
}

void VisualizerDrawAABBCommand::execute() {
	VisualizerAttorney::Draw::RenderAABB(m, c);
	VisualizerDrawAABBCommandFactory::RecycleVisualizerDrawAABBCommand(this);
}

