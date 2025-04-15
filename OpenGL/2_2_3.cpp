#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


void RenderScene(void) {
    cout << "RenderScene" << endl;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-25.0f, 25.0f, 25.0f, -25.0f);

    glFlush();
}


void SetupRC(void) {
    cout << "SetupRC" << endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 화면을 어떤색으로 지울지 결정
}

void ChangeSize(GLsizei w, GLsizei h) {
    cout << "w = " << w << " h = " << h << endl;
    cout << "ChangeSize" << endl;

    GLint wSize = 100;
    GLfloat aspectRatio;

    // 0으로 나누는 오류 방지
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        // 세로가 더 길면 y축 확장
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, 1.0, -1.0);
    }
    else {
        // 가로가 더 길면 x축 확장
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, 1.0, -1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("simple");

    SetupRC();

    // [객체 설정 및 렌더링] 도형 색상, 위치, 형태 등을 설정하고 화면에 그리는 함수 등록
    glutDisplayFunc(RenderScene);

    // [배경 및 투영 설정] 창 크기 변경 시 호출되어 시야각과 비율에 맞춰 투영 행렬 및 뷰포트 설정
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}
