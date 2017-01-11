#include <linux/fb.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

inline uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo)
{
	return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}

int main()
{
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;

	int fb_fd = open("/dev/fb1",O_RDWR);

	//Get variable screen information
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);

	//vinfo.grayscale=0;
	//vinfo.bits_per_pixel=16;
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
	long screensize = vinfo.yres_virtual * vinfo.xres_virtual;//finfo.line_length;

	uint8_t *fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);

	int x,y;

	for (x=0;x<vinfo.xres-1;x++)
		for (y=0;y<vinfo.yres-1;y++)
		{
			long location = (x/*+vinfo.xoffset*/) * (vinfo.bits_per_pixel/8) + (y/*+vinfo.yoffset*/) * vinfo.xres/*finfo.line_length*/;
			*((uint32_t*)(fbp + location)) = pixel_color(0xFF,0x00,0xFF, &vinfo);
		}

	return 0;
}
