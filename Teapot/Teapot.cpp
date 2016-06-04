/*13331321 ������*/
#include "iostream"
#include "GL/glut.h"
using namespace std;
void myInit(void) 
{
	//�����������
	GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1.0 };//������
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//�����
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//�����
	GLfloat light_position0[] = { 1.0, 1.0, 1.0, 0.0 };//��Դλ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); //���û�����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //���������
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //���þ��淴��
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //���ù���λ��
	//����������� 
	GLfloat mat_ambient[] = { 0.12, 0.12, 0.12, 1.0};
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0};
	GLfloat mat_shininess[] = { 30.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //�����ǰ����û�������
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //�����ǰ�����������
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//�����ǰ����þ��淴��
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//���ǰ�ߵľ���ָ��

	glEnable(GL_LIGHTING);//��������ģʽ
	glEnable(GL_LIGHT0); //������0�Ź�Դ
	glEnable(GL_DEPTH_TEST);//������Ȳ���
}
void reshape(int w, int h)
{
	//����͸��ͶӰ
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
	glTranslatef(0.0, 0.0, -1.0);//��Z�ᷴ����ƽ��
	glutSolidTeapot(1);//���Ʋ��
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