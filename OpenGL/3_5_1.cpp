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

    GLfloat x, y;
    GLfloat factor = 1;
    GLfloat pattern = 0x00ff;


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glEnable(GL_LINE_STIPPLE);
    for (y = -90.0f; y <= 90.0f; y += 20.0f) {
        glLineStipple(factor, pattern);

        glBegin(GL_LINES);
        glVertex2f(-80.0f, y);
        glVertex2f(80.0f, y);
        glEnd();

        factor += 1;
    }

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
# glLineStipple(factor, pattern);

factor : ��Ʈ�� �� �ȼ��� �׸��� ����
ex) 1�̸� 1�ȼ�, 2�� 2�ȼ�

pattern : ��Ʈ����(�����ʿ��� �������� �о�ߵ�)
ex) factor: 1, patten: 0x00ff => 0000 0000 1111 1111 =>  4�ȼ� �׸���, 4�ȼ� �׸���, 4�ȼ� ����, 4�ȼ� ����
*/

/*
���ΰ� �� ��� y�� Ȯ��
ī�޶�� �⺻������ z=0���� -z������ �ٶ󺸱� ������,
z�� �Ű������� (nearZ, forZ) = (1, 100)���� �ϸ�
���� ��ǥ�� (-1, -100)�� �ǰ�, �� ���� ���� �� �� ����
glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 0); => z�� 100���� 0������ ��ǥ�� ���� ���� ������
glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, 0, 100);  => z�� 0���� -100������ ��ǥ�� ���� ���� ������
*/

/*
glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -50, 50);
�̷��� �ϸ� ������ �� �Ⱥ��̴� ������
glVertex3d(x, y, z);���� z���� -50 ~ 50 ��ġ�� �������ص�,
glRotated();�� ���� �׷��� ��ǥ�踦 ȸ�����ױ� ������
���� z���� -50���� �� �۾����ų�, ���� z������ �� Ŀ���� �����̴�.
*/