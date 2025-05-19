#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>

void RenderScene(void) {
    GLfloat x = 0, y = 0, z = 0;
    GLint offset = 20;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // 회전 적용
    glRotated(45.0f, 1.0f, 0.0f, 0.0f); // x축 회전
    glRotated(45.0f, 0.0f, 1.0f, 0.0f); // y축 회전

    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glLineWidth(3.0f);           // 굵게

    // === 실선 영역 ===
    glBegin(GL_LINES);
    // 앞면
    glVertex3d(x - offset, y - offset, z + offset); glVertex3d(x + offset, y - offset, z + offset);
    glVertex3d(x + offset, y - offset, z + offset); glVertex3d(x + offset, y + offset, z + offset);
    glVertex3d(x + offset, y + offset, z + offset); glVertex3d(x - offset, y + offset, z + offset);
    glVertex3d(x - offset, y + offset, z + offset); glVertex3d(x - offset, y - offset, z + offset);

    // 뒷면 (위 + 오른쪽 + 위쪽 오른쪽 세로선)
    glVertex3d(x + offset, y + offset, z - offset); glVertex3d(x - offset, y + offset, z - offset);
    glVertex3d(x - offset, y + offset, z - offset); glVertex3d(x - offset, y - offset, z - offset);

    // 앞뒤 연결선 (오른쪽 세로선 2개, 위쪽 가로선)
    glVertex3d(x + offset, y + offset, z + offset); glVertex3d(x + offset, y + offset, z - offset);
    glVertex3d(x - offset, y + offset, z + offset); glVertex3d(x - offset, y + offset, z - offset);
    glVertex3d(x - offset, y - offset, z + offset); glVertex3d(x - offset, y - offset, z - offset);
    glEnd();

    // === 점선 영역 (가려지는 선만) ===
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
