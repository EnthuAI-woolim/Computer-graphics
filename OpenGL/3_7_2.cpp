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
    GLfloat x, y, angle, zLoc;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    glPushMatrix();

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);


    glTranslatef(xTran, yTran, 0.0f);

    gluLookAt(
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f
    );

    zLoc = 10.0f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, zLoc);
    for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f)) {
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);
        glVertex3f(x, y, zLoc);
    }
    glEnd();

    zLoc = 20.0f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, zLoc);
    for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f)) {
        x = 20.0f * cos(angle);
        y = 20.0f * sin(angle);

        glVertex3f(x, y, zLoc);
    }
    glEnd();

    glPopMatrix();
    //glFlush();
    glutSwapBuffers();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
}
void ChangeSize(GLsizei w, GLsizei h) {
    GLdouble nRange = 100.0f;
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

