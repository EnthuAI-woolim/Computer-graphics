#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>

void RenderScene(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    // 폴리곤 삼각형 그리기 색상
    // glShadeModel(GL_FLAT) => 제일 마지막에 지정한 색상으로 그려짐
    // glShadeModel(GL_SMOOTH) => 각 정점에 지정한 색상으로 그려짐(그라데이션 효과)
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(50.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(50.0f, 50.0f);
    glEnd();
    

    glFlush();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
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
