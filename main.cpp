/**********************************************************************************************************************/
//HW1 OpenGL Skeleton code, V1.0 for displaying simple 2D and 3D objects using OpenGL and implementing affine transformations
//You need to implement the above functionalities
//Anurag Purwar, MEC572

//The functions and the places where you may not need not make any changes are marked MNT (May Not Touch)
/**********************************************************************************************************************/

#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include "color.h"
#include "2DPoint.h"
#include <GL/glui.h> 
#include <math.h>
    
using namespace std;

int width, height;
int win_id;
GLint vp[4];


TwoDPoint m_LDownPos;
int m_LButtonDown;
TwoDPoint m_RDownPos;
int m_RButtonDown;
TwoDPoint m_MDownPos;
int m_MButtonDown;
double m_yRotate;
double m_xRotate;
double m_zRotate;
double m_transY;
double m_transX;
double m_transZ;   
/************************************************************/
// my variables
#define WIDTH 4
#define HEIGHT 4
GLfloat transM[WIDTH*HEIGHT];
GLfloat identityM[WIDTH*HEIGHT];
double m_shearX;
double m_shearY;
double m_shearZ;
bool upY, downY, leftX, rightX;
double m_shear;
/************************************************************/
void mouseFunc(int, int, int, int );
void mouseMotionFunc(int, int);
void keyboard(unsigned char, int, int);
void draw(int);
void display(void);
void reshape(int, int);
void shellmessages(void);
void init(void);

// my function
void arrowKey(int key, int x, int y);


/*The following is the display function that concerns you the most.
 I have already completed it for you. 
 So no need to change anything here, at least for now*/

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSetWindow(win_id);
    draw(GL_RENDER);
    glutSwapBuffers();
}
/////////////////////////////////////////////////////////////////////////
// New implemented function for identity matrix. 

void identityMatrix(GLfloat identityM[WIDTH*HEIGHT]){
	int n, m;
	int numberOfElements = sizeof(identityM) / sizeof(identityM[0]);
	
	for (n = 0; n < HEIGHT; n++){
		for (m = 0; m < WIDTH; m++){
			identityM[n*WIDTH + m] = (n == m);
		}
	}
	
}

// New implemented function for translation. 

void translationMatrix(GLfloat transM[WIDTH*HEIGHT], double tx, double ty, double tz){

	identityMatrix(transM);

	transM[12] = tx;
	transM[13] = ty;
	transM[14] = tz;


}
// new rotation matrix function
void rotationMatrix(GLfloat rotationM[WIDTH*HEIGHT], double angle, double x, double y, double z){
	
	identityMatrix(transM);

	double c1 = cos(angle);
	double s1 = sin(angle);


	rotationM[0] = c1 + x*x*(1 - c1);
	rotationM[1] = x*y*(1 - c1)+z*s1;
	rotationM[2] =  z*x*(1 - c1)-y*s1;
	rotationM[4] =  x*y*(1 - c1)-z*s1;
	rotationM[5] =  c1+y*y*(1 - c1);
	rotationM[6] =  z*y*(1 - c1)+x*s1;
	rotationM[8] = x*z*(1 - c1)+y*s1;
	rotationM[9] = y*z*(1 - c1)-x*s1;
	rotationM[10] = c1+z*z*(1-c1);
	

}
// new scaling matrix function
void scalingMatrix(GLfloat transM[WIDTH*HEIGHT], double sx, double sy, double sz){

	identityMatrix(transM);

	transM[0] = sx;
	transM[5] = sy;
	transM[10] = sz;

	cout << transM[0] << endl;
	cout << transM[5] << endl;
	cout << transM[10] << endl;

}
// new shear matrix function
void shearMatrix(GLfloat transM[WIDTH*HEIGHT], double d){

	identityMatrix(transM);

	transM[4] = d;
}

////////////////////////////////////////////////////////////////

/* This is the function that needs to be changed for drawing. */
void draw(int mode)
{
	
   glPushMatrix();
   translationMatrix(transM, m_transX, m_transY, m_transZ);
  // glLoadIdentity();
   glMultMatrixf(transM);
	//::glTranslated(m_transX, m_transY, m_transZ);
   rotationMatrix(transM, m_xRotate, 1.0, 0.0, 0.0);
   glMultMatrixf(transM);
   rotationMatrix(transM, m_yRotate, 0.0, 1.0, 0.0);
   glMultMatrixf(transM);
   rotationMatrix(transM, m_xRotate, 0.0, 0.0, 1.0);

   glMultMatrixf(transM);
   if (rightX || leftX){
	   scalingMatrix(transM, m_shearX, 1.0, 1.0);
	   glMultMatrixf(transM);
   }
   else if (upY || downY){
	   scalingMatrix(transM, 1.0, m_shearY, 1.0);
	   glMultMatrixf(transM);
   }
   shearMatrix(transM, m_shear);
   glMultMatrixf(transM);
   /*::glRotated(m_xRotate, 1.0, 0.0, 0.0);
	::glRotated(m_yRotate, 0.0, 1.0, 0.0);
	::glRotated(m_zRotate, 0.0, 0.0, 1.0);*/
   glMaterialfv(GL_FRONT,GL_DIFFUSE,BROWN);
   glutSolidCube(5);
   // glutSolidTeapot(5);
  glPopMatrix();
}



// When you resize/create the window, this gets called. MNT.
void reshape(int w, int h)
{
	width  = w;
	height = h;

	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glGetIntegerv(GL_VIEWPORT, vp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,1.0,0.1,3000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//OpenGL initialization function. MNT.
void init(void)
{
	glClearColor(.0, .0, .0, .0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);	
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);

}

//Light initialization function. MNT.
void setupLight(void)
{	
	float LightAmbient[]	= { 1.0f, 1.0f, 1.0f, 1.0};
	float LightDiffuse[]	= { 0.7f, 0.7f, 0.7f, 1.0f};
	float LightSpecular[]	= { 1.0f, 1.0f, 1.0f, 1.0f };
	float LightPosition[]	= { 3.0f, 3.0f, 3.0f, 1.0f };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	

	float no_mat[]={0.0f,0.0f,0.0f,1.0f};
    float mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
    float mat_ambient_color[]={0.8f,0.3f,0.7f,1.0f};
    float mat_diffuse[]={0.7f,0.7f,0.7f,1.0f};
    
    float mat_specular[]={0.7f,0.7f,0.7f,1.0f};

    float no_shininess[]={0.0};
    float low_shininess[]={5.0};
    float high_shininess[]={100.0};
    float mat_emission[]={0.2f,0.1f,0.1f,0.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission); 

}


void shellmessages(void)
{
	cout<<"\n* Left Button Click  - Rotates\n\n"
		<<"* Right Button - Pans \n\n"
		<<"* Middle Button - Zoom\n\n"
		<< "* Up/Down Right/Left arrow keys for scaling\n\n" // new comments on shell
		<< "* press d and c for shear "
		<<"* Escape key - Exit\n\n";
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize (700, 500);
   glutInitWindowPosition (50, 50);
   win_id = glutCreateWindow("HW1, MEC572");
   shellmessages();
   init();
   setupLight();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouseFunc);
   glutMotionFunc(mouseMotionFunc);
   
   glutSpecialFunc(arrowKey); // added function call back for arrow keys.
  
   glutMainLoop();

   return 0;
}


