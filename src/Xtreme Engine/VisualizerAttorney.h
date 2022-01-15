#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"
#include "AzulCore.h"

class VisualizerAttorney
{

public:
	class Draw
	{
		friend class VisualizerDrawBSphereCommand;
		friend class VisualizerDrawAABBCommand;
		friend class VisualizerDrawOBBCommand;
		friend class XtremeEngine;
		friend class DrawableManager;
	private:
		static void RenderBSphere(Matrix& S, const Vect& col) { Visualizer::Instance().privRenderBSphere(S, col); }
		static void RenderAABB(Matrix& S, const Vect& col) { Visualizer::Instance().privRenderAABB(S, col); }
		static void RenderOBB(Matrix& S, const Vect& col) { Visualizer::Instance().privRenderOBB(S,col); }
		static void VisualizeAll() { Visualizer::Instance().VisualizeAll(); }
	};
public:
	class Delete
	{
		friend class XtremeEngine;
	private:
		static void Terminate() { Visualizer::Delete(); }
	};
};


#endif _VisualizerAttorney