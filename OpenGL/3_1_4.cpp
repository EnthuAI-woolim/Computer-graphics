#define GL_SILENCE_DEPRECATION

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
    GLfloat sizes[2], step, point;

    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glRotated(45.0f, 1.0f, 0.0f, 0.0f);
    glRotated(45.0f, 0.0f, 1.0f, 0.0f);

    point = sizes[0];
    z = -50.0f;
    for (angle = 0.0f; angle <= (2.0f * GL_PI * 3); angle += 0.1f) {
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);

        glPointSize(point);

        glBegin(GL_POINTS);
        glVertex3d(x, y, z);
        glEnd();

        z += 0.5f;
        point += step;
    }

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
RenderScene함수 설명

void RenderScene(void) {
    cout << "RenderScene" << endl; // 디버깅용 출력: 함수 호출 여부 확인

    // 점의 좌표와 회전 각도, 점 크기 관련 변수 선언
    GLfloat x, y, z, angle;
    GLfloat sizes[2], step, point;

    // 시스템에서 지원하는 점 크기의 최소/최대 값과 증가 단위를 얻어옴
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);         // sizes[0]: 최소, sizes[1]: 최대
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);   // 점 크기를 증가시킬 때의 최소 단위

    // 화면 초기화 (이전에 그려진 모든 색상 버퍼 내용 제거)
    glClear(GL_COLOR_BUFFER_BIT);

    // 점의 기본 색상 설정 (빨간색)
    glColor3f(1.0f, 0.0f, 0.0f);

    // 모델뷰 행렬 스택 저장 (현재 좌표계 상태 저장)
    glPushMatrix();

    // 좌표계를 X축 기준으로 45도 회전
    glRotated(45.0f, 1.0f, 0.0f, 0.0f);

    // 좌표계를 Y축 기준으로 45도 회전
    glRotated(45.0f, 0.0f, 1.0f, 0.0f);

    // 점 크기 초기값 설정 (최소 크기부터 시작)
    point = sizes[0];

    // 나선형 그리기 시작: z축을 따라 증가하면서 점을 배치
    z = -50.0f;

    for (angle = 0.0f; angle <= (2.0f * GL_PI * 3); angle += 0.1f) {
        // x, y는 원 궤도 따라 회전하면서 계산
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);

        // 현재 점의 크기를 설정 (glBegin 전에 반드시 호출해야 함)
        glPointSize(point);

        // 점 하나 그리기 시작
        glBegin(GL_POINTS);
        glVertex3d(x, y, z); // 3차원 좌표계에서 점 하나 출력
        glEnd();

        // z값을 조금씩 증가시켜서 나선처럼 만듦
        z += 0.5f;

        // 점 크기를 step만큼 증가
        point += step;

        // 최대 점 크기를 넘으면 다시 최소로 초기화 (순환)
        if (point > sizes[1])
            point = sizes[0];
    }

    // 회전된 좌표계 복구 (glPushMatrix의 상태로 되돌림)
    glPopMatrix();

    // 명령 버퍼에 저장된 그리기 명령 즉시 실행
    glFlush();
}

*/