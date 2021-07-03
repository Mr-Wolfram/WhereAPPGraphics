#pragma once

#include <string>
#include <vector>

#include "../base/application.hpp"
#include "bunny.h"
#include "Block.hpp"

class Transformation : public Application {
public:
	Transformation();

	~Transformation() = default;
    
    void setup(const char* cfilepath);

	void renderFrame() override;

private:
	std::vector<Bunny> _bunnies;
    std::vector<Block> _blocks;

	glm::vec3 _positions[3] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(10.0f, 0.0f, 0.0f)
	};

	glm::vec3 _rotateAxis[3] = {
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	float _rotateAngles[3] = {
        1.0f, 0.0f, 0.0f
	};

	glm::vec3 _scales[3] = {
		glm::vec3(1.5f, 1.5f, 1.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};
};
