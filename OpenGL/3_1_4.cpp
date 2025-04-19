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
glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -50, 50);
�̷��� �ϸ� ������ �� �Ⱥ��̴� ������
glVertex3d(x, y, z);���� z���� -50 ~ 50 ��ġ�� �������ص�,
glRotated();�� ���� �׷��� ��ǥ�踦 ȸ�����ױ� ������
���� z���� -50���� �� �۾����ų�, ���� z������ �� Ŀ���� �����̴�.
*/

/*
RenderScene�Լ� ����

void RenderScene(void) {
    cout << "RenderScene" << endl; // ������ ���: �Լ� ȣ�� ���� Ȯ��

    // ���� ��ǥ�� ȸ�� ����, �� ũ�� ���� ���� ����
    GLfloat x, y, z, angle;
    GLfloat sizes[2], step, point;

    // �ý��ۿ��� �����ϴ� �� ũ���� �ּ�/�ִ� ���� ���� ������ ����
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);         // sizes[0]: �ּ�, sizes[1]: �ִ�
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);   // �� ũ�⸦ ������ų ���� �ּ� ����

    // ȭ�� �ʱ�ȭ (������ �׷��� ��� ���� ���� ���� ����)
    glClear(GL_COLOR_BUFFER_BIT);

    // ���� �⺻ ���� ���� (������)
    glColor3f(1.0f, 0.0f, 0.0f);

    // �𵨺� ��� ���� ���� (���� ��ǥ�� ���� ����)
    glPushMatrix();

    // ��ǥ�踦 X�� �������� 45�� ȸ��
    glRotated(45.0f, 1.0f, 0.0f, 0.0f);

    // ��ǥ�踦 Y�� �������� 45�� ȸ��
    glRotated(45.0f, 0.0f, 1.0f, 0.0f);

    // �� ũ�� �ʱⰪ ���� (�ּ� ũ����� ����)
    point = sizes[0];

    // ������ �׸��� ����: z���� ���� �����ϸ鼭 ���� ��ġ
    z = -50.0f;

    for (angle = 0.0f; angle <= (2.0f * GL_PI * 3); angle += 0.1f) {
        // x, y�� �� �˵� ���� ȸ���ϸ鼭 ���
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);

        // ���� ���� ũ�⸦ ���� (glBegin ���� �ݵ�� ȣ���ؾ� ��)
        glPointSize(point);

        // �� �ϳ� �׸��� ����
        glBegin(GL_POINTS);
        glVertex3d(x, y, z); // 3���� ��ǥ�迡�� �� �ϳ� ���
        glEnd();

        // z���� ���ݾ� �������Ѽ� ����ó�� ����
        z += 0.5f;

        // �� ũ�⸦ step��ŭ ����
        point += step;

        // �ִ� �� ũ�⸦ ������ �ٽ� �ּҷ� �ʱ�ȭ (��ȯ)
        if (point > sizes[1])
            point = sizes[0];
    }

    // ȸ���� ��ǥ�� ���� (glPushMatrix�� ���·� �ǵ���)
    glPopMatrix();

    // ��� ���ۿ� ����� �׸��� ��� ��� ����
    glFlush();
}

*/