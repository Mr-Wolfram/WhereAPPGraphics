//
//  GLUtil.h
//  GLKit
//
//  Created by qinmin on 2017/1/4.
//  Copyright © 2017年 qinmin. All rights reserved.
//

#import<Foundation/Foundation.h>
#include <OpenGLES/ES3/gl.h>

@interface GLUtils: NSObject

// Create a shader object, load the shader source string, and compile the shader.
//
+(GLuint)loadShader:(GLenum)type withString:(NSString *)shaderString;

+(GLuint)loadShader:(GLenum)type withFilepath:(NSString *)shaderFilepath;

//直接返回program
+(GLuint)loadProgram:(NSString *)vertexShaderFilepath withFragmentShaderFilepath:(NSString *)fragmentShaderFilepath;

@end
