#include "hello_triangle.hpp"

HelloTriangle::HelloTriangle() {
    
}

void HelloTriangle::setup() {
    _shader.load(vsCode, fsCode);
    // create a vertex array object
    glGenVertexArrays(1, &_vao);
    // create a vertex buffer object
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

    // specify layout, size of a vertex, data type, normalize, sizeof vertex array, offset of the attribute
    GLuint positionLoca = glGetAttribLocation(_shader.getID(), "position");
    glEnableVertexAttribArray(positionLoca);
    
    GLuint colorLoca = glGetAttribLocation(_shader.getID(), "color");
    glEnableVertexAttribArray(colorLoca);
    
    glVertexAttribPointer(positionLoca, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(colorLoca, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
}

HelloTriangle::~HelloTriangle() {
    if (_vbo != 0) {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }

    if (_vao != 0) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}

void HelloTriangle::handleInput() {

}

void HelloTriangle::renderFrame() {

    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    _shader.use();
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
