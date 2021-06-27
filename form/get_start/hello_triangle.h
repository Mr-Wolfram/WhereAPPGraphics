#pragma once

#include "../base/application.h"
#include "../base/shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
};

class HelloTriangle : public Application {
public:
	HelloTriangle();

	~HelloTriangle();


private:
	GLuint _vao = 0;

	GLuint _vbo = 0;

	Vertex _vertices[3] = {
		{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f) },
		{ glm::vec3(0.0f,  0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f) }
	};

	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 color;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"	color = aColor;\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec3 color;\n"
		"out vec4 outColor;\n"
		"void main() {\n"
		"	outColor = vec4(color, 1.0f);\n"
		"}\n";

	Shader _shader{ vsCode, fsCode };

	virtual void handleInput();

	virtual void renderFrame();

};
