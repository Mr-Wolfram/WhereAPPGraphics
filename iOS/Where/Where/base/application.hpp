//
//  application.hpp
//  Where
//
//  Created by Apple on 2021/6/29.
//

#pragma once

#include <stdio.h>
#include <glm/glm.hpp>
#include <OpenGLES/ES3/gl.h>

#include "shader.h"

class Application {
public:
    Application();
    ~Application();
    
    void run();
    
    float windowWidth, windowHeight;
    
    float deltaTime = 0.05;
protected:
    
    glm::vec4 _clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    virtual void renderFrame() = 0;
    
};
