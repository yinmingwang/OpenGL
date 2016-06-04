#include <iostream>
#include <OpenMesh\Core\IO\MeshIO.hh>
#include <OpenMesh\Core\Mesh\TriMesh_ArrayKernelT.hh>
#include <GL\glut.h>
using namespace std;
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
MyMesh mesh;
int xRotate = 0;
int yRotate = 0;
float horizontaltranslen = 0.0;
float verticaltranslen = 0.0;
GLuint showFaceList, showHalfEdgeList, showPointList;
bool flag = true;
bool showFace = true;
bool showHalfEdge = false;
bool showPoint = false;
void ShowHalfEdge();
void ShowFace();
void ShowPoint();
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (flag) {
		if (w > h)
			glOrtho(-static_cast<GLdouble>(w) / h, static_cast<GLdouble>(w) / h, -1.0, 1.0, -1.0, 1.0);
		else
			glOrtho(-1.0, 1.0, -static_cast<GLdouble>(h) / w, static_cast<GLdouble>(h) / w, -1.0, 1.0);
	}
	if (!flag) {
		gluPerspective(90.0, 1.0, 1.0, 300.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 250.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void init()
{
	glClearColor(0.5, 0.8, 1.0, 0.0);
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//光照
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//光照位置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING); // 启用光源
	glEnable(GL_LIGHT0); // 启用指定光源
	ShowPoint();
	ShowHalfEdge();
	ShowFace();
}
void ShowPoint() {
	showPointList = glGenLists(1);
	glNewList(showPointList, GL_COMPILE);
	glDisable(GL_LIGHTING);
	glLineWidth(0.5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		glVertex3fv(mesh.point(*v_it).data());//每个点的坐标位置
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glEndList();
}
void ShowHalfEdge() {
	showHalfEdgeList = glGenLists(1);
	glNewList(showHalfEdgeList, GL_COMPILE);
	glDisable(GL_LIGHTING);
	glLineWidth(0.5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (MyMesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) {
		//得到每条半边的起始点和终点的位置
		glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
		glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glEndList();
}
void ShowFace() {
	showFaceList = glGenLists(1);
	glNewList(showFaceList, GL_COMPILE);
	for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
		glBegin(GL_TRIANGLES);
		for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {//循环器，迭代当前面上的所有顶点
			glNormal3fv(mesh.normal(*fv_it).data());//法向量
			glVertex3fv(mesh.point(*fv_it).data());//顶点数据
		}
		glEnd();
	}
	glEndList();
}
void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		xRotate = (xRotate - 5) % 360;
		break;
	case GLUT_KEY_DOWN:
		xRotate = (xRotate + 5) % 360;
		break;
	case GLUT_KEY_LEFT:
		yRotate = (yRotate - 5) % 360;
		break;
	case GLUT_KEY_RIGHT:
		yRotate = (yRotate + 5) % 360;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 'f' || key == 'Y') {
		showFace = true;
		showHalfEdge = false;
		showPoint = false;
	}
	if (key == 'l' || key == 'L') {
		showFace = true;
		showHalfEdge = true;
		showPoint = false;
	}
	if (key == 'h' || key == 'H') {
		showFace = false;
		showHalfEdge = true;
		showPoint = false;
	}
	if (key == 'p' || key == 'P') {
		showFace = false;
		showHalfEdge = false;
		showPoint = true;
	}
	if (key == 'd' || key == 'D') {
		if (!flag) {
			horizontaltranslen += 1;
		}
		else {
			horizontaltranslen += 0.1;
		}
	}
	if (key == 'a' || key == 'A') {
		if (!flag) {
			horizontaltranslen -= 1;
		}
		else {
			horizontaltranslen -= 0.1;
		}
	}
	if (key == 'w' || key == 'W') {
		if (!flag) {
			verticaltranslen += 1;
		}
		else {
			verticaltranslen += 0.1;
		}

	}
	if (key == 's' || key == 'S') {
		if (!flag) {
			verticaltranslen -= 1;
		}
		else {
			verticaltranslen -= 0.1;
		}
	}
	glutPostRedisplay();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (!flag) {
		glTranslatef(0.0, -20.0, -120.0);
	}
	glTranslatef(0.0, verticaltranslen, 0.0);
	glTranslatef(horizontaltranslen, 0.0, 0.0);
	glRotatef(xRotate, 1.0, 0.0, 0.0);
	glRotatef(yRotate, 0.0, 1.0, 0.0);
	if (showFace) {
		glCallList(showFaceList);
	}
	if (showHalfEdge) {
		glCallList(showHalfEdgeList);
	}
	if (showPoint) {
		glCallList(showPointList);
	}
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	mesh.request_vertex_normals(); // 添加顶点法向量到网格中
	map<int, string> filename;
	string cow = "cow.obj";
	string cactus = "cactus.ply";
	string Armadillo = "Armadillo.off";
	filename.insert(pair<int, string>(1, cow));
	filename.insert(pair<int, string>(2, cactus));
	filename.insert(pair<int, string>(3, Armadillo));
	cout << "文件对应的序号" << endl;
	cout << "1   cow.obj" << endl << "2   cactus.ply" << endl << "3   Armadillo.off" << endl;
	cout << "键盘说明：" << endl << "w或W      向上移动" << endl << "s或S      向下移动" << endl << "a或A      向左移动" << endl << "d或D      向右移动" << endl;
	cout << "Up键      向上旋转" << endl << "Down键    向下旋转" << endl << "Left键    向左旋转" << endl << "Right键   向右旋转" << endl;
	cout << "h或H   Wireframe效果" << endl << "f或F   Flat效果" << endl << "l或L   Flat lines效果" << endl << "p或P   Point效果" << endl << endl;
	cout << "请输入相应的序号选择文件（如输入1）" << endl;
	int n;
	cin >> n;
	if (n == 1 || n == 2) {
		flag = true;
	}
	else {
		flag = false;
	}
	cout << "选择的文件为：" << filename[n] << endl;
	//确保网格中有顶点法向量
	if (!mesh.has_vertex_normals())
	{
		std::cerr << "ERROR: Standard vertex property 'Normals' not available!\n";
		return 1;
	}
	//读网格
	OpenMesh::IO::Options opt;//选择器，根据输入的不同模型来选择读取器和写入器
	OpenMesh::IO::read_mesh(mesh, filename[n], opt);
	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		mesh.request_face_normals();// 利用面的法向量来更新顶点法向量
		mesh.update_normals();//更新网格法向量
		mesh.release_face_normals();//移除
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Mesh");
	init();
	glutKeyboardFunc(&keyboard);
	glutSpecialFunc(&special);
	glutReshapeFunc(&reshape);
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;
}