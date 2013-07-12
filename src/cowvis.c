#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "cowvis.h"

#define ESCAPE 27

int window = 0;
int fullscreen = 0;
float rotx = 0.0f;
float roty = 0.0f;
char window_name[] = "C.O.W. Vis";

int create_window(char *title, int x, int y, int width, int height)
{
	int id;
	
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	
	id = glutCreateWindow(title);
	if(id < 1)
	{
		printf("Window not created: %d", id);
		return 0;
	}
	
	if(fullscreen)
		glutFullScreen();
	
	glutDisplayFunc(&DrawGLScene);
	glutIdleFunc(&DrawGLScene);
	glutReshapeFunc(&ReSizeGLScene);
	glutKeyboardFunc(&keyPressed);
	
	InitGL(width, height);
	
	return id;
}

void InitGL(int width, int height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ((GLfloat)width) / ((GLfloat)height), 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
}

void ReSizeGLScene(int width, int height)
{
	if(height == 0)
		height = 1;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ((GLfloat)width) / ((GLfloat)height), 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
}

void DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -1.5f);
	glRotatef(rotx, 0.0f, 1.0f, 0.0f);
	glRotatef(roty, 1.0f, 0.0f, 0.0f);
	
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f( 0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f,-0.5f, 0.0f);
	glVertex3f( 0.5f,-0.5f, 0.0f);
	glEnd();
	
	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y)
{
	if(key == ESCAPE)
	{
		glutDestroyWindow(window);
		exit(0);
	}
	
	if(key == 'f')
	{
		fullscreen = (fullscreen+1)%2;
		glutDestroyWindow(window);
		window = create_window(window_name, 0, 0, 640, 480);
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	fullscreen = 0;
	window = create_window(window_name, 0, 0, 640, 480);
	glutMainLoop();

	return 1;
}
