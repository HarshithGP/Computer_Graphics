#include<GL/glut.h>
typedef GLfloat point[3];
point v[4] = { { 0, 0, 0 }, { 500, 0, 0 }, { 250, 500, 100 }, { 250, 200, 100 } };

void  triangle(point a, point b, point c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void tetra(point a, point b, point c, point d)
{
	glColor3f(1, 0, 0);
	triangle(a, b, c);

	glColor3f(0, 1, 0);
	triangle(a, b, d);

	glColor3f(0, 0, 1);
	triangle(a, c, d);

	glColor3f(1, 1, 0);
	triangle(b, d, c);
}

void divide_tetra(point a, point b, point c, point d, int m)
{
	int j;
	GLfloat mid[6][3];

	if (m > 0)
	{
		for (j = 0; j < 3; j++)
		{
			mid[0][j] = (a[j] + b[j]) / 2;
			mid[1][j] = (c[j] + b[j]) / 2;
			mid[2][j] = (a[j] + c[j]) / 2;
			mid[3][j] = (a[j] + d[j]) / 2;
			mid[4][j] = (d[j] + b[j]) / 2;
			mid[5][j] = (c[j] + d[j]) / 2;
		}

		divide_tetra(a, mid[0], mid[2], mid[3], m - 1);
		divide_tetra(mid[0], b, mid[1], mid[4], m - 1);
		divide_tetra(mid[2], mid[1], c, mid[5], m - 1);
		divide_tetra(mid[3], mid[4], mid[5], d, m - 1);
	}
	else
		tetra(a, b, c, d);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0], v[1], v[2], v[3], 2);
	glEnd();
	glFlush();
}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-750, 750, -750, 750, -750, 750);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutCreateWindow("Gasket");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}