//  ========================================================================
//  COSC363: Computer Graphics (2018);  University of Canterbury.
//
//  FILE NAME: Teapot.cpp
//  See Lab01.pdf for details
//  ========================================================================

#include <cmath>
#include <GL/freeglut.h>

float cam_hgt = 10;
float xpos = 0;


//--Draws a grid of lines on the floor plane -------------------------------
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

//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display(void)
{
	float lpos[4] = { 0., 10., 30., 1.0 };  //light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(xpos, cam_hgt, 12, 0, 0, 0, 0, 1, 0);  //Camera position and orientation

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //Set light position

	glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.
	drawFloor();

	glEnable(GL_LIGHTING);			//Enable lighting when drawing the teapot
	glColor3f(0.0, 1.0, 1.0);

	glTranslatef(0, 10, -10);

	glPushMatrix();
		glTranslatef(22.5, 1.5, 0);
		glScalef(50, 1, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 3, -5);
		glRotatef(90, 0, 1, 0);
		glTranslatef(-22.5, -1.5, 0);
		glScalef(35, 1, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 3, -5);
		glRotatef(-90, 0, 1, 0);
		glTranslatef(-22.5, -1.5, 0);
		glScalef(35, 1, 1);
		glTranslatef(50, 0, 0);
		glutSolidCube(1);
	glPopMatrix();

	glRotatef(90, 1, 0, 0);
	glPushMatrix();
		for (int i = 0; i < 4; i++) {
			glutSolidCylinder(1, 10, 100, 100);
			glutSolidSphere(1.5, 100, 100);
			glTranslatef(5, 0, 0);
		}

		glTranslatef(10, 0, 0);

		for (int i = 0; i < 4; i++) {
			glutSolidCylinder(1, 10, 100, 100);
			glutSolidSphere(1.5, 100, 100);
			glTranslatef(5, 0, 0);
		}
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		for (int i = 0; i < 8; i++) {
			glutSolidCylinder(1, 10, 100, 100);
			glutSolidSphere(1.5, 100, 100);
			glTranslatef(5, 0, 0);
		}
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(50, 0, 35);
		for (int i = 0; i < 8; i++) {
			glutSolidCylinder(1, 10, 100, 100);
			glutSolidSphere(1.5, 100, 100);
			glTranslatef(5, 0, 0);
		}
	glPopMatrix();

	glFlush();
}

//----------------------------------------------------------------------
void initialize(void)
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

void special(int key, int x, int y) {
	if (key == GLUT_KEY_UP) cam_hgt++;
	else if (key == GLUT_KEY_DOWN) cam_hgt--;
	else if (key == GLUT_KEY_LEFT) xpos--;
	else if (key == GLUT_KEY_RIGHT) xpos++;
	glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Teapot");
	initialize();
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}