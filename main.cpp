#include <iostream>
#include <GL/glut.h>
#include <GLKit/GLKMatrix4.h>

using namespace std;

void handleKeypress(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// @deprecated
    // gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);

    GLKMatrix4 perspective = GLKMatrix4MakePerspective(45.0, (float)w / (float)h, 1.0f, 200.0f);
    glLoadMatrixf(perspective.m);
}

float _angle = -70.0f;

void drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -8.0f);

	//Add ambient light
	GLfloat ambientColor[] = { 0.0f, 0.0f, 0.0f, 0.5f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 0.9f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 0.9f }; //Color (0.5, 0.2, 0.2)
														//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);



	glRotatef(_angle, 0.0f, 1.0f, 0.0f);

	//Set the color here
	glColor3f(1.0f, 1.0f, 0.0f);
	
	//Front
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -0.25f, -0.5f);
	glVertex3f(-1.5f, 0.25f, -0.5f);
	glVertex3f(1.5f, 0.25f, -0.5f);
	glVertex3f(1.5f, -0.25f, -0.5f);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.5f, -0.25f, -0.5f);
	glVertex3f(1.5f, 0.25f, -0.5f);
	glVertex3f(1.5f, 0.25f, 0.5f);
	glVertex3f(1.5f, -0.25f, 0.5f);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -0.25f, 0.5f);
	glVertex3f(1.5f, 0.25f, 0.5f);
	glVertex3f(-1.5f, 0.25f, 0.5f);
	glVertex3f(-1.5f, -0.25f, 0.5f);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.5f, -0.25f, 0.5f);
	glVertex3f(-1.5f, 0.25f, 0.5f);
	glVertex3f(-1.5f, 0.25, -0.5f);
	glVertex3f(-1.5f, -0.25f, -0.5f);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.5f, 0.25f, 0.5f);
	glVertex3f(1.5f, 0.25f, -0.5f);
	glVertex3f(-1.5f, 0.25f, -0.5f);
	glVertex3f(-1.5f, 0.25f, 0.5f);
	glEnd();


    glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.5f, -0.25f, -0.5f);
	glVertex3f(1.5f, -0.25f, 0.5f);
	glVertex3f(-1.5f, -0.25f, 0.5f);
	glVertex3f(-1.5f, -0.25f, -0.5f);
	glEnd();

	glTranslatef(-1.5f, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glutSolidSphere(0.8f, 300, 300); // GLUT solid sphere

	glTranslatef(3, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glutSolidSphere(0.8f, 300, 300);
	
	glPopMatrix();

	glutSwapBuffers();
	
}

double speed;
void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(static_cast<unsigned int>(1000 / speed), update, 0);
}

int main(int argc, char** argv) {
	cout << "Input speed:" << endl;
	cin >> speed;

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	glutCreateWindow("3D gauntlet");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	//Add a timer
	glutTimerFunc(static_cast<unsigned int>(1000 / speed), update, 0);

	glutMainLoop();
}