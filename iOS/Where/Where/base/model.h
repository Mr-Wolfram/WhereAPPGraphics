#pragma once

#include <string>
#include <vector>

#include <OpenGLES/ES3/gl.h>
#include "vertex.h"
#include "object3d.h"

class Model : public Object3D {
public:
	Model(const std::string& filepath);

	Model(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	~Model();

	Model(Model&& model) noexcept = default;

	GLuint getVertexArrayObject() const;

	size_t getVertexCount() const;

	size_t getFaceCount() const;

	void draw() const;

private:
	// vertices of the table represented in model's own coordinate
	std::vector<Vertex> _vertices;
	std::vector<uint32_t> _indices;

	// opengl objects
	GLuint _vao = 0;
	GLuint _vbo = 0;
	GLuint _ebo = 0;

	void initGLResources();
};
