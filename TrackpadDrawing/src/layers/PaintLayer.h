#pragma once

#include "Layer.h"

class PaintLayer : public Layer
{
public:
	PaintLayer() = default;
	~PaintLayer() = default;

	void OnRender(Window* window) override;
};

