//
//  Block.cpp
//  Where
//
//  Created by Apple on 2021/7/2.
//

#include "Block.hpp"
#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

Block::Block(){
    // create a vertex array object
    glGenVertexArrays(1, &_vao);
    // create a vertex buffer object
    glGenBuffers(1, &_vbo);
    // create a element array buffer for
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BlockVertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indices.size(), _indices.data(), GL_STATIC_DRAW);
    // specify layout, size of a vertex, data type, normalize, sizeof vertex array, offset of the attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), (void*)offsetof(BlockVertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), (void*)offsetof(BlockVertex, color));
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    //glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Block::~Block() {
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

Block::Block(Block&& table) noexcept {
    _position = table._position;
    _rotation = table._rotation;
    _scale = table._scale;
    
    _vertices = std::move(table._vertices);
    _indices = std::move(table._indices);
    
    _vao = table._vao;
    _vbo = table._vbo;
    _ebo = table._ebo;

    table._vao = 0;
    table._vbo = 0;
    table._ebo = 0;
}

void Block::loadShader() {
    _shader.load(_vsCode, _fsCode);
}
void Block::setPosition(const glm::vec3& position) {
    _position = position;
}

void Block::setRotation(const glm::vec3& axis, float angle) {
    _rotation = glm::axisAngleMatrix(axis, angle);
}

void Block::setScale(const glm::vec3& scale) {
    _scale = scale;
}


void Block::draw(const glm::mat4& projection, const glm::mat4& view) {
    // model matrix transform the homogenous coodinates
    // from model space (raw vertex data form model) to world space, depending on following parametes:
    // change your code here
    // -----------------------------------------------
    // @translation
    glm::mat4 translation = glm::mat4(1.0f);
    translation = glm::translate(translation, _position);
    // @rotation
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = _rotation;
    // @scale
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(scale, _scale);
    
    glm::mat4 model = translation * rotation * scale;

    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);
    _shader.setMat4("model", model);
    glBindVertexArray(_vao);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

