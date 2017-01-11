#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>


#include "fbWrite.h"

const char *leftScreen = "/dev/fb1";
FBWrite *leftTFT;
int tftWidth = 128;
int tftHeight = 160;

void init( void )
{
	glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glMatrixMode( GL_PROJECTION );
	gluOrtho2D( 0.0, 200.0, 0.0, 150.0 );
}

void handleKeypress( unsigned char key, int x, int y){
	
	switch( key )
	{
		case 27:
		{
			exit(0);
		}
	}
}

int getelem2d(int i, int j, int k, int width, int height, int depth, GLubyte *array3d)
{
int value;

value = array3d[k + depth * (j + height * i)];

return value;
}

void putelem2d(int fwdvalue, int i, int j, int k, int width, int height, int depth, GLubyte *array3d)
{
array3d[k + depth * (j + height * i)] = fwdvalue;
}

void grabber( int height, int width){
	int pixelsQty;
	int i,j,k;
	int x,y;
	int fwdValue;
	unsigned char *curpix;
	GLubyte *pixels;
	//GLubyte *revPixels;

	//How many pixels
	pixelsQty = 3 * width * height;
	
	//glReadBuffer(GL_FRONT);

	//Set up alignment format for bitmap.
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei( GL_PACK_ALIGNMENT,  1);
	glPixelStorei( GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0);

	//pixel array, mode 1
	pixels = (GLubyte*) malloc(pixelsQty);
	if(	!pixels ){
		printf("error, not enough memory to assign pixels");
		exit(0);
	}
	
	//rev pixel array, mode 1
	//revPixels = (GLubyte*) malloc(pixelsQty);
	//if(	!revPixels ){
	//	printf("error, not enough memory to assign revPixels");
	//	exit(0);
	//}
	
	//store image from back buffer
	glPixelStorei( GL_UNPACK_ROW_LENGTH, 0);

	//store pixels in memory
	glReadPixels(0,0, height, width, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	/* Save pixels' RGB values inverse to an array */
	//for (i = 0; i < height; i++)
	//	for (j = 0; j < width; j++)
	//		for (k = 0; k < 3; k++)
	//		{	
	//			fwdValue = getelem2d(i, j, k, width, height, 3, pixels);
	//			putelem2d(fwdValue, i, j, (2 - k), width, height, 3, revPixels);
	//		}	

	leftTFT->FBDraw_m((unsigned char*)pixels);
	free(pixels);
	//free(revPixels);
}

void lineSegment( void ){
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin( GL_LINES );
		glVertex2i( 180, 15 );
		glVertex2i( 10, 145 );
	glEnd();
	
	grabber(tftHeight,tftWidth);

	if( glGetError )
		printf("gl error, %i", glGetError);
	glFlush();

	

}


int main( int argc, char **argv){
	leftTFT = new FBWrite();
	//FBWrite *rightTFT = new FBWrite((char*)"/dev/fb2");
	leftTFT->FBDrawClear(0x00, 0x00, 0x00	);
	//leftTFT->FBDrawClear(0xFF, 0xFF, 0xFF );

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition( 50, 100 );
	glutInitWindowSize( tftHeight, tftWidth );
	glutCreateWindow("example openGL program");
	
	init();
	glutKeyboardFunc(handleKeypress);
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}
