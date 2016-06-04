/*13331321 殷明旺*/
#include<GL/glut.h>
GLfloat vertices[][3] = { //定义立方体的八个顶点
	{ 1.0, -1.0, -1.0 },
	{ 1.0, -1.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, -1.0 },
	{ -1.0, -1.0, -1.0 },
	{ -1.0, -1.0, 1.0 },
	{ -1.0, 1.0, 1.0 },
	{ -1.0, 1.0, -1.0 } 
};
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //设置背景颜色为亮白
	glMatrixMode(GL_PROJECTION); //设置合适的矩形
	glLoadIdentity();
}
void CubePlane(int a, int b, int c, int d)
{                                      //绘制平面，由四个顶点确定
	glBegin(GL_QUADS);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void Draw_Cube()
{
	CubePlane(0, 3, 2, 1);
	CubePlane(1, 2, 6, 5);
	CubePlane(2, 3, 7, 6);
	CubePlane(3, 0, 4, 7);
	CubePlane(4, 5, 6, 7);
	CubePlane(5, 4, 0, 1);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotated(30, 1, 0, 1);
	glPushMatrix();            //开始压栈
	glColor3f(0, 0, 0);
	glutWireCube(2.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	//glutSolidCube(2.0);  //可以直接用来绘制填充好的立方体
	Draw_Cube();
	glPopMatrix();      //出栈
	glutSwapBuffers(); //双缓冲交换输出图像
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);  //进行透视投影
	glLoadIdentity();
	gluPerspective(60, 0.8, 2, 6);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//视角
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("PerspectiveCube");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9, 0.9, 0.9, 1.0f);
	Init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;

}