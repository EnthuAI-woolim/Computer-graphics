#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>

#define GL_PI 3.1415f

void RenderScene(void) {

    GLfloat x, y, angle;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(0, 0);
    int idx = 0;
    for (angle = 0.0f; angle <= (2.0f * GL_PI); angle += (GL_PI / 8.0f)) { // π 라디안이 180°이므로, π/8은 22.5
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);
        if (idx % 2 == 0) glColor3f(0.0f, 1.0f, 0.0f);
        else glColor3f(1.0f, 0.0f, 0.0f);

        glVertex2d(x, y);
        idx++;
    }
    glEnd();


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
    glutMainLoop();
}
