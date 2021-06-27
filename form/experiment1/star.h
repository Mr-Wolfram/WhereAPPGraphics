#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include "../base/shader.h"

class Star {
public:
	Star(const glm::vec2& position, float rotation, float radius, float aspect);

	~Star();

	void render();

private:
	glm::vec2 _position;
	float _rotation;
	float _radius;

	// you are free to change the size of the vertices
	// but make sure that the size matches the number of vertices you use
	glm::vec2 _vertices[30];

	const char* _vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec2 aPosition;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPosition, 0.0f, 1.0f);\n"
		"}\n";

	const char* _fsCode =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"	fragColor = vec4(1.0f, 0.988f, 0.008f, 1.0f);\n"
		"}\n";

	Shader _shader = { _vsCode, _fsCode };

	GLuint _vao = 0;

	GLuint _vbo = 0;
};