#pragma once

#include <memory>
#include <string>
#include <vector>

#include <OpenGLES/ES3/gl.h>

#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"

class SkyBox {
public:
	SkyBox(GLuint skyboxTextureBoxID1, GLuint skyboxTextureBoxID2, GLuint skyboxTextureBoxID3, GLuint skyboxTextureBoxID4, GLuint skyboxTextureBoxID5, GLuint skyboxTextureBoxID6);

	~SkyBox();

	void draw(const glm::mat4& projection, const glm::mat4& view);

private:
	GLuint _vao = 0;
	GLuint _vbo = 0;

	std::unique_ptr<TextureCubemap> _texture;

	std::unique_ptr<Shader> _shader;

	void cleanup();
};
