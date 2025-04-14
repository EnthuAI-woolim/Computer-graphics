#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cf) 원래 SetupRC에 있었음. 설정이 반영되지 않는 것을 방지

	glClear(GL_COLOR_BUFFER_BIT); // 배경색으로 초기화(SetupRC에서 배경색 지정했음)

	// default 좌표계는 ModelView이다.(object 좌표계)

	// projection 좌표계로 이동(카메라 좌표계)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 640, 480);
	glOrtho(1, -1, 1, -1, 1, -1); // 뷰포트 안에서 제일왼쪽: 1, 제일오른쪽: -1, 제일밑: 1, 제일위: -1
	// 원래 => glOrtho(-1, 1, -1, 1, 1, -1)
	// 설명
	// : 아래 glRectf함수에서대로라면 1사분면에 빨간사각형이 그려져야됌
	// 그걸 3사분면에 오게하려면, 좌표계를 좌우반전 그리고 상하반전 시켜줘야됨.
	// 그러면 x값이 양수이면 왼쪽으로, 음수이면 오른쪽으로 감 / y값도 마찬가지임

	// object 좌표계로 이동(ModelView)
	glMatrixMode(GL_MODELVIEW);		
	glLoadIdentity();				

	glDisable(GL_LIGHTING); // cf) glColor3f 무시 방지를 이해

	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(0.0f, 240.0f, 320.0f, 0.0f);

	glFlush(); 
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Simple");

	glutDisplayFunc(RenderScene); // 화면 출력 함수(RenderScene) 등록만
	SetupRC();	// 즉시 실행돼서 색깔 지정

	glutMainLoop(); // OpenGL이 이 함수를 통해 RenderScene함수가 실행되면서 처음 화면을 그리게 됨
	return 0;
}