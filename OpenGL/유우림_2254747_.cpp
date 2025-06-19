#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
using namespace std;

#define GL_PI 3.1415f
int num = 0;

void keyboard(unsigned char key, int x, int y) {
    num = int(key) - 48;
    //num++;

    cout << num;

    glutPostRedisplay();
}


void RenderScene(void) {
    GLfloat x, y, angle;
    int idx;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Ű���带 1���� 8���� ������� ������ ������ �ϳ��� ����(����)�Ǵ� �ڵ� �����
    // ������ �� 8���̴�.
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    idx = 0;
    for (angle = 0.0f; angle < (2.0f * GL_PI) / 8 * num + 0.5; angle += (GL_PI / 4.0f)) {

        if (idx % 2) glColor3f(0.0f, 1.0f, 0.0f);
        else glColor3f(1.0f, 0.0f, 0.0f);

        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);
        glVertex2f(x, y);
        idx++;
    }
    glEnd();

    //glFlush();
    glutSwapBuffers();
}


void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
    //glShadeModel(GL_SMOOTH);
}
void ChangeSize(GLsizei w, GLsizei h) {
    GLdouble nRange = 100;
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

    glutKeyboardFunc(keyboard);

    SetupRC();
    glutMainLoop();
}
