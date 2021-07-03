//
//  hello_triangle.hpp
//  Where
//
//  Created by Apple on 2021/6/29.
//

#pragma once

#include "application.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class HelloTriangle : public Application {
public:
    HelloTriangle();

    ~HelloTriangle();

    virtual void setup();
    
private:
    GLuint _vao = 0;

    GLuint _vbo = 0;

    Vertex _vertices[3] = {
        { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 1.0f, 0.0f) },
        { glm::vec3(0.0f,  0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f) }
    };

    const char* vsCode =
    "attribute vec4 position;\n"
    "attribute vec4 color;\n"
    "varying vec4 aColor; // 向片段着色器输出一个颜色\n"
    "void main(void) {\n"
    "    gl_Position = position;\n"
    "    aColor = color; // aColor设置为我们从顶点数据那里得到的输入颜色\n"
    "}\n";

    const char* fsCode =
    "precision mediump float;\n"
    "varying lowp vec4 aColor; // 接受顶点着色器输出的颜色\n"
    "void main(void) {\n"
    "    gl_FragColor = aColor; // 设置最终颜色为接受的颜色\n"
    "}\n";

    Shader _shader;

    virtual void handleInput();

    virtual void renderFrame();

};

