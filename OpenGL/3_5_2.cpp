#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void glPointSize(GLfloat s);
void glLineWidth(GLfloat s);

void RenderScene(void) {
    cout << "RenderScene" << endl;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotated(45.0f, 1.0f, 0.0f, 0.0f);
    glRotated(45.0f, 0.0f, 1.0f, 0.0f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glColor3d(1.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, 0.0f, 0.0f);
    glVertex3d(90.0f, 0.0f, 0.0f);

    glVertex3d(90.0f, 0.0f, 0.0f);
    glVertex3d(85.0f, 5.0f, 0.0f);

    glVertex3d(90.0f, 0.0f, 0.0f);
    glVertex3d(85.0f, -5.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(0.0f, 1.0f, 0.0f);
    glVertex3d(0.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, 90.0f, 0.0f);

    glVertex3d(0.0f, 90.0f, 0.0f);
    glVertex3d(5.0f, 85.0f, 0.0f);

    glVertex3d(0.0f, 90.0f, 0.0f);
    glVertex3d(-5.0f, 85.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(0.0f, 0.0f, 1.0f);
    glVertex3d(0.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, 0.0f, 90.0f);

    glVertex3d(0.0f, 0.0f, 90.0f);
    glVertex3d(5.0f, 0.0f, 85.0f);

    glVertex3d(0.0f, 0.0f, 90.0f);
    glVertex3d(-5.0f, 0.0f, 85.0f);
    glEnd();


    glPopMatrix();
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
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 100);
    }
    else {
        // ���ΰ� �� ��� x�� Ȯ��
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

    // [��ü ���� �� ������] ���� ����, ��ġ, ���� ���� �����ϰ� ȭ�鿡 �׸��� �Լ� ���
    glutDisplayFunc(RenderScene);

    // [��� �� ���� ����] â ũ�� ���� �� ȣ��Ǿ� �þ߰��� ������ ���� ���� ��� �� ����Ʈ ����
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
���ΰ� �� ��� y�� Ȯ��
ī�޶�� �⺻������ z=0���� -z������ �ٶ󺸱� ������,
z�� �Ű������� (nearZ, forZ) = (1, 100)���� �ϸ�
���� ��ǥ�� (-1, -100)�� �ǰ�, �� ���� ���� �� �� ����
glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 0); => z�� 100���� 0������ ��ǥ�� ���� ���� ������
glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, 0, 100);  => z�� 0���� -100������ ��ǥ�� ���� ���� ������
*/

/*
# glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -50, 50);
�̷��� �ϸ� ������ �� �Ⱥ��̴� ������
glVertex3d(x, y, z);���� z���� -50 ~ 50 ��ġ�� �������ص�,
glRotated();�� ���� �׷��� ��ǥ�踦 ȸ�����ױ� ������
���� z���� -50���� �� �۾����ų�, ���� z������ �� Ŀ���� �����̴�.
*/