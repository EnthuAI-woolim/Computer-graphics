#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cf) 원래 SetupRC에 있었음. 설정이 반영되지 않는 것을 방지

	glClear(GL_COLOR_BUFFER_BIT); // 배경색으로 초기화(SetupRC에서 배경색 지정했음)

	// default 좌표계는 ModelView이다.(object 좌표계)

	// projection 좌표계로 이동(카메라 좌표계)
	glMatrixMode(GL_PROJECTION);	// 배경설정 - 투영 행렬(시야 설정용 매트릭스)
	glLoadIdentity();				// 좌표계 초기화 = 기존 설정을 초기화 (단위행렬로 초기화)
	glViewport(0, 0, 500, 500); // 렌더링 결과를 출력할 실제 픽셀 영역설정, 왼쪽 아래가 (0,0)
	glOrtho(-1, 1, -1, 1, 1, -1); // // 뷰포트 안에서 제일왼쪽: -1, 제일오른쪽: 1, 제일밑: -1, 제일위: 1

	// object 좌표계로 이동(ModelView)
	glMatrixMode(GL_MODELVIEW);		// 도형설정 - 모델뷰 행렬로 전환
	glLoadIdentity();				// 좌표계 초기화 = 이전 설정 초기화 → 모든 도형은 원점 기준으로 렌더링

	glDisable(GL_LIGHTING); // cf) glColor3f 무시 방지를 이해

	glColor3f(1.0f, 0.0f, 0.0f);
	// 위 glOrtho()의 좌표계 설정을 기준으로 화면의 가운데(뷰포트를 윈도우크기랑 1:1매팅해서)에 
	// 각변의 1/2크기의 정사각형 그린 것임
	glRectf(-0.25f, 0.25f, 0.25f, -0.25f);

	glFlush(); // 지금까지 큐에 쌓인 명령들, 당장 실행해!
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