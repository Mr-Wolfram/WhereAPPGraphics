//
//  GLView.m
//  Where
//
//  Created by Apple on 2021/6/29.
//

#import "GLView.h"
#import "GLUtils.h"
#import "TextureManager.h"
#import <OpenGLES/ES3/gl.h>
//#import "hello_triangle.hpp"
//#import "transformation.h"
#import "entity.h"

@interface GLView ()
{
    CAEAGLLayer *_eaglLayer;  //OpenGL内容只会在此类layer上描绘
    EAGLContext *_context;    //OpenGL渲染上下文
    GLuint _renderBuffer;     //
    GLuint _frameBuffer;      //
    GLuint _depthBuffer;      //深度缓存

    GLuint _programHandle;
    GLuint _positionSlot;
    
    GLuint _blendTextureID1;
    GLuint _blendTextureID2;
    GLuint _blendTextureID3;
    GLuint _blendTextureID4;
    GLuint _blendTextureID5;
    GLuint _blendTextureID6;
    
    GLuint _skyboxTextureBoxID1;
    GLuint _skyboxTextureBoxID2;
    GLuint _skyboxTextureBoxID3;
    GLuint _skyboxTextureBoxID4;
    GLuint _skyboxTextureBoxID5;
    GLuint _skyboxTextureBoxID6;
    
    //手势
    UIPanGestureRecognizer *_panGesture;      //平移
    UIPinchGestureRecognizer *_pinchGesture;  //缩放
    UIRotationGestureRecognizer *_rotationGesture; //旋转
    
    NSTimer* myTimer;
    
    Entity* app;
}

@end

@implementation GLView

+(Class)layerClass{
    //OpenGL内容只会在此类layer上描绘
    return [CAEAGLLayer class];
}

- (void)layoutSubviews {
        _panGesture = [[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(viewTranslate:)];
        [self addGestureRecognizer:_panGesture];

        _pinchGesture = [[UIPinchGestureRecognizer alloc]initWithTarget:self action:@selector(viewZoom:)];
        [self addGestureRecognizer:_pinchGesture];

        _rotationGesture = [[UIRotationGestureRecognizer alloc]initWithTarget:self action:@selector(viewRotation:)];
        [self addGestureRecognizer:_rotationGesture];
        
        [self setupLayer];
        [self setupContext];
        
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        [self setupApp];
        [self setupTimer];
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
    _depthBuffer = 3;
//    NSLog(@"addr：%@",&_depthBuffer);
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
    
    app = new Entity();
    
    NSString * nsFilepath = [[NSBundle mainBundle] pathForResource:@"sphere" ofType:@"obj"];
    const char* filepath = [nsFilepath UTF8String];
    
    _blendTextureID1 = [TextureManager getTextureImage:[UIImage imageNamed:@"eye.png"]];
    _blendTextureID2 = [TextureManager getTextureImage:[UIImage imageNamed:@"bodyMap.png"]];
    _blendTextureID3 = [TextureManager getTextureImage:[UIImage imageNamed:@"bodyMap.png"]];
    _blendTextureID4 = [TextureManager getTextureImage:[UIImage imageNamed:@"bodyMap.png"]];
    _blendTextureID5 = [TextureManager getTextureImage:[UIImage imageNamed:@"planetMap.png"]];
    _blendTextureID6 = [TextureManager getTextureImage:[UIImage imageNamed:@"planetMap.png"]];
    
    app->_skyboxTextureBoxID1 = [TextureManager getTextureImage:[UIImage imageNamed:@"right.jpg"]];
    app->_skyboxTextureBoxID2 = [TextureManager getTextureImage:[UIImage imageNamed:@"left.jpg"]];
    app->_skyboxTextureBoxID3 = [TextureManager getTextureImage:[UIImage imageNamed:@"top.jpg"]];
    app->_skyboxTextureBoxID4 = [TextureManager getTextureImage:[UIImage imageNamed:@"bottom.jpg"]];
    app->_skyboxTextureBoxID5 = [TextureManager getTextureImage:[UIImage imageNamed:@"front.jpg"]];
    app->_skyboxTextureBoxID6 = [TextureManager getTextureImage:[UIImage imageNamed:@"back.jpg"]];
    
    app->windowWidth = self.frame.size.width;
    app->windowHeight = self.frame.size.height;
    app->setup();
    app->setModel(filepath, _blendTextureID1, _blendTextureID2, _blendTextureID3, _blendTextureID4, _blendTextureID5, _blendTextureID6);
}

-(void)setupTimer
{
    myTimer = [NSTimer scheduledTimerWithTimeInterval:app->deltaTime target:self selector:@selector(onRes:) userInfo:nil repeats:YES];
}


-(void)viewTranslate:(UIPanGestureRecognizer *)panGesture{
    NSLog(@"translate");
    CGPoint transPoint = [panGesture translationInView:self];
    float x = transPoint.x / self.frame.size.width;
    float y = transPoint.y / self.frame.size.height;
    app->move(glm::vec3(-x, y, 0.0f));
    
    [panGesture setTranslation:CGPointMake(0, 0) inView:self];
}

-(void)viewRotation:(UIRotationGestureRecognizer *)rotationGesture{
//    float rotate = rotationGesture.rotation;
//    RX += rotate/2.0;
//    RY += rotate/3.0;
//    RZ += rotate;
//
//    rotationGesture.rotation = 0;
}

-(void)viewZoom:(UIPinchGestureRecognizer *)pinchGesture{
    NSLog(@"zoom");
    float scale = pinchGesture.scale;
    
    app->doScale(scale - 1);

    pinchGesture.scale = 1.0;
}
- (IBAction)takeSnapshot:(id)sender {
    NSLog(@"Snapshot");
    UIImage *shareImg = [self takePicture];

    UIImageWriteToSavedPhotosAlbum(shareImg,self, @selector(resultImage:didFinishSavingWithError:contextInfo:), NULL);
}




- (void)onRes:(id)sender {
    [self render];
}

-(void)render
{
    // Setup viewport
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);
    app->run();
    
    [_context presentRenderbuffer:_renderBuffer];
}

- (UIImage*) takePicture {
    int s = 1;
    UIScreen* screen = [UIScreen mainScreen];
    if ([screen respondsToSelector:@selector(scale)]) {
        s = (int) [screen scale];
    }

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);


    int width = viewport[2];
    int height = viewport[3];

    int myDataLength = width * height * 4;
    GLubyte *buffer = (GLubyte *) malloc(myDataLength);
    GLubyte *buffer2 = (GLubyte *) malloc(myDataLength);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    for(int y1 = 0; y1 < height; y1++) {
        for(int x1 = 0; x1 <width * 4; x1++) {
            buffer2[(height - 1 - y1) * width * 4 + x1] = buffer[y1 * 4 * width + x1];
        }
    }
    free(buffer);

    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer2, myDataLength, NULL);
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow = 4 * width;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGImageRef imageRef = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    CGColorSpaceRelease(colorSpaceRef);
    CGDataProviderRelease(provider);
    UIImage *image = [ UIImage imageWithCGImage:imageRef scale:s orientation:UIImageOrientationUp ];
    return image;
}

- (void)resultImage:(UIImage *)image didFinishSavingWithError:(NSError *)error
  contextInfo:(void *)contextInfo {
    NSLog(@"Snapshot Done");
//    [SVProgressHUD showSuccessWithStatus:@"保存图片到相册成功"];

}






@end
