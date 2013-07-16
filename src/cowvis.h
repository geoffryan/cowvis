#include "cow.h"

#define cv_message(msg) fprintf(stdout, "[cowvis] %s: %s\n", __FUNCTION__, msg);
#define cv_error(msg) fprintf(stderr, "[ERROR] %s: %s\n", __FUNCTION__, msg);

//Callback Functions
void IdleFunc();
void ReshapeFunc(int width, int height);
void DisplayFunc();
void KeyboardFunc(unsigned char key, int x, int y);
void SpecialFunc(int key, int x, int y);

//Everything Else
int cv_create_window(char *title, int x, int y, int width, int height);
void cv_init_gl(int width, int height);
void cv_exit();
void cv_build_cutplanes();
void cv_wirecube(float side);
void cv_build_cutplane(int ax);
void cv_draw_cutplanes();
void cv_cmap(double val, int cmap, GLfloat *rrr, GLfloat *ggg, GLfloat *bbb);


struct cv_cutplane
{
	GLuint tex;
	int ind;
	int cmap;
	GLfloat X0[3];
	GLfloat X1[3];
	GLfloat X2[3];
	GLfloat X3[3];
};
typedef struct cv_cutplane cv_cutplane;

const struct cv_cutplane cutplane_default = {0, 0, 0, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}};