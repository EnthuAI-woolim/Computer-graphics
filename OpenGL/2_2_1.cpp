#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT);

	// 다음에 그릴 도형의 색상을 설정(R, G, B)
	// 이제부터 그리는 거 전부 빨강으로 칠할거야!
	glColor3f(1.0f, 0.0f, 0.0f);

	// 사각형 그리는 함수(x1, y1, x2, y2) -> 대각선 방향의 두 꼭짓점
	// 좌표계 설정이 없다면, 일반적으로 직교 투영으로 [-1, 1] 범위 내에서 작동
	glRectf(-0.25f, 0.25f, 0.25f, -0.25f);

	glFlush(); // 지금까지 큐에 쌓인 명령들, 당장 실행해!
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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