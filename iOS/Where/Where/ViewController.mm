//
//  ViewController.m
//  Where
//
//  Created by Apple on 2021/6/28.
//

#import "ViewController.h"
#import "GLView.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    GLView *openGLView = [[GLView alloc]initWithFrame:self.view.bounds];
    [self.view addSubview:openGLView];

}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
