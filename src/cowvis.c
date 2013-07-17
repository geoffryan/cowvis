#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
int mode = 0;
int mem = 0;
int cm = 3;

cow_domain *dom;
cow_dfield *dfield;
double min;
double max;

cv_cutplane cutplanes[3];
cv_projection projection_r;

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
void IdleFunc()
{
	glutPostRedisplay();
}

void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, transz);
	glRotatef(roty, 0.0f, 1.0f, 0.0f);
	glRotatef(rotx, 1.0f, 0.0f, 0.0f);
	
	switch(mode)
	{
		case 0:
			cv_draw_cutplanes();
			break;
		case 1:
			cv_draw_projection();
			break;
		default:
			cv_draw_cutplanes();
			break;
	}
	
//	glBegin(GL_QUADS);
//	glColor3f(0.5f, 0.5f, 0.0f);
//	glVertex3f( 0.5f, 0.5f, 0.0f);
//	glVertex3f(-0.5f, 0.5f, 0.0f);
//	glVertex3f(-0.5f,-0.5f, 0.0f);
//	glVertex3f( 0.5f,-0.5f, 0.0f);
//	glEnd();
//	glBegin(GL_QUADS);
//	glColor3f(0.5f, 0.0f, 0.5f);
//	glVertex3f( 0.5f, 0.0f, 0.5f);
//	glVertex3f(-0.5f, 0.0f, 0.5f);
//	glVertex3f(-0.5f, 0.0f,-0.5f);
//	glVertex3f( 0.5f, 0.0f,-0.5f);
//	glEnd();
//	glBegin(GL_QUADS);
//	glColor3f(0.0f, 0.5f, 0.5f);
//	glVertex3f( 0.0f, 0.5f, 0.5f);
//	glVertex3f( 0.0f, 0.5f,-0.5f);
//	glVertex3f( 0.0f,-0.5f,-0.5f);
//	glVertex3f( 0.0f,-0.5f, 0.5f);
//	glEnd();
//	
//	cv_wirecube(1.0f);
	
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
			cv_build_cutplanes();
			break;
			
		case '-':
			transz *= mag_scale;
			break;
		case '=':
			transz /= mag_scale;
			break;
			
		case 'c':
			cm++;
			break;
			
		case 'x':
			cutplanes[0].ind++;
			cv_build_cutplane(0);
			break;
			
		case 'y':
			cutplanes[1].ind++;
			cv_build_cutplane(1);
			break;
			
		case 'z':
			cutplanes[2].ind++;
			cv_build_cutplane(2);
			break;
			
		case 'p':
			mode = 1;
			projection_r.built = 0;
			cv_build_scene();
			break;
			
		case 'u':
			mode = 0;
			cv_build_scene();
			break;
			
		case '1':
			mem = 0;
			cv_build_scene();
			break;
		case '2':
			if(cow_dfield_getnmembers(dfield) >= 2)
			{
				mem = 1;
				cv_build_scene();
			}
			break;
		case '3':
			if(cow_dfield_getnmembers(dfield) >= 3)
			{
				mem = 2;
				cv_build_scene();
			}
			break;
		case '4':
			if(cow_dfield_getnmembers(dfield) >= 4)
			{
				mem = 3;
				cv_build_scene();
			}
			break;
		case '5':
			if(cow_dfield_getnmembers(dfield) >= 5)
			{
				mem = 4;
				cv_build_scene();
			}
			break;
		case '6':
			if(cow_dfield_getnmembers(dfield) >= 6)
			{
				mem = 5;
				cv_build_scene();
			}
			break;
		case '7':
			if(cow_dfield_getnmembers(dfield) >= 7)
			{
				mem = 6;
				cv_build_scene();
			}
			break;
		case '8':
			if(cow_dfield_getnmembers(dfield) >= 8)
			{
				mem = 7;
				cv_build_scene();
			}
			break;
		case '9':
			if(cow_dfield_getnmembers(dfield) >= 9)
			{
				mem = 8;
				cv_build_scene();
			}
			break;
		case '0':
			if(cow_dfield_getnmembers(dfield) >= 10)
			{
				mem = 9;
				cv_build_scene();
			}
			break;
		
		default:
			break;
	}
	
	glutPostRedisplay();
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
	glutIdleFunc(&IdleFunc);
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

