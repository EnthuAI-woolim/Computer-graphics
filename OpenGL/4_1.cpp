#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
using namespace std;

#define GL_PI 3.1415f
bool bCull = true;
bool bDepth = true;
GLfloat xTran = 0.0f;
GLfloat yTran = 0.0f;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;



void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        xRot -= 2.0f;
    if (key == GLUT_KEY_DOWN)
        xRot += 2.0f;
    if (key == GLUT_KEY_LEFT)
        yRot -= 2.0f;
    if (key == GLUT_KEY_RIGHT)
        yRot += 2.0f;

    if (xRot > 360.0f)
        xRot -= 360.0f;
    if (xRot < 0.0f)
        xRot += 360.0f;
    if (yRot > 360.0f)
        yRot -= 360.0f;
    if (yRot < 0.0f)
        yRot += 360.0f;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') {
        xTran -= 2.0f;
    }
    else if (key == 'd') {
        xTran += 2.0f;
    }
    else if (key == 'w') {
        yTran += 2.0f;
    }
    else if (key == 'x') {
        yTran -= 2.0f;
    }
    glutPostRedisplay();
}


void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (bCull) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if (bDepth) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ī�޶� ����(z������ -30 ������ ��, ȸ�� ��)
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
    glTranslatef(0, 0, -30.0f);
    glRotatef(30.0f, 1, 0, 0);
    glRotatef(-30.0f, 0, 1, 0);

    // �� �׸��� (�Ǽ�)
    glBegin(GL_LINES);
    glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(90, 0, 0);
    glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 90, 0);
    glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 90);
    glEnd();

    // ù ��° ť�� (�Ǽ�
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glColor3d(0, 0, 1);
    glutWireCube(10.0f);
    glDisable(GL_LINE_STIPPLE);

    // �� ��° ť�� (����)
    glPushMatrix(); // �� �Լ� ������ �ۼ��� �ڵ��� ���� ����� ����� ���ÿ� �����ؼ� �����س���
    // ���⼭���ʹ� ���� ����� ����� ���� - y������ 20�ö� ������ ť�긦 �׸�
    glTranslatef(0.0f, 20.0f, 0.0f);

    glColor3d(1, 0, 0);
    glutWireCube(10.0f);
    glPopMatrix(); // ���ÿ� ����� ����� ������ �ٽ� ���� ��ķ� �����

    //glFlush();
    glutSwapBuffers();
}


void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
}
void ChangeSize(GLsizei w, GLsizei h) {
    GLdouble nRange = 50;
    GLdouble aspectRatio;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h)
        glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange, nRange);
    else
        glOrtho(-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("simple");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(keyboard);

    SetupRC();
    glutMainLoop();
}

/*

������Ʈ�� ��ȯ
- ���� ��ǥ
���������� ��ȯ, Ư�� �̵����� ��� ������ ǥ���� �� �ְ� ���ִ� ��ǥ ǥ����

1. ��ī��Ʈ ��ǥ��
��� ���ϴ°� ��ü�� ������ �ٲ��ִ� �۾��̴�.
��� ��: Ȯ��, ȸ�� ǥ��
��� ���ϱ�: �̵� ǥ��

2. ���� ��ǥ��
��� ��ȯ�� 3x3 ��� ������ Ȯ��, ȸ��, �̵� ǥ�� ������
*/