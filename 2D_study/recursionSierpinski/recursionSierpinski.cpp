#include <GL/glut.h>

// 初始三角形 
GLfloat vertexTriangle[3][2] = { { -1.0, -0.58 }, { 1.0, -0.58 }, { 0.0, 1.15 } };

int nTimes;
typedef GLfloat point2[2];

void triangle(point2 a, point2 b, point2 c)
{
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
}
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{
	/*基于顶点的数量对三角形细分*/
	GLfloat v0[2], v1[2], v2[2];
	int j;
	if (m>0)
	{
		for (j = 0; j < 2; j++) v0[j] = (a[j] + b[j]) / 2.0;
		for (j = 0; j < 2; j++) v1[j] = (a[j] + c[j]) / 2.0;
		for (j = 0; j < 2; j++) v2[j] = (b[j] + c[j]) / 2.0;
		divide_triangle(a, v0, v1, m - 1);
		divide_triangle(c, v1, v2, m - 1);
		divide_triangle(b, v2, v0, m - 1);
	}
	else
	{
		triangle(a, b, c);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_triangle(vertexTriangle[0], vertexTriangle[1], vertexTriangle[2],nTimes);
	glEnd();
	glFlush();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
}
int main(int argc, char *argv[])
{
	nTimes = 6;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sierpinski recursion 示例");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}