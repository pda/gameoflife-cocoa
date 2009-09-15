//
//  TestController.m
//  cocoatest
//
//  Created by Paul Annesley on 4/09/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "TestController.h"

#import <dispatch/dispatch.h>
#import <OpenGL/gl.h>
#import <sys/time.h>

@implementation TestController

- (IBAction)stop:(id)sender {
	isRunning = 0;
}

- (IBAction)run:(id)sender {

	glContext = 0;
	
	if (isRunning)
	{
		isRunning = 0;
	}
	else
	{
		dispatch_async(dispatch_get_global_queue(0, 0), ^{

			struct framerate fr;
			framerate_init(&fr);
			
			int counter = 0;
			
			isRunning = 1;
			
			if (glContext != 1)
			{
				[[ opengl openGLContext ] makeCurrentContext ];				
				glContext = 1;
			}
			
			if (!isInitialized)
				[self random];
			
			while (isRunning)
			{
				if (glContext != 1)
				{
					[[ opengl openGLContext ] makeCurrentContext ];				
					glContext = 1;
				}
				
				bitmap_render(game.active);
				gameoflife_tick(&game);
				counter++;
				
				if (counter % 10 == 0)
				{
					framerate_increment(&fr, 10);
					dispatch_async(dispatch_get_main_queue(), ^{
						[fps setIntValue:framerate_get(&fr)];
					});
				}

				usleep(sleep_usec);
			}
		});
	}
	
}

- (IBAction)random {
	if (!isInitialized)
	{
		gameoflife_init(&game, 192, 144);
		isInitialized = 1;
	}
	gameoflife_bitmap_random(&game, clock(), 16);
	[self render];
}

- (IBAction)speed:(id)sender {
	sleep_usec = [sender intValue] * -1;
}

- (IBAction)load:(id)sender {
	
	char gosper[9][36] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	
	if (glContext != 0)
	{
		glContext = 0;
		[[ opengl openGLContext ] makeCurrentContext ];				
	}
	
	if (!isInitialized)
	{
		gameoflife_init(&game, 192, 144);
		isInitialized = 1;
	}
	
	// TODO: no magic numbers
	switch ([sender indexOfSelectedItem]) {
			
		case 1:
			bitmap_clear(game.active);
			for (int y = 0; y < 9; y++)
				for (int x = 0; x < 36; x++)
					bitmap_set(game.active, x + 10, y + 10, gosper[y][x]);
			for (int y = 0; y < 9; y++)
				for (int x = 0; x < 36; x++)
					bitmap_set(game.active, x + 40, y + 45, gosper[y][x]);
			
			bitmap_set(game.active, 133, 128, 1);
			bitmap_set(game.active, 134, 128, 1);
			bitmap_set(game.active, 135, 128, 1);
			
			bitmap_set(game.active, 267, 262, 1);
			bitmap_set(game.active, 268, 262, 1);
			bitmap_set(game.active, 269, 262, 1);
			
			bitmap_set(game.active, 371, 366, 1);
			bitmap_set(game.active, 372, 366, 1);
			bitmap_set(game.active, 373, 366, 1);
			
			bitmap_set(game.active, 491, 486, 1);
			bitmap_set(game.active, 492, 486, 1);
			bitmap_set(game.active, 493, 486, 1);
			
			[self render];
			break;
			
		case 2:
			bitmap_clear(game.active);
			[self render];
			break;
			
		case 3:
			[self random];
			break;

		default:
			break;
	}
}

- (IBAction)render {
	bitmap_render(game.active);
}

@end
