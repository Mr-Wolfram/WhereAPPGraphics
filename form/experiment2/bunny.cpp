#include "bunny.h"
#include <glm/ext.hpp>

Bunny::Bunny(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	: _vertices(vertices), _indices(indices) {
	
	// create a vertex array object
	glGenVertexArrays(1, &_vao);
	// create a vertex buffer object
	glGenBuffers(1, &_vbo);
	// create a element array buffer
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(uint32_t), _indices.data(), GL_STATIC_DRAW);

	// specify layout, size of a vertex, data type, normalize, sizeof vertex array, offset of the attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

Bunny::~Bunny() {
	if (_ebo != 0) {
		glDeleteBuffers(1, &_ebo);
		_ebo = 0;
	}

	if (_vbo != 0) {
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	}

	if (_vao != 0) {
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
}

Bunny::Bunny(Bunny&& bunny) noexcept {
	_position = bunny._position;
	_rotation = bunny._rotation;
	_scale = bunny._scale;

	_vertices = std::move(bunny._vertices);
	_indices = std::move(bunny._indices);
	
	_vao = bunny._vao;
	_vbo = bunny._vbo;
	_ebo = bunny._ebo;

	bunny._vao = 0;
	bunny._vbo = 0;
	bunny._ebo = 0;
}


void Bunny::setPosition(const glm::vec3& position) {
	_position = position;
}

void Bunny::setRotation(const glm::vec3& axis, float angle) {
	_rotation = glm::axisAngleMatrix(axis, angle);
}

void Bunny::setScale(const glm::vec3& scale) {
	_scale = scale;
}


void Bunny::draw(const glm::mat4& projection, const glm::mat4& view) {
	// model matrix transform the homogenous coodinates
	// from model space (raw vertex data form model) to world space, depending on following parametes:
	// change your code here
	// -----------------------------------------------
	// @translation
	glm::mat4 translation = glm::mat4(1.0f);
	// @rotation
	glm::mat4 rotation = glm::mat4(1.0f);
	// @scale
	glm::mat4 scale = glm::mat4(1.0f);

	glm::mat4 model = translation * rotation * scale;

	_shader.use();
	_shader.setMat4("projection", projection);
	_shader.setMat4("view", view);
	_shader.setMat4("model", model);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
