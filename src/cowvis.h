#include "cow.h"

#define cv_message(msg) fprintf(stdout, "[cowvis] %s: %s\n", __FUNCTION__, msg);
#define cv_error(msg) fprintf(stderr, "[ERROR] %s: %s\n", __FUNCTION__, msg);

//Callback Functions
void InitGL(int width, int height);
void ReshapeFunc(int width, int height);
void DisplayFunc();
void KeyboardFunc(unsigned char key, int x, int y);
void SpecialFunc(int key, int x, int y);

//Everything Else
int cv_create_window(char *title, int x, int y, int width, int height);
void cv_init_gl(int width, int height);
void cv_exit();