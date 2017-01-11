#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void init( void )
{
	glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glMatrixMode( GL_PROJECTION );
	gluOrtho2D( 0.0, 200.0, 0.0, 150.0 );
}

void lineSegment( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin( GL_LINES );
		glVertex2i( 180, 15 );
		glVertex2i( 10, 145 );
	glEnd();
	
	glFlush();
}

void main( int argc, char *argv[])
{
	char *glVersion;
	char *glVendor;
	char *glRenderer;

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition( 50, 100 );
	glutInitWindowSize( 128, 128 );
	glutCreateWindow("example openGL program");
	
	glVersion = (char *)glGetString(GL_VERSION);
	printf("gl_version: %s\n", glVersion);
	glVendor  = (char *)glGetString(GL_VENDOR);	
        printf("gl_vendor: %s\n", glVendor);
	glRenderer = (char *)glGetString(GL_RENDERER);
	printf("gl_renderer, %s\n", glRenderer);

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}

