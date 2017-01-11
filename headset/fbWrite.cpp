#include "fbWrite.h"

inline uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo)
{
	return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}

/*
Segfaults because of const char *frambuffer being given to open. 
*/
FBWrite::FBWrite(const char *framebuffer){

	//printf("framebuffer %s\n", framebuffer);
	fb_fd = open(framebuffer, O_RDWR);

	//Get variable screen information
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);

	vinfo.grayscale=0;
	vinfo.bits_per_pixel=8;
	ioctl(fb_fd, FBIOPUT_VSCREENINFO, &vinfo);
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);

	ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo);
	screensize = vinfo.yres_virtual * finfo.line_length;

	fbp = (uint8_t *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);

}


FBWrite::FBWrite()
{
	
	fb_fd = open("/dev/fb1",O_RDWR);

	//Get variable screen information
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);

	vinfo.grayscale=0;
	vinfo.bits_per_pixel=16;
	ioctl(fb_fd, FBIOPUT_VSCREENINFO, &vinfo);
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);

	ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo);

	printf("yres_virtual : %i \n", vinfo.yres_virtual);
	printf("xres_virtual : %i \n", vinfo.xres_virtual);

	printf("yres : %i \n", vinfo.yres);
	printf("xres : %i \n", vinfo.xres);
	
	printf("bpp : %i \n", vinfo.bits_per_pixel);
	printf("grayscale : %i \n", vinfo.grayscale);

	printf("line_length : %i \n", finfo.line_length );
	
	//finfo reports line length 100 bytes to long, segfaults
	screensize = vinfo.yres_virtual * finfo.line_length;

	fbp = (uint8_t *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);
};

void FBWrite::FBDraw(void){
	int x,y;
	long location = 0;

	for (x=0;x<vinfo.xres-1;x++)
		for (y=0;y<vinfo.yres-1;y++)
		{
			
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
			*((uint32_t*)(fbp + location)) = pixel_color(0xFF,0xFF,0xFF, &vinfo);
		}

}

void FBWrite::FBDraw_m(unsigned char *mem){
	int x,y;
	long location = 0;
	int offset = 0;

	for (x=0;x<vinfo.xres ;x++){
		for (y=0;y<vinfo.yres ;y++)
		{		
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
			//*((uint32_t*)(fbp + location)) = pixel_color(0xFF,0xFF,0xFF, &vinfo);
			*((uint32_t*)(fbp + location)) = pixel_color( mem[offset], mem[offset+1], mem[offset+2], &vinfo);
			offset = offset +3;
		}
	}
}


void FBWrite::FBDrawClear( unsigned char r, unsigned char b, unsigned char g){
	int x,y;
	long location = 0;
	for (x=0;x<vinfo.xres+1;x++){
		for (y=0;y<vinfo.yres+1;y++)
		{
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8)  +  (y+vinfo.yoffset) * finfo.line_length;
			*((uint32_t*)(fbp + location)) = pixel_color(r,g,b, &vinfo);
		}
	}
}

void FBWrite::FBDraw_a(unsigned char **array, int maxX, int maxY){
/*	int fbX, fbY;
	long location = 0;
	for ( fbX = 0; fbX < vinfo.xres + 1; fbX++ ){
		for ( fbY = 0; fbY < vinfo.yres + 1; fbY++)
		{
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8)  +  (y+vinfo.yoffset) * finfo.line_length;
			*((uint32_t*)(fbp + location)) = pixel_color(r,g,b, &vinfo);
		}
	}*/
}
