//
//  GLView.m
//  Where
//
//  Created by Apple on 2021/6/29.
//

#import "GLView.h"
#import "GLUtils.h"
#import <OpenGLES/ES3/gl.h>
//#import "hello_triangle.hpp"
#import "transformation.h"

@interface GLView ()
{
    CAEAGLLayer *_eaglLayer;  //OpenGL内容只会在此类layer上描绘
    EAGLContext *_context;    //OpenGL渲染上下文
    GLuint _renderBuffer;     //
    GLuint _frameBuffer;      //
    GLuint _depthBuffer;      //深度缓存

    GLuint _programHandle;
    GLuint _positionSlot;
    
    Transformation app;
}

@end

@implementation GLView

+(Class)layerClass{
    //OpenGL内容只会在此类layer上描绘
    return [CAEAGLLayer class];
}

-(instancetype)initWithFrame:(CGRect)frame{
    if (self==[super initWithFrame:frame]) {
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
//        [self setupProgram];  //配置program
        [self setupApp];
        [self render];
    }
    
    return self;
}

- (void)setupLayer
{
    _eaglLayer = (CAEAGLLayer*) self.layer;
    
    // CALayer 默认是透明的，必须将它设为不透明才能让其可见,性能最好
    _eaglLayer.opaque = YES;
    
    // 设置描绘属性，在这里设置不维持渲染内容以及颜色格式为 RGBA8
    _eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                     [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
}

- (void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES3;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 3.0 context");
    }
    
    // 设置为当前上下文
    [EAGLContext setCurrentContext:_context];
}

-(void)setupDepthBuffer{
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

-(void)setupRenderBuffer{
    glGenRenderbuffers(1, &_renderBuffer); //生成和绑定render buffer的API函数
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
    //为其分配空间
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

-(void)setupFrameBuffer{
    glGenFramebuffers(1, &_frameBuffer);   //生成和绑定frame buffer的API函数
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    //将renderbuffer跟framebuffer进行绑定
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _renderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
}

- (void)setupProgram
{
    // Load shaders
    //
    NSString * vertexShaderPath = [[NSBundle mainBundle] pathForResource:@"SimpleVertex"
                                                                  ofType:@"glsl"];
    NSString * fragmentShaderPath = [[NSBundle mainBundle] pathForResource:@"SimpleFragment"
                                                                    ofType:@"glsl"];

    // Create program.
    _programHandle = [GLUtils loadProgram:vertexShaderPath withFragmentShaderFilepath:fragmentShaderPath];
    
    glUseProgram(_programHandle);
    
    // Get attribute slot from program
    //
    _positionSlot = glGetAttribLocation(_programHandle, "vPosition");
}

-(void)setupApp {
    NSString * nsFilepath = [[NSBundle mainBundle] pathForResource:@"bunny" ofType:@"obj"];
    const char* filepath = [nsFilepath UTF8String];
    app.setup(filepath);
    app.windowsWidth = self.frame.size.width;
    app.windowsHeight = self.frame.size.height;
}

-(void)render
{
    // Setup viewport
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);
    app.run();
    
    [_context presentRenderbuffer:_renderBuffer];
}

@end
