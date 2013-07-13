#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "cowvis.h"

#define ESCAPE_KEY 27

int init_width = 640;
int init_height = 480;

int window = 0;
int fullscreen = 0;
float rotx = 0.0f;
float roty = 0.0f;
float transz = -3.0f;
float delta_theta = 5.0f;
float mag_scale = 1.1f;
char window_name[] = "C.O.W. Vis";

cow_domain *dom;
cow_dfield *dfield;

void ReshapeFunc(int width, int height)
{
	if(height == 0)
		height = 1;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ((GLfloat)width) / ((GLfloat)height), 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
}

void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, transz);
	glRotatef(roty, 0.0f, 1.0f, 0.0f);
	glRotatef(rotx, 1.0f, 0.0f, 0.0f);
	
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.0f);
	glVertex3f( 0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f,-0.5f, 0.0f);
	glVertex3f( 0.5f,-0.5f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 0.5f);
	glVertex3f( 0.5f, 0.0f, 0.5f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(-0.5f, 0.0f,-0.5f);
	glVertex3f( 0.5f, 0.0f,-0.5f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f( 0.0f, 0.5f, 0.5f);
	glVertex3f( 0.0f, 0.5f,-0.5f);
	glVertex3f( 0.0f,-0.5f,-0.5f);
	glVertex3f( 0.0f,-0.5f, 0.5f);
	glEnd();
	
	cv_wirecube(1.0f);
	
	glutSwapBuffers();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
		case ESCAPE_KEY:	
			cv_exit();
			break;
			
		case 'f':
			fullscreen = (fullscreen+1)%2;
			glutDestroyWindow(window);
			window = cv_create_window(window_name, 0, 0, init_width, init_height);
			break;
			
		case '-':
			transz *= mag_scale;
			break;
		case '=':
			transz /= mag_scale;
			break;
		
		default:
			break;
	}
}

void SpecialFunc(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:
			roty += delta_theta;
			break;
		case GLUT_KEY_LEFT:
			roty -= delta_theta;
			break;
		case GLUT_KEY_UP:
			rotx -= delta_theta;
			break;
		case GLUT_KEY_DOWN:
			rotx += delta_theta;
			break;
		default:
			break;
	}
	
	glutPostRedisplay();
}

int cv_create_window(char *title, int x, int y, int width, int height)
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
	
	glutDisplayFunc(&DisplayFunc);
	glutIdleFunc(&DisplayFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardFunc(&KeyboardFunc);
	glutSpecialFunc(&SpecialFunc);
	
	cv_init_gl(width, height);
	
	return id;
}

void cv_init_gl(int width, int height)
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

void cv_exit()
{
	glutDestroyWindow(window);
	cow_dfield_del(dfield);
	cow_domain_del(dom);
	cv_message("Everything swept under the rug.");
	exit(0);
}

void cv_wirecube(float side)
{
	float disp = 0.5f * side;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( disp, disp, disp);
	glVertex3f(-disp, disp, disp);
	glVertex3f(-disp,-disp, disp);
	glVertex3f( disp,-disp, disp);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f( disp, disp,-disp);
	glVertex3f( disp,-disp,-disp);
	glVertex3f(-disp,-disp,-disp);
	glVertex3f(-disp, disp,-disp);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f( disp, disp,-disp);
	glVertex3f(-disp, disp,-disp);
	glVertex3f(-disp, disp, disp);
	glVertex3f( disp, disp, disp);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f( disp,-disp,-disp);
	glVertex3f( disp,-disp, disp);
	glVertex3f(-disp,-disp, disp);
	glVertex3f(-disp,-disp,-disp);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f( disp, disp,-disp);
	glVertex3f( disp, disp, disp);
	glVertex3f( disp,-disp, disp);
	glVertex3f( disp,-disp,-disp);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-disp, disp,-disp);
	glVertex3f(-disp,-disp,-disp);
	glVertex3f(-disp,-disp, disp);
	glVertex3f(-disp, disp, disp);
	glEnd();
}

int main(int argc, char *argv[])
{
	int err;
	char *filename;
	char field_member[] = "phi/phi";
	
	if(argc > 1)
		filename = argv[1];
	else
	{
		printf("\nYa gotta give me a file numbnuts!\n\n");
		return 0;
	}
	
	dom = cow_domain_new();
	dfield = cow_dfield_new();
	
	err = cow_domain_readsize(dom, filename, field_member);
	if(err)
	{
		fprintf(stderr, "Unable to read size of dataset %s.  Does it even exist?\n", field_member);
		return 1;
	}
	
	cow_domain_setguard(dom, 2);
	cow_domain_setextent(dom, 0, -0.5, 0.5);
	cow_domain_setextent(dom, 1, -0.5, 0.5);
	cow_domain_setextent(dom, 2, -0.5, 0.5);
	cow_domain_commit(dom);
	
	cow_dfield_setname(dfield, "phi");
	cow_dfield_addmember(dfield, "phi");
	cow_dfield_addmember(dfield, "phiv");
	cow_dfield_setdomain(dfield, dom);
	cow_dfield_commit(dfield);
	
	cv_message("Reading data file");
	
	cow_dfield_read(dfield, filename);
	cow_dfield_syncguard(dfield);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	window = cv_create_window(window_name, 0, 0, init_width, init_height);
	glutMainLoop();

	return 1;
}
