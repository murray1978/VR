/*
  cube.cpp - 
	test - cube, 1x1x1, hard coded then from obj file.
*/

#include <GL/glut.h>

void init( void ) {
	glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glMatrixMode( GL_PROJECTION );
	gluOrtho2D( 0.0, 200.0, 0.0, 150.0 );
}

void draw( void ){
	glClear( GL_COLOR_BUFFER_BIT );

	glFlush();
}

int main( int argc, char **argv  ){

	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(0,0);
	glutInitWindowSize(128,128);
	glutCreateWindow("LeftWindow");
	init();
	
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
