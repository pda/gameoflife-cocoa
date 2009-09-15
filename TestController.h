//
//  TestController.h
//  cocoatest
//
//  Created by Paul Annesley on 4/09/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <time.h>
#import "gameoflife.h"
#import "framerate.h"

@interface TestController : NSObject {

	IBOutlet NSOpenGLView *opengl;
	IBOutlet NSTextField *fps;
	struct gameoflife game;
	int isInitialized, isRunning, glContext;
	int sleep_usec;
}

- (IBAction)run:(id)sender;
- (IBAction)random;
- (IBAction)speed:(id)sender;
- (IBAction)load:(id)sender;
- (IBAction)render;

@end
