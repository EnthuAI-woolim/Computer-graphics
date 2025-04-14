#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cf) 원래 SetupRC에 있었음. 설정이 반영되지 않는 것을 방지

	glClear(GL_COLOR_BUFFER_BIT); // 배경색으로 초기화(SetupRC에서 배경색 지정했음)

	// cf) default 좌표계는 ModelView이다.(object 좌표계)

	// 1. 
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(0, 0, 500, 500);
	//glOrtho(0, 500, 0, 500, 1, -1);
	//

	//glMatrixMode(GL_MODELVIEW);		
	//glLoadIdentity();				

	//glDisable(GL_LIGHTING); // cf) glColor3f 무시 방지를 이해

	//glColor3f(1.0f, 0.0f, 0.0f);
	//glRectf(250.0f, 250.0f, 375.0f, 375.0f);

	// 2.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 250, 500);
	glOrtho(-1, 1, -1, 1, 1, -1);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING); // cf) glColor3f 무시 방지를 이해

	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-0.25f, 0.25f, 0.25f, -0.25f);

	glFlush(); 
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Simple");

	glutDisplayFunc(RenderScene); // 화면 출력 함수(RenderScene) 등록만
	SetupRC();	// 즉시 실행돼서 색깔 지정

	glutMainLoop(); // OpenGL이 이 함수를 통해 RenderScene함수가 실행되면서 처음 화면을 그리게 됨
	return 0;
}