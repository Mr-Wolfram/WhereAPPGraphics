#pragma once

#include "../base/application.h"
#include "flag.h"
#include "star.h"

class RenderFlag : public Application {
public:
	RenderFlag();

	~RenderFlag();

private:
	Flag* _flag = nullptr;
	Star* _stars[5] = { nullptr };
	
	void handleInput() override;

	void renderFrame() override;
};