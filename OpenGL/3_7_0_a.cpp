#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>

#define GL_PI 3.1415f
bool bCull = true;
GLfloat xTran = 0.0f;
GLfloat yTran = 0.0f;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

void SpecialKeys(int key, int, int y) {
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
    if (key == 'a')
        xTran -= 2.0f;
    else if (key == 'd')
        xTran += 2.0f;
    else if (key == 'w')
        yTran += 2.0f;
    else if (key == 'x')
        yTran -= 2.0f;

    glutPostRedisplay();
}

void RenderScene(void) {

    GLfloat x, y, angle;

    glClear(GL_COLOR_BUFFER_BIT);

    if (bCull) {
        glEnable(GL_CULL_FACE); // ������Ʈ �ڿ��� ������ �ʵ��� �ϴ� ���
    }
    else {
        glDisable(GL_CULL_FACE);
    }

    glPushMatrix();
    // ����Ű ������ ��� ȸ��
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // a,d: x���̵�, w,x: y���̵� 
    glTranslatef(xTran, yTran, 0.0f);


    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(0, 0);
    int idx = 0;
    for (angle = 0.0f; angle <= (2.0f * GL_PI); angle += (GL_PI / 8.0f)) { // �� ������ 180���̹Ƿ�, ��/8�� 22.5
        // �ð�ݴ����(�������): glEnable(GL_CULL_FACE)�ص� ����
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);
        // �ð����(�ĸ����): glEnable(GL_CULL_FACE)�ϸ� �Ⱥ���
        // x = 50.0f * sin(angle);
        // y = 50.0f * cos(angle);
        if (idx % 2 == 0) glColor3f(0.0f, 1.0f, 0.0f);
        else glColor3f(1.0f, 0.0f, 0.0f);

        glVertex2d(x, y);
        idx++;
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2d(0, 0);
    for (angle = 0.0f; angle <= (2.0f * GL_PI); angle += (GL_PI / 8.0f)) { // �� ������ 180���̹Ƿ�, ��/8�� 22.5
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);

        glVertex2d(x, y);
    }
    glEnd();

    glPopMatrix();
    glFlush();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
    //glShadeModel(GL_SMOOTH);
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
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}

/*
GL_CULL_FACE
: ������Ʈ �ڿ��� �Ⱥ����� �ʵ��� �ϴ� ���


*/