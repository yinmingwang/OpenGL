/*13331321 殷明旺*/
#include "iostream"
#include "GL/glut.h"
using namespace std;
void myInit(void) 
{
	//定义光照属性
	GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1.0 };//环境光
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//漫射光
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//镜面光
	GLfloat light_position0[] = { 1.0, 1.0, 1.0, 0.0 };//光源位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); //设置环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //设置漫射光
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //设置镜面反射
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //设置光照位置
	//定义材质属性 
	GLfloat mat_ambient[] = { 0.12, 0.12, 0.12, 1.0};
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0};
	GLfloat mat_shininess[] = { 30.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //茶壶的前面采用环境反射
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //茶壶的前面采用漫反射
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//茶壶的前面采用镜面反射
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//茶壶前边的镜面指数

	glEnable(GL_LIGHTING);//开启光照模式
	glEnable(GL_LIGHT0); //开启第0号光源
	glEnable(GL_DEPTH_TEST);//启用深度测试
}
void reshape(int w, int h)
{
	//采用透视投影
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1.0);//往Z轴反方向平移
	glutSolidTeapot(1);//绘制茶壶
	glPopMatrix();
	glutSwapBuffers();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Teapot");
	myInit();
	glutReshapeFunc(reshape);
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;

}