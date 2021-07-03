//
//  Block.hpp
//  Where
//
//  Created by Apple on 2021/7/2.
//

#ifndef Block_hpp
#define Block_hpp

#include <vector>
#include <glm/glm.hpp>

#include "../base/vertex.h"
#include "../base/shader.h"

struct BlockVertex {
    glm::vec3 position;
    glm::vec3 color;
};

class Block {
public:
    Block();

    ~Block();
    
    Block(Block&& block) noexcept;

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
    std::vector<BlockVertex> _vertices = {
        { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 1.0f, 0.0f) },
        { glm::vec3(0.5f,  0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f) },
        { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) },
        { glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f) },
        { glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 1.0f) },
        { glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f) }
    };
    
    std::vector<GLuint> _indices = {
        // Front face
        0, 3, 2, 0, 2, 1,
        
        // Back face
        7, 5, 4, 7, 6, 5,
        
        // Left face
        0, 1, 6, 0, 6, 7,
        
        // Right face
        3, 4, 5, 3, 5, 2,
        
        // Up face
        1, 2, 5, 1, 5, 6,
        
        // Down face
        0, 7, 4, 0, 4, 3
    };


    // opengl objects
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    
    const char* _vsCode =
        "#version 300 es\n"
        "precision mediump float;"
        "layout(location = 0) in vec3 aPosition;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec4 color;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "   gl_Position = model * vec4(aPosition, 1.0f);"
        "   color = vec4(aColor, 1.0f);\n"
        "}\n";

    const char* _fsCode =
        "#version 300 es\n"
        "precision mediump float;\n"
        "in vec4 color;\n"
        "layout(location = 0) out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = color;\n"
        "}\n";

    Shader _shader;
};

#endif /* Block_hpp */
