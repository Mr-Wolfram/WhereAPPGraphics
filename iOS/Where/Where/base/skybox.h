#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"

class SkyBox {
public:
	SkyBox(const std::vector<std::string>& textureFilenames);

	~SkyBox();

	void draw(const glm::mat4& projection, const glm::mat4& view);

private:
	GLuint _vao = 0;
	GLuint _vbo = 0;

	std::unique_ptr<TextureCubemap> _texture;

	std::unique_ptr<Shader> _shader;

	void cleanup();
};