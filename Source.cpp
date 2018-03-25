//  ========================================================================
//  COSC363: Computer Graphics (2018);  University of Canterbury.
//
//  FILE NAME: Skybox.cpp
//  See Lab03.pdf for details
//  ========================================================================

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 180.0;		//Camera rotation
float xlook, zlook;
float xpos = 0;
float ypos = 500;
float zpos = 0;
float cdr = 3.14159265 / 180.0;	//Conversion from degrees to radians

GLuint texId[6];

void drawFloor()
{
	glColor3f(0., 0.5, 0.);			//Floor colour

	for (int i = -50; i <= 50; i++)
	{
		glBegin(GL_LINES);			//A set of grid lines on the xz-plane
		glVertex3f(-50, -0.75, i);
		glVertex3f(50, -0.75, i);
		glVertex3f(i, -0.75, -50);
		glVertex3f(i, -0.75, 50);
		glEnd();
	}
}

void loadGLTextures()				// Load bitmaps And Convert To Textures
{
	glGenTextures(6, texId); 		// Create texture ids
									// *** left ***
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	// loadTGA("left.tga");
	loadTGA("images/negx.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** front ***
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	// loadTGA("front.tga");
	loadTGA("images/posz.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** right ***
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	// loadTGA("right.tga");
	loadTGA("images/posx.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** back***
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	// loadTGA("back.tga");
	loadTGA("images/negz.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** top ***
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	// loadTGA("top.tga");
	loadTGA("images/posy.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// *** down ***
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	// loadTGA("down.tga");
	loadTGA("images/negy.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

//========================================================================================

void skybox() {
	glEnable(GL_TEXTURE_2D);

	////////////////////// LEFT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(1, 0); glVertex3f(-1000, 0., -1000);
	glTexCoord2f(1, 1); glVertex3f(-1000, 1000., -1000);
	glTexCoord2f(0, 1); glVertex3f(-1000, 1000, 1000);
	glEnd();

	////////////////////// FRONT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1000, 0, -1000);
	glTexCoord2f(1, 0); glVertex3f(1000, 0., -1000);
	glTexCoord2f(1, 1); glVertex3f(1000, 1000, -1000);
	glTexCoord2f(0, 1); glVertex3f(-1000, 1000, -1000);
	glEnd();

	////////////////////// RIGHT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(1, 0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(1, 1); glVertex3f(1000, 1000, 1000);
	glTexCoord2f(0, 1); glVertex3f(1000, 1000, -1000);
	glEnd();


	////////////////////// REAR WALL ////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(1, 0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(1, 1); glVertex3f(-1000, 1000, 1000);
	glTexCoord2f(0, 1); glVertex3f(1000, 1000, 1000);
	glEnd();

	/////////////////////// TOP //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1, 0); glVertex3f(1000, 1000, -1000);
	glTexCoord2f(1, 1); glVertex3f(1000, 1000, 1000);
	glTexCoord2f(0, 1); glVertex3f(-1000, 1000, 1000);
	glEnd();

	/////////////////////// FLOOR //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1000, 0., 1000);
	glTexCoord2f(1, 0); glVertex3f(1000, 0., 1000);
	glTexCoord2f(1, 1); glVertex3f(1000, 0., -1000);
	glTexCoord2f(0, 1); glVertex3f(-1000, 0., -1000);
	glEnd();

}

//---------------------------------------------------------------------
void initialise(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_LIGHTING);		//Enable OpenGL states
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 1000.0);   //Camera Frustum
}

//---------------------------------------------------------------------
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	xlook = -100.0*sin(lookAngle*cdr);
	zlook = -100.0*cos(lookAngle*cdr);
	gluLookAt(xpos, ypos, zpos, xlook, 500, zlook, 0, 1, 0);  //camera rotation

	glDisable(GL_LIGHTING);
		drawFloor();
	glEnable(GL_LIGHTING);

	// skybox();

	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	glTranslatef(500, 500, 250);
	glRotatef(180, 0, 500, 0);
	glutSolidCylinder(50, 100, 10,10);
	glColor4f(1, 1, 1, 1);
	glFlush();
}

//--------------------------------------------------------------
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (lookAngle < 90) {
			lookAngle += 5;		 //Turn left
		}
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (lookAngle > -90) {
			lookAngle -= 5;   //Turn right
		}
	}
	else if (key == GLUT_KEY_UP) {
		float xrotrad, zrotrad;
		xrotrad = zlook * cdr;
		zrotrad = xlook * cdr;

		xpos += float(sin(zrotrad)) * 3;
		ypos -= float(sin(xrotrad)) * 3;
		zpos -= float(cos(zrotrad)) * 3;
	}
	else if (key == GLUT_KEY_DOWN) {
		float xrotrad, zrotrad;
		xrotrad = zlook * cdr;
		zrotrad = xlook * cdr;

		xpos -= float(sin(zrotrad)) * 3;
		ypos += float(sin(xrotrad)) * 3;
		zpos += float(cos(zrotrad)) * 3;
	}

	glutPostRedisplay();
}
//-------------------------------------------------------------------

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Sky Box");
	initialise();
	glutDisplayFunc(display);
	glutSpecialFunc(special);

	glutMainLoop();
	return 0;
}
