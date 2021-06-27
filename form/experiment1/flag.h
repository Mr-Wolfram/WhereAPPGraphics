#pragma once

#include <glm/glm.hpp>
#include "../base/shader.h"

class Flag {
public:
	Flag();

	~Flag();

	void render();

private:
	const glm::vec2 _vertices[6] = {
		glm::vec2(-0.5f, -0.5f),
		glm::vec2( 0.5f, -0.5f),
		glm::vec2( 0.5f,  0.5f),
		glm::vec2( 0.5f,  0.5f),
		glm::vec2(-0.5f,  0.5f),
		glm::vec2(-0.5f, -0.5f)
	};

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
		"	fragColor = vec4(0.93f, 0.15f, 0.14f, 1.0f);\n"
		"}\n";

	Shader _shader = { _vsCode, _fsCode };

	GLuint _vao = 0;

	GLuint _vbo = 0;
};