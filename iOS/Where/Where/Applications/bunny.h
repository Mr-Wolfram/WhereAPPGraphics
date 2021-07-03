#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../base/vertex.h"
#include "../base/shader.h"

class Bunny {
public:
	Bunny(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

	~Bunny();

	Bunny(Bunny&& bunny) noexcept;

	void setPosition(const glm::vec3& position);

	void setRotation(const glm::vec3& axis, float angle);

	void setScale(const glm::vec3& s);
    
    void loadShader();

	void draw(const glm::mat4& projection, const glm::mat4& view);
private:
	// center of the table
	glm::vec3 _position = { 0.0f,0.0f,0.0f };
	// rotation of the table
	glm::mat4 _rotation = glm::mat4(1.0f);
	// scale of the table
	glm::vec3 _scale = { 1.0f, 1.0f, 1.0f };

	// vertices of the table represented in model's own coordinate
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;

	// opengl objects
	GLuint _vao = 0;
	GLuint _vbo = 0;
	GLuint _ebo = 0;
    
    const char* _vsCode2 =
        "attribute vec3 aPosition;\n"
        "attribute vec3 aNormal;\n"
        "varying vec4 color;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "    vec3 normal = mat3(transpose(inverse(model))) * aNormal;\n"
        "    vec3 worldPosition = vec3(model * vec4(aPosition, 1.0f));\n"
        "    gl_Position = projection * view * vec4(worldPosition, 1.0f);\n"
        "   vec3 lightPosition = vec3(100.0f, 100.0f, 100.0f);\n"
        "   // ambient color\n"
        "   float ka = 0.0f;\n"
        "   vec3 objectColor = vec3(1.0f, 0.0f, 0.0f);\n"
        "   vec3 ambient = ka * objectColor;\n"
        "   // diffuse color\n"
        "   float kd = 0.8f;\n"
        "   vec3 lightColor = vec3(0.0f, 1.0f, 0.0f);\n"
        "   vec3 lightDirection = normalize(lightPosition - worldPosition);\n"
        "   vec3 diffuse = kd * lightColor * max(dot(normalize(normal), lightDirection), 0.0f);\n"
        "   color = vec4(ambient + diffuse, 1.0f);\n"
        "}\n";

    const char* _fsCode2 =
        "precision highp float;\n"
        "varying vec4 color;\n"
        "void main() {\n"
        "   gl_FragColor = color;\n"
        "}\n";
    
	const char* _vsCode =
		"#version 300 es\n"
        "precision highp float;"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"out vec4 color;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main() {\n"
		"	vec3 normal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	vec3 worldPosition = vec3(model * vec4(aPosition, 1.0f));\n"
		"	gl_Position = projection * view * vec4(worldPosition, 1.0f);\n"
        "   vec3 lightPosition = vec3(100.0f, 100.0f, 100.0f);\n"
        "   // ambient color\n"
        "   float ka = 0.0f;\n"
        "   vec3 objectColor = vec3(1.0f, 0.0f, 0.0f);\n"
        "   vec3 ambient = ka * objectColor;\n"
        "   // diffuse color\n"
        "   float kd = 0.8f;\n"
        "   vec3 lightColor = vec3(0.0f, 1.0f, 0.0f);\n"
        "   vec3 lightDirection = normalize(lightPosition - worldPosition);\n"
        "   vec3 diffuse = kd * lightColor * max(dot(normalize(normal), lightDirection), 0.0f);\n"
        "   color = vec4(ambient + diffuse, 1.0f);\n"
		"}\n";

	const char* _fsCode =
		"#version 300 es\n"
        "precision highp float;\n"
		"in vec4 color;\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
        "   fragColor = color;\n"
		"}\n";

	Shader _shader;
};
