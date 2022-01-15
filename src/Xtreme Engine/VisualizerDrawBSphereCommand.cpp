#include "VisualizerDrawBSphereCommand.h"
#include "Visualizer.h"
#include "VisualizerAttorney.h"
#include "VisualizerDrawBSphereCommandFactory.h"

VisualizerDrawBSphereCommand::~VisualizerDrawBSphereCommand() {

}

VisualizerDrawBSphereCommand::VisualizerDrawBSphereCommand(Matrix S, const Vect col) 
	:m(S),c(col)
{

}

void VisualizerDrawBSphereCommand::Initialize(Matrix S, const Vect col) {
	m = S;
	c = col;
}

void VisualizerDrawBSphereCommand::execute() {
	VisualizerAttorney::Draw::RenderBSphere(m, c);
	VisualizerDrawBSphereCommandFactory::RecycleVisualizerDrawBSphereCommand(this);

}

