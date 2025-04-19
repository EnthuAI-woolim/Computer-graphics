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

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glPointSize(7.0f);

    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 50.0f, 0.0f);
    glEnd();

    glFlush();
}


void SetupRC(void) {
    cout << "SetupRC" << endl;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // ȭ���� ������� ������ ����
}

void ChangeSize(GLsizei w, GLsizei h) {
    cout << "w = " << w << " h = " << h << endl;
    cout << "ChangeSize" << endl;

    GLint wSize = 100;
    GLfloat aspectRatio;

    // 0���� ������ ���� ����
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        // ���ΰ� �� ��� y�� Ȯ��
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 0);
    }
    else {
        // ���ΰ� �� ��� x�� Ȯ��
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100, 0);
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

    // [��ü ���� �� ������] ���� ����, ��ġ, ���� ���� �����ϰ� ȭ�鿡 �׸��� �Լ� ���
    glutDisplayFunc(RenderScene);

    // [��� �� ���� ����] â ũ�� ���� �� ȣ��Ǿ� �þ߰��� ������ ���� ���� ��� �� ����Ʈ ����
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

// 2 * PI = 360��