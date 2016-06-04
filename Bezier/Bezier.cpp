/*13331321 殷明旺*/
#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
using namespace std;
int numpoint = 0; //控制点的数量
class point{
private:
	double x;
	double y;
public:
	point() {
		x = 0;
		y = 0;
	}
	/*获取x*/
	double getx() {
		return x;
	}
	/*获取y*/
	double gety() {
	   return y;
	}
	/*设置点的坐标*/
	void setpoint(double x1, double y1) {
		x = x1;
		y = y1;
	}
};
point points[4];//四个控制点
void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640, 0.0, 480.0);
}
/*画点*/
void drawpoint(point p) {
	glColor3f(1.0f, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2d(p.getx(), p.gety());
	glEnd();
	glFlush();
}
/*画线*/
void drawline(point p1, point p2) {
	glBegin(GL_LINES);
	glVertex2d(p1.getx(), p1.gety());
	glVertex2d(p2.getx(), p2.gety());
	glEnd();
	glFlush();
}
/*绘制Bezier曲线*/
void drawBezier(point p1, point p2, point p3, point p4) {
	double x = p1.getx();
	double y = p1.gety();
	for (double t = 0.0; t <= 1.0; t += 0.001) {
		point firstpoint, secondpoint;
		firstpoint.setpoint(x, y);
		x = pow(1 - t, 3)*p1.getx() + 3 * p2.getx()*t*pow(1 - t, 2) + 3 * p3.getx()*pow(t, 2)*(1 - t) + p4.getx()*pow(t, 3);
		y = pow(1 - t, 3)*p1.gety() + 3 * p2.gety()*t*pow(1 - t, 2) + 3 * p3.gety()*pow(t, 2)*(1 - t) + p4.gety()*pow(t, 3);
		secondpoint.setpoint(x, y);
		drawline(firstpoint, secondpoint);
	}
}
void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) { //如果鼠标被按下
		if (button == GLUT_LEFT_BUTTON) { //如果按下的是鼠标左键
			points[numpoint].setpoint(x, 480-y);
			drawpoint(points[numpoint]);
			numpoint++;
			if (numpoint == 4) {
				glColor3f(1.0, 1.0, 1.0);
				drawline(points[0], points[1]);
				drawline(points[1], points[2]);
				drawline(points[2], points[3]);
				drawBezier(points[0], points[1], points[2], points[3]);
				numpoint = 0;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON) { //如果按下的是鼠标右键
			glClear(GL_COLOR_BUFFER_BIT); //清空缓冲区
			numpoint = 0;
			glFlush();
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
int main(int argc, char * agrv[])
{
	glutInit(&argc, agrv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Bezier Curve");
	cout << "点击鼠标左键绘制Bezier曲线，点击鼠标右键清空窗口" << endl;
	glutMouseFunc(mouse);
	glutDisplayFunc(&display);
	myInit();
	glutMainLoop();
	return 0;
}