void cv_init()
{
	int i,j,k;
	int nx, ny, nz, ng, sx, sy, sz;
	double *data = cow_dfield_getdatabuffer(dfield);
	
	nx = cow_domain_getsize(dom, 0);
	ny = cow_domain_getsize(dom, 1);
	nz = cow_domain_getsize(dom, 2);
	ng = cow_domain_getguard(dom);
	sx = cow_dfield_getstride(dfield, 0);
	sy = cow_dfield_getstride(dfield, 1);
	sz = cow_dfield_getstride(dfield, 2);
	
	min = data[sx*ng+sy*ng+sz*ng];
	max = data[sx*ng+sy*ng+sz*ng];
	
	for(i=ng; i<nx+ng; i++)
		for(j=ng; j<ny+ng; j++)
			for(k=ng; k<nz+ng; k++)
			{
				if(data[sx*i+sy*j+sz*k] < min)
					min = data[sx*i+sy*j+sz*k];
				if(data[sx*i+sy*j+sz*k] > max)
					max = data[sx*i+sy*j+sz*k];
			}
	
	for(i=0; i<3; i++)
		cutplanes[i] = cutplane_default;
	
	projection_r = projection_default;
}

void cv_exit()
{
	int i;
	for(i=0; i<3; i++)
		glDeleteTextures(1, &(cutplanes[i].tex));
	if(projection_r.x != NULL)
		free(projection_r.x);
	if(projection_r.y != NULL)
		free(projection_r.y);
	glutDestroyWindow(window);
	cow_dfield_del(dfield);
	cow_domain_del(dom);
	cv_message("Everything swept under the rug.");
	exit(0);
}

void cv_build_scene()
{
	switch(mode)
	{
		case 0:
			cv_build_cutplanes();
			break;
		case 1:
			projection_r.built = 0;
			cv_build_projection_r();
			break;
		default:
			cv_build_cutplanes();
			break;
	}
}

