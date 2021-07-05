//
//  ViewController.m
//  Where
//
//  Created by Apple on 2021/6/28.
//

#import "ViewController.h"
#import "GLView.h"

@interface ViewController ()
@property (nonatomic , strong) GLView* openGLView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.openGLView = (GLView *)self.view;

}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
