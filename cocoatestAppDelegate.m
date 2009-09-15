//
//  cocoatestAppDelegate.m
//  cocoatest
//
//  Created by Paul Annesley on 3/09/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#include "gameoflife.h"

#import "cocoatestAppDelegate.h"

@implementation cocoatestAppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	
	[[ opengl openGLContext ] makeCurrentContext ];
	
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, 960, 720, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(6);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glFlush();
}

@end
