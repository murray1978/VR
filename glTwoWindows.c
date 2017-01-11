#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void handleKeypress( unsigned char key, int x, int y){
	
	switch( key )
	{
		case 27:
		{
			exit(0);
		}
	}
}

void resize(int w, int h){
	glViewport( 0,0,500,500);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45,(double)500/(double)500,1.0,200);
}

void init( void ){
	glEnable( GL_DEPTH_TEST);

}

void drawLeft( void ){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
		glVertex3f( 0.0f, 0.0f, -5.0f);
		glVertex3f( 0.0f, 1.0f, -5.0f);
		glVertex3f(1.0f, 1.0f, -5.0f);
		glVertex3f(1.0f, 0.0f, -5.0f);
	glEnd();

	glutSwapBuffers();
}

void drawRight( void){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,-5.0f);
	glVertex3f(0.0f,1.0f,-5.0f);
	glVertex3f(1.0f,1.0f,-5.0f);
	glVertex3f(1.0f,0.0f,-5.0f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc,char** argv){

    glutInit(&argc,argv);
    init();
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);

    

    //window1=

     glutCreateWindow("LeftEye");
glutPositionWindow(10,10);
    glutDisplayFunc(drawLeft);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(resize);
    //create the second  window

    //window2 =

    glutCreateWindow("rightEye");

    //define a window position for second window

    glutPositionWindow(510,410);

    // register callbacks for second window, which is now current
    glutDisplayFunc(drawRight);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(resize);


    glutMainLoop();

    return 0;

}

