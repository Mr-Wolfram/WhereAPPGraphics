#include "skybox.h"

SkyBox::SkyBox(GLuint skyboxTextureBoxID1, GLuint skyboxTextureBoxID2, GLuint skyboxTextureBoxID3, GLuint skyboxTextureBoxID4, GLuint skyboxTextureBoxID5, GLuint skyboxTextureBoxID6) {
	GLfloat vertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
	};

    // create vao and vbo
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);

    try {
        // init texture
        _texture.reset(new TextureCubemap(textureID));

        const char* vertCode =
            "#version 330 core\n"
            "layout(location = 0) in vec3 aPosition;\n"
            "out vec3 texCoord;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 view;\n"
            "void main() {\n"
            "   texCoord = aPosition;\n"
            "   gl_Position = (projection * view * vec4(aPosition, 1.0f)).xyww;\n"
            "}\n";

        const char* fragCode =
            "#version 330 core\n"
            "out vec4 color;\n"
            "in vec3 texCoord;\n"
            "uniform samplerCube cubemap;\n"
            "void main() {\n"
            "   color = texture(cubemap, texCoord);\n"
            "}\n";

        _shader.reset(new Shader(vertCode, fragCode));
    } catch(const std::exception&) {
        cleanup();
        throw;
    }

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::stringstream ss;
        ss << "skybox creation failure, (code " << error << ")";
        cleanup();
        throw std::runtime_error(ss.str());
    }
}

SkyBox::~SkyBox() {
    cleanup();
}

void SkyBox::draw(const glm::mat4& projection, const glm::mat4& view) {
    // -----------------------------------------------
    // write your code here

    glDepthMask(GL_FALSE);
    // 1. use the shader
    _shader->use();
    // 2. transfer mvp matrices to gpu 
    _shader->setMat4("projection", projection);
    _shader->setMat4("view", view);
    _shader->setInt("cubemap", 2);
    // 3. transfer material attributes to gpu
    glActiveTexture(GL_TEXTURE2);
    
    // -----------------------------------------------
    glBindVertexArray(_vao);
    _texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

void SkyBox::cleanup() {
    if (_vbo != 0) {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }

    if (_vao != 0) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}
