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
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ȭ���� ������� ������ ����
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
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, 1.0, -1.0);
    }
    else {
        // ���ΰ� �� ��� x�� Ȯ��
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

    // [��ü ���� �� ������] ���� ����, ��ġ, ���� ���� �����ϰ� ȭ�鿡 �׸��� �Լ� ���
    glutDisplayFunc(RenderScene);

    // [��� �� ���� ����] â ũ�� ���� �� ȣ��Ǿ� �þ߰��� ������ ���� ���� ��� �� ����Ʈ ����
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}
