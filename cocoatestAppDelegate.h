//
//  cocoatestAppDelegate.h
//  cocoatest
//
//  Created by Paul Annesley on 3/09/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface cocoatestAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	IBOutlet NSOpenGLView *opengl;
	struct gameoflife game;
}

@property (assign) IBOutlet NSWindow *window;

@end
