/*13331321 殷明旺*/
#include "GL/glut.h"
#include "iostream"
using namespace std;
int gd = 0, zd = 0;
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 2, 6);
	glFrustum(-4, 4, -4, 4, 0, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void processNormalKeys(unsigned char key, int x, int y){
	if (key == 'y') {
		gd = (gd + 10) % 360;  //正方向公转
	}
	if (key == 'd') {
		zd = (zd + 10) % 360;  // 正方向自转
	}
	if ( key == 'Y') {
		gd = (gd - 10) % 360;//反方向公转
	}
	if ( key == 'D') {    
		zd = (zd - 10) % 360;  // 反方向自转
	}
   glutPostRedisplay();   // 重绘窗口
}
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glShadeModel(GL_FLAT);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix(); 
	glutWireSphere(1.5f, 18, 18);
	glRotatef(gd, 0.0, 1.0, 0.0);   //公转
	glTranslatef(2.5, 0.0, 0.0);
	glRotatef(zd, 0.0, 1.0, 0.0);  //自转
	glutWireSphere(0.3f, 12, 12);
	glPopMatrix();
	glutSwapBuffers();  //双缓冲
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	myInit();
	glutReshapeFunc(reshape);
	glutDisplayFunc(&display);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
	return 0;

}