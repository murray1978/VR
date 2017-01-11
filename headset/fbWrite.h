#pragma once
#include <linux/fb.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string.h>

#define FB_DEVICE 		0
#define FB_BITS_PER_PIXEL 	1
#define FB_SCREEN_X 		2
#define FB_SCREEN_Y 		3
#define FB_VIRTUAL_X 		4
#define FB_VIRTUAL_Y		5

class FBWrite{
public:
	FBWrite();
	FBWrite(const char *framebuffer);
	int 	FBSetScreenFrameBuffer( char * );
	int 	FBSetMemoryFrameBuffer( void *mem );
	void FBDraw( void );
	void FBDrawClear( unsigned char r, unsigned char b, unsigned char g);
	void FBDraw_m( unsigned char *mem );
	void FBDraw_a(unsigned char **array, int maxX, int maxY);
	char *FBGetString( char *what);
	int	FBGetInteger( char *what);
private:

	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;

	int fb_fd;
	long screensize;
	uint8_t *fbp;
	char *frameBuffer;
	int   iScreenSizeX;
	int   iScreenSizeY;

};