void cv_build_cutplanes()
{
	int i,j,k;
	int nx, ny, nz, ng, sx, sy, sz;
	double *data = cow_dfield_getdatabuffer(dfield);
	
	nx = cow_domain_getsize(dom, 0);
	ny = cow_domain_getsize(dom, 1);
	nz = cow_domain_getsize(dom, 2);
	ng = cow_domain_getguard(dom);
	sx = cow_dfield_getstride(dfield, 0);
	sy = cow_dfield_getstride(dfield, 1);
	sz = cow_dfield_getstride(dfield, 2);
	
	min = data[sx*ng+sy*ng+sz*ng+mem];
	max = data[sx*ng+sy*ng+sz*ng+mem];
	
	for(i=ng; i<nx+ng; i++)
		for(j=ng; j<ny+ng; j++)
			for(k=ng; k<nz+ng; k++)
			{
				if(data[sx*i+sy*j+sz*k+mem] < min)
					min = data[sx*i+sy*j+sz*k+mem];
				if(data[sx*i+sy*j+sz*k+mem] > max)
					max = data[sx*i+sy*j+sz*k+mem];
			}
	
	cv_build_cutplane(0);
	cv_build_cutplane(1);
	cv_build_cutplane(2);
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

void cv_build_cutplane(int ax)
{
	int ind[3];
	int ng, sx, sy, sz, nm;
	int nx[3];
	int ax1, ax2;
	double *raw_data = cow_dfield_getdatabuffer(dfield);
	double val, depth;
	GLfloat rrr, ggg, bbb;
	
	nx[0] = cow_domain_getsize(dom, 0);
	nx[1] = cow_domain_getsize(dom, 1);
	nx[2] = cow_domain_getsize(dom, 2);
	ng = cow_domain_getguard(dom);
	sx = cow_dfield_getstride(dfield, 0);
	sy = cow_dfield_getstride(dfield, 1);
	sz = cow_dfield_getstride(dfield, 2);
	nm = cow_dfield_getnmembers(dfield);
	
	ax = ax%3;
	ax1 = (ax+1)%3;
	ax2 = (ax+2)%3;
	
	GLfloat *tex_data = (GLfloat *) malloc(3*nx[ax1]*nx[ax2] * sizeof(GLfloat));
	
	if(cutplanes[ax].tex == 0)
	{
		glGenTextures(1, &(cutplanes[ax].tex));
		cutplanes[ax].ind  = nx[ax]/2;
	}
	cutplanes[ax].ind = cutplanes[ax].ind % nx[ax];
	
	//TODO: Make this use guardzones properly.
	for(ind[0]=ng; ind[0]<nx[0]+ng; ind[0]++)
		for(ind[1]=ng; ind[1]<nx[1]+ng; ind[1]++)
			for(ind[2]=ng; ind[2]<nx[2]+ng; ind[2]++)
				if(ind[ax] == cutplanes[ax].ind)
				{
					val = (raw_data[sx*ind[0]+sy*ind[1]+sz*ind[2]+mem] - min) / (max-min);
					cv_cmap(val, cm, &rrr, &ggg, &bbb);
					tex_data[3*(nx[ax1]*ind[ax2]-ng+ind[ax1])+0] = rrr;
					tex_data[3*(nx[ax1]*ind[ax2]+ind[ax1])+1] = ggg;
					tex_data[3*(nx[ax1]*ind[ax2]+ind[ax1])+2] = bbb;
				}
	cutplanes[ax].cmap = cm;
	
	depth = (((float)cutplanes[ax].ind) + 0.5f) / ((float) nx[ax]) - 0.5f;
	
	cutplanes[ax].X0[ax] = depth;
	cutplanes[ax].X0[ax1] = -0.5f;
	cutplanes[ax].X0[ax2] = -0.5f;
	cutplanes[ax].X1[ax] = depth;
	cutplanes[ax].X1[ax1] =  0.5f;
	cutplanes[ax].X1[ax2] = -0.5f;
	cutplanes[ax].X2[ax] = depth;
	cutplanes[ax].X2[ax1] =  0.5f;
	cutplanes[ax].X2[ax2] =  0.5f;
	cutplanes[ax].X3[ax] = depth;
	cutplanes[ax].X3[ax1] = -0.5f;
	cutplanes[ax].X3[ax2] =  0.5f;
	
	glBindTexture(GL_TEXTURE_2D, cutplanes[ax].tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nx[ax1], nx[ax2], 0, GL_RGB, GL_FLOAT, tex_data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	free(tex_data);
	
}

void cv_draw_cutplanes()
{
	int i;
	
	cv_wirecube(1.0f);
	
	glEnable(GL_TEXTURE_2D);
	
	for(i=0; i<3; i++)
	{
		if(cutplanes[i].tex == 0 || cutplanes[i].cmap != cm)
			cv_build_cutplane(i);
		
		//TODO: Error checking on cutplanes[i].tex
		glBindTexture(GL_TEXTURE_2D, cutplanes[i].tex);
		
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(cutplanes[i].X0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(cutplanes[i].X1);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(cutplanes[i].X2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(cutplanes[i].X3);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}
	
	glDisable(GL_TEXTURE_2D);
}

void cv_build_projection_r()
{
	int i,j,k,n;
	int nx[3];
	int ng, sx, sy, sz, nm, N;
	double x,y,z,r,phi;
	
	nx[0] = cow_domain_getsize(dom, 0);
	nx[1] = cow_domain_getsize(dom, 1);
	nx[2] = cow_domain_getsize(dom, 2);
	ng = cow_domain_getguard(dom);
	sx = cow_dfield_getstride(dfield, 0);
	sy = cow_dfield_getstride(dfield, 1);
	sz = cow_dfield_getstride(dfield, 2);
	nm = cow_dfield_getnmembers(dfield);
	double *raw_data = cow_dfield_getdatabuffer(dfield);
	
	N = nx[0]*nx[1]*nx[2];
	projection_r.num = N;
	projection_r.x = (GLfloat *) malloc(N * sizeof(GLfloat));
	projection_r.y = (GLfloat *) malloc(N * sizeof(GLfloat));
	
	x = cow_domain_positionatindex(dom, 0, ng);
	y = cow_domain_positionatindex(dom, 1, ng);
	z = cow_domain_positionatindex(dom, 2, ng);
	r = x*x + y*y + z*z;
	
	double rmin = r;
	double rmax = r;
	double phimin = raw_data[sx*ng+sy*ng+sz*ng+mem];
	double phimax = raw_data[sx*ng+sy*ng+sz*ng+mem];
	
	n = 0;
	for(i=ng; i<nx[0]+ng; i++)
	{
		x = cow_domain_positionatindex(dom, 0, i);
		for(j=ng; j<nx[1]+ng; j++)
		{
			y = cow_domain_positionatindex(dom, 1, j);
			for(k=ng; k<nx[2]+ng; k++)
			{
				z = cow_domain_positionatindex(dom, 2, k);
				r = sqrt(x*x + y*y + z*z);
				phi = raw_data[sx*i+sy*j+sz*k+mem];
				projection_r.x[n] = (GLfloat) r;
				projection_r.y[n] = (GLfloat) phi;
				n++;
				
				if(r < rmin)
					rmin = r;
				if(r > rmax)
					rmax = r;
				if(phi < phimin)
					phimin = phi;
				if(phi > phimax)
					phimax = phi;
			}
		}
	}
	
	projection_r.xmin = (GLfloat) rmin;
	projection_r.xmax = (GLfloat) rmax;
	projection_r.ymin = (GLfloat) phimin;
	projection_r.ymax = (GLfloat) phimax;
	
	projection_r.X0[0] = -1.0f;
	projection_r.X0[1] = -1.0f;
	projection_r.X0[2] =  0.0f;
	projection_r.X1[0] =  1.0f;
	projection_r.X1[1] = -1.0f;
	projection_r.X1[2] =  0.0f;
	projection_r.X2[0] =  1.0f;
	projection_r.X2[1] =  1.0f;
	projection_r.X2[2] =  0.0f;
	projection_r.X3[0] = -1.0f;
	projection_r.X3[1] =  1.0f;
	projection_r.X3[2] =  0.0f;
	
	
	for(n=0; n<N; n++)
	{
		projection_r.x[n] = (projection_r.x[n] - projection_r.xmin) 
								/ (projection_r.xmax - projection_r.xmin);
		projection_r.y[n] = (projection_r.y[n] - projection_r.ymin) 
								/ (projection_r.ymax - projection_r.ymin);
	}
	
	projection_r.built = 1;	
}

void cv_draw_projection()
{
	int n;
	GLfloat xlo, xhi, ylo, yhi;
	
	if(!projection_r.built)
		cv_build_projection_r();
	
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3fv(projection_r.X0);
	glVertex3fv(projection_r.X1);
	glVertex3fv(projection_r.X2);
	glVertex3fv(projection_r.X3);
	glEnd();
	
	xlo = projection_r.X0[0];
	xhi = projection_r.X1[0];
	ylo = projection_r.X0[1];
	yhi = projection_r.X3[1];
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for(n = 0; n < projection_r.num; n++)
		glVertex3f((xhi-xlo)*projection_r.x[n]+xlo, (yhi-ylo)*projection_r.y[n]+ylo, 0.01f);
	glEnd();
}

void cv_cmap(double val, int cmap, GLfloat *rrr, GLfloat *ggg, GLfloat *bbb)
{
	if(val < 0.0)
		cv_message("val underbounds");
	if(val > 1.0)
		cv_message("val overbounds");
	
	int num_cmaps = 4;
	cmap = cmap % num_cmaps;
	
	if(cmap == 0)
	{
		*rrr = (GLfloat) val;
		*ggg = 0.0f;
		*bbb = 0.0f;
	}
	
	else if(cmap == 1)
	{
		*rrr = 0.0f;
		*ggg = (GLfloat) val;
		*bbb = 0.0f;
	}
	
	else if(cmap == 2)
	{
		*rrr = 0.0f;
		*ggg = 0.0f;
		*bbb = (GLfloat) val;
	}
	
	else if(cmap == 3)
	{
		if(val < 0.1)
		{
			*bbb = 4.0*(val+0.15);
			*ggg = 0.0;
			*rrr = 0.0;
		}
		else if (val < 0.35)
		{
			*bbb = 1.0;
			*ggg = 4.0*(val-0.1);
			*rrr = 0.0;
		}
		else if (val < 0.6)
		{
			*bbb = 4.0*(0.6-val);
			*ggg = 1.0;
			*rrr = 4.0*(val-0.35);
		}
		else if (val < 0.85)
		{
			*bbb = 0.0;
			*ggg = 4.0*(0.85-val);
			*rrr = 1.0;
		}
		else
		{
			*bbb = 0.0;
			*ggg = 0.0;
			*rrr = 4.0*(1.1-val);
		}

	}
	
	else
	{
		*rrr = 0.0f;
		*ggg = 0.0f;
		*bbb = 0.0f;
	}
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
	
	cow_domain_setguard(dom, 0);
	cow_domain_setextent(dom, 0, -0.5, 0.5);
	cow_domain_setextent(dom, 1, -0.5, 0.5);
	cow_domain_setextent(dom, 2, -0.5, 0.5);
	cow_domain_commit(dom);
	
	cow_dfield_setname(dfield, "phi");
	cow_dfield_addmember(dfield, "phi");
	cow_dfield_addmember(dfield, "phiv");
	cow_dfield_setdomain(dfield, dom);
	cow_dfield_commit(dfield);
	
	cv_message("Reading data file.");
	
	cow_dfield_read(dfield, filename);
	cow_dfield_syncguard(dfield);
	
	cv_init();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	window = cv_create_window(window_name, 0, 0, init_width, init_height);
	glutMainLoop();

	return 1;
}
