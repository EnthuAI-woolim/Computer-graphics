#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>

void RenderScene(void) {
    GLfloat x = 0, y = 0, z = 0;
    GLint offset = 20;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // ȸ�� ����
    glRotated(45.0f, 1.0f, 0.0f, 0.0f); // x�� ȸ��
    glRotated(45.0f, 0.0f, 1.0f, 0.0f); // y�� ȸ��

    glColor3f(1.0f, 0.0f, 0.0f); // ������
    glLineWidth(3.0f);           // ����

    // === �Ǽ� ���� ===
    glBegin(GL_LINES);
    // �ո�
    glVertex3d(x - offset, y - offset, z + offset); glVertex3d(x + offset, y - offset, z + offset);
    glVertex3d(x + offset, y - offset, z + offset); glVertex3d(x + offset, y + offset, z + offset);
    glVertex3d(x + offset, y + offset, z + offset); glVertex3d(x - offset, y + offset, z + offset);
    glVertex3d(x - offset, y + offset, z + offset); glVertex3d(x - offset, y - offset, z + offset);

    // �޸� (�� + ������ + ���� ������ ���μ�)
    glVertex3d(x + offset, y + offset, z - offset); glVertex3d(x - offset, y + offset, z - offset);
    glVertex3d(x - offset, y + offset, z - offset); glVertex3d(x - offset, y - offset, z - offset);

    // �յ� ���ἱ (������ ���μ� 2��, ���� ���μ�)
    glVertex3d(x + offset, y + offset, z + offset); glVertex3d(x + offset, y + offset, z - offset);
    glVertex3d(x - offset, y + offset, z + offset); glVertex3d(x - offset, y + offset, z - offset);
    glVertex3d(x - offset, y - offset, z + offset); glVertex3d(x - offset, y - offset, z - offset);
    glEnd();

    // === ���� ���� (�������� ����) ===
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x5555);
    glBegin(GL_LINES);
    glVertex3d(x - offset, y - offset, z - offset); glVertex3d(x + offset, y - offset, z - offset);
    glVertex3d(x + offset, y - offset, z - offset); glVertex3d(x + offset, y + offset, z - offset);
    glVertex3d(x + offset, y - offset, z + offset); glVertex3d(x + offset, y - offset, z - offset);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glPopMatrix();
    glFlush();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLint wSize = 100;
    GLfloat aspectRatio;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h)
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 100);
    else
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100, 100);

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
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
}
