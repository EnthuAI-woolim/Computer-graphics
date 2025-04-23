﻿#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GL_PI 3.1415f

using namespace std;

void glPointSize(GLfloat s);

void RenderScene(void) {
    cout << "RenderScene" << endl;

    GLfloat x, y, z, angle;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotated(45.0f, 1.0f, 0.0f, 0.0f);
    glRotated(45.0f, 0.0f, 1.0f, 0.0f);

    glPointSize(7.0f);
    glBegin(GL_POINTS);
    z = -50.0f;
    for (angle = 0.0f; angle <= (2.0f * GL_PI * 3); angle += 0.1f) {
        if (angle == 0.0f) {
            glColor3f(0.0f, 0.0f, 1.0f);
        }
        else {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);
        glVertex3d(x, y, z);
        z += 0.5f;
    }
    cout << "z = " << z << endl;
    glEnd();
    glPopMatrix();

    glFlush();
}


void SetupRC(void) {
    cout << "SetupRC" << endl;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 화면을 어떤색으로 지울지 결정
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
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 100);
    }
    else {
        // 가로가 더 길면 x축 확장
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100, 100);
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

/*
세로가 더 길면 y축 확장
카메라는 기본적으로 z=0에서 -z축으로 바라보기 때문에,
z의 매개변수를 (nearZ, forZ) = (1, 100)으로 하면
실제 좌표는 (-1, -100)이 되고, 이 안의 모델을 볼 수 있음
glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 0); => z가 100에서 0사이의 좌표값 안의 모델을 보여줌
glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, 0, 100);  => z가 0에서 -100사이의 좌표값 안의 모델을 보여줌
*/

/*
glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -50, 50);
이렇게 하면 점들이 다 안보이는 이유는
glVertex3d(x, y, z);에서 z값이 -50 ~ 50 위치에 찍힌다해도,
glRotated();를 통해 그려질 좌표계를 회전시켰기 때문에
실제 z값은 -50보다 더 작어졌거나, 실제 z값보다 더 커졌기 때문이다.
*/

/*
## glBegin/​glEnd 허용 리스트

OpenGL 명세상 glBegin() 안에서는
- glVertex*()
- glColor*()
- glTexCoord*()
- glNormal*()
등 버텍스 관련 속성 설정 함수만 호출할 수 있습니다.

반면, glPointSize, glEnable, glMatrixMode 같은 상태 설정(state setting) 함수는 금지되어 있죠.
*/