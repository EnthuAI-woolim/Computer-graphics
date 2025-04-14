#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

// 렌더링 함수
void RenderScene(void) {
    std::cout << "RenderScene" << std::endl;

    glClear(GL_COLOR_BUFFER_BIT);  // 화면 지우기

    // 단일 버퍼 모드에서는 glFlush(), 더블 버퍼는 glutSwapBuffers()
    glutSwapBuffers(); // 현재 버퍼 보여주기
}

// 초기 설정
void SetupRC(void) {
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // 파란 배경
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ← 더블 버퍼 사용
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
    return 0;
}
