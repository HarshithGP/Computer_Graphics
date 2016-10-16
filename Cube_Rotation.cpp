#include<GL/glut.h>
GLfloat vertices[8][3] = { { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 }, { 1, -1, -1 }, { -1, -1, 1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, -1, 1 } };
GLfloat theta[3] = { 0, 0, 0 };
GLint axis = 2;

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{
	glColor3f(1, 0, 0);
	polygon(0, 3, 2, 1);
	glColor3f(0, 0, 1);
	polygon(1, 2, 6, 5);
	glColor3f(0, 1, 0);
	polygon(2, 3, 7, 6);
	glColor3f(1, 1, 0);
	polygon(4, 5, 6, 7);
	glColor3f(1, 0, 1);
	polygon(0, 1, 5, 4);
	glColor3f(0, 1, 1);
	polygon(0, 4, 7, 3);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	colorcube();
	
	glutSwapBuffers();
	glFlush();
	
}

void spincube()
{
	theta[axis] += 0.00001;
	if (theta[axis] > 360)
		theta[axis] = 0;

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		axis = 0;
	if (button == GLUT_MIDDLE_BUTTON&&state == GLUT_DOWN)
		axis = 1;
	if (button == GLUT_RIGHT_BUTTON&&state == GLUT_DOWN)
		axis = 2;
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutCreateWindow("Cube Rotation");
	
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(spincube);
	glutDisplayFunc(display);
	
	glEnable(GL_DEPTH_TEST);
	

	glutMainLoop();
